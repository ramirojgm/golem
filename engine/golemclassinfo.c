/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "golem.h"
#include <gmodule.h>
#include <string.h>

struct _GolemClassInfoPrivate {
  gchar * name;
  gchar * parent_name;

  GType   gtype;
  GType	  gtype_parent;

  goffset private_offset;

  GolemModule
    * module;

  GolemStatement
    * init,
    * constructed,
    * dispose,
    * finalize;

  void (*parent_dispose)(GObject * object);

  GList
    * interfaces,
    * functions,
    * properties;
};

struct _GolemFunctionSpec
{
  GolemClosureInfo * info;
  GolemStatement * body;
};

struct _GolemPropertySpec {
  gchar * type;
  gchar * property_name;
  GParamSpec * param_spec;
  GolemStatement * getter;
  GolemStatement * setter;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemClassInfo,golem_class_info,GOLEM_TYPE_TYPE_INFO)

static void
golem_class_info_init(GolemClassInfo * info)
{
  GolemClassInfoPrivate * priv = golem_class_info_get_instance_private(info);
  info->priv = priv;
  priv->gtype = G_TYPE_NONE;
  priv->parent_dispose = NULL;
  priv->init = NULL;
  priv->constructed = NULL;
  priv->dispose = NULL;
  priv->name = NULL;
  priv->functions = NULL;
  priv->properties = NULL;
  g_mutex_init(&(info->mutex));
}

static GolemMap *
golem_object_get_instance_private(GolemClassInfo * info,gpointer instance)
{
  return *((GolemMap**)(instance + info->priv->private_offset));
}

static void
golem_object_stack_error_free(GQueue * stack_error)
{
  g_queue_free_full(stack_error,(GDestroyNotify)g_error_free);
}

void
golem_object_push_error(gpointer object,GError * error)
{
  GQueue * queue =  g_object_get_data(G_OBJECT(object),"::stack_error::");
  if(!queue)
    {
      queue = g_queue_new();
      g_object_set_data_full(G_OBJECT(object),"::stack_error::",queue,(GDestroyNotify)golem_object_stack_error_free);
    }
  g_queue_push_tail(queue,error);
}

GError *
golem_object_pop_error(gpointer object)
{
  GQueue * queue =  g_object_steal_data(G_OBJECT(object),"::stack_error::");
  GError * error = NULL;
  if(queue)
    {
      gchar new_description[2048] = {0,};
      memset(new_description,0,2048);
      GError * new_error;
      while(!g_queue_is_empty(queue))
	{
	  new_error = (GError*)g_queue_pop_head(queue);
	  strcat(new_description,new_error->message);
	  strcat(new_description,"\n");
	  g_error_free(new_error);
	}
      g_queue_free(queue);
      error = g_error_new_literal(GOLEM_ERROR,GOLEM_UNHANDLED_ERROR,new_description);
    }
  return error;
}

static void
golem_object_init(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemClassInfo * info = GOLEM_CLASS_INFO(data);
  if(info)
    {
      GolemMap * priv = golem_map_new();
      *((GolemMap**)(instance + info->priv->private_offset)) = priv;

      if(info->priv->init)
	{
	  GError * error = NULL;
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,info->priv->gtype);
	  g_value_init(&priv_value,GOLEM_TYPE_MAP);
	  g_value_take_object(&this_value,instance);
	  g_value_take_boxed(&priv_value,priv);
	  GolemRuntime * runtime = golem_runtime_new(golem_module_get_context(info->priv->module));
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  golem_statement_execute(info->priv->init,runtime,&error);
	  if(error)
	    golem_object_push_error(instance,error);
	  golem_runtime_destroy(runtime);
	}
    }
}

static void
golem_object_constructed(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemClassInfo * info = GOLEM_CLASS_INFO(data);
  if(info)
    {
      GolemMap * priv = golem_object_get_instance_private(info,instance);
      if(info->priv->constructed)
	{
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,info->priv->gtype);
	  g_value_init(&priv_value,GOLEM_TYPE_MAP);
	  g_value_take_object(&this_value,instance);
	  g_value_take_boxed(&priv_value,priv);
	  GolemRuntime * runtime = golem_runtime_new(golem_module_get_context(info->priv->module));
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  GError * constructed_error = NULL;
	  golem_statement_execute(info->priv->constructed,runtime,&constructed_error);
	  if(constructed_error)
	    {
	      g_print("%s",constructed_error->message);
	    }
	  golem_runtime_destroy(runtime);
	}
    }
}

static void
golem_object_dispose(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemClassInfo * info = GOLEM_CLASS_INFO(data);
  g_print("Dispose");
  if(info)
    {
      GolemMap * priv = golem_object_get_instance_private(info,instance);
      if(info->priv->dispose)
	{
	  GValue priv_value = G_VALUE_INIT;
	  GValue this_value = G_VALUE_INIT;
	  g_value_init(&priv_value,GOLEM_TYPE_MAP);
	  g_value_init(&this_value,info->priv->gtype);
	  g_value_take_object(&this_value,instance);
	  g_value_take_boxed(&priv_value,priv);

	  GolemRuntime * runtime = golem_runtime_new(golem_module_get_context(info->priv->module));
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_statement_execute(info->priv->dispose,runtime,NULL);
	  golem_runtime_destroy(runtime);
	}
    }
  info->priv->parent_dispose(instance);
}


static void
golem_object_get_property(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemClassInfo * info = GOLEM_CLASS_INFO(data);
  guint property_id = golem_llm_invoke_get_guint(invoke);
  GValue * value = (GValue*)golem_llm_invoke_get_gpointer(invoke);

  g_mutex_lock(&info->mutex);
  GolemPropertySpec * property = (GolemPropertySpec *)g_list_nth_data(g_list_first( info->priv->properties),property_id - 1);
  g_mutex_unlock(&info->mutex);

  if(property && property->getter)
    {
      GolemMap * priv = golem_object_get_instance_private(info,instance);
      GValue priv_value = G_VALUE_INIT;
      GValue this_value = G_VALUE_INIT;
      GValue return_value = G_VALUE_INIT;
      g_value_init(&priv_value,GOLEM_TYPE_MAP);
      g_value_init(&this_value,info->priv->gtype);
      g_value_take_boxed(&priv_value,priv);
      g_value_take_object(&this_value,instance);
      GolemRuntime * runtime = golem_runtime_new(golem_module_get_context(info->priv->module));
      golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
      golem_statement_execute(property->getter,runtime,NULL);
      golem_runtime_get_return(runtime,&return_value);
      golem_runtime_destroy(runtime);
      g_value_copy(&return_value,value);
      g_value_unset(&return_value);
    }
}

static void
golem_object_set_property(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemClassInfo * info = GOLEM_CLASS_INFO(data);
  guint property_id = golem_llm_invoke_get_guint(invoke);
  GValue * value = (GValue*)golem_llm_invoke_get_gpointer(invoke);

  g_mutex_lock(&info->mutex);
  GolemPropertySpec * property = (GolemPropertySpec *)g_list_nth_data(g_list_first( info->priv->properties),property_id - 1);
  g_mutex_unlock(&info->mutex);

  if(property && property->setter)
    {
      GolemMap * priv = golem_object_get_instance_private(info,instance);
      GValue priv_value = G_VALUE_INIT;
      GValue this_value = G_VALUE_INIT;
      g_value_init(&priv_value,GOLEM_TYPE_MAP);
      g_value_init(&this_value,info->priv->gtype);
      g_value_take_boxed(&priv_value,priv);
      g_value_take_object(&this_value,instance);
      GolemRuntime * runtime = golem_runtime_new(golem_module_get_context(info->priv->module));
      golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"value",value,NULL);
      golem_statement_execute(property->setter,runtime,NULL);
      golem_runtime_destroy(runtime);
    }
}


static const gchar *
_golem_type_info_get_name(GolemTypeInfo * type_info)
{
  GolemClassInfo * self = GOLEM_CLASS_INFO(type_info);
  return self->priv->name;
}

static void
golem_object_class_init (gpointer klass,GolemLLMInvoke * invoke,gpointer class_data)
{
  GolemClassInfo * info = GOLEM_CLASS_INFO(class_data);

  info->priv->parent_dispose = G_OBJECT_CLASS(klass)->dispose;

  G_OBJECT_CLASS(klass)->dispose = golem_llm_new_vfunction(golem_object_dispose,info);
  G_OBJECT_CLASS(klass)->constructed = golem_llm_new_vfunction(golem_object_constructed,info);
  G_OBJECT_CLASS(klass)->set_property = golem_llm_new_vfunction(golem_object_set_property,info);
  G_OBJECT_CLASS(klass)->get_property = golem_llm_new_vfunction(golem_object_get_property,info);

  guint property_id;
  guint property_count;
  GList * property_iter_spec = NULL;
  GolemPropertySpec * property_spec = NULL;

  property_count = g_list_length(g_list_first(info->priv->properties));
  property_iter_spec = g_list_first(info->priv->properties);
  if(property_iter_spec)
    property_spec = (GolemPropertySpec*)property_iter_spec->data;

  for(property_id = 1;property_id <= property_count;property_id ++ )
    {
      if(!property_spec->param_spec)
      {
	GType property_type = golem_type_from_name(property_spec->type);
	GParamFlags property_flags = 0;

	if(property_spec->getter && property_spec->setter)
	  property_flags = G_PARAM_READWRITE | G_PARAM_CONSTRUCT;
	else if(property_spec->getter)
	  property_flags = G_PARAM_READABLE;
	else if(property_spec->setter)
	  property_flags = G_PARAM_WRITABLE | G_PARAM_CONSTRUCT;

	if(property_type)
	  {
	    GType fundamental_type = G_TYPE_FUNDAMENTAL(property_type);
	    switch(fundamental_type)
	    {
	      case G_TYPE_BOOLEAN:
		property_spec->param_spec = g_param_spec_boolean(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    FALSE,
		    property_flags);
		break;
	      case G_TYPE_BOXED:
		property_spec->param_spec = g_param_spec_boxed(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    property_type,
		    property_flags);
		break;
	      case G_TYPE_OBJECT:
		property_spec->param_spec = g_param_spec_object(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    property_type,
		    property_flags);
		break;
	      case G_TYPE_ENUM:
		property_spec->param_spec = g_param_spec_enum(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    property_type,
		    0,
		    property_flags);
		break;
	      case G_TYPE_FLAGS:
		property_spec->param_spec = g_param_spec_flags(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    property_type,
		    0,
		    property_flags);
		break;
	      case G_TYPE_DOUBLE:
		property_spec->param_spec = g_param_spec_double(
		      property_spec->property_name,
		      property_spec->property_name,
		      "",
		      G_MINDOUBLE,
		      G_MAXDOUBLE,
		      0,
		      property_flags);
		  break;
	      case G_TYPE_FLOAT:
		property_spec->param_spec = g_param_spec_float(
		      property_spec->property_name,
		      property_spec->property_name,
		      "",
		      G_MINFLOAT,
		      G_MAXFLOAT,
		      0,
		      property_flags);
		  break;
	      case G_TYPE_CHAR:
		property_spec->param_spec = g_param_spec_char(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MININT8,
		    G_MAXINT8,
		    0,
		    property_flags);
		break;
	      case G_TYPE_UCHAR:
		property_spec->param_spec = g_param_spec_char(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MININT8,
		    G_MAXUINT8,
		    0,
		    property_flags);
		break;
	      case G_TYPE_INT:
		property_spec->param_spec = g_param_spec_int(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MININT,
		    G_MAXINT,
		    0,
		    property_flags);
		break;
	      case G_TYPE_UINT:
		property_spec->param_spec = g_param_spec_uint(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MININT,
		    G_MAXUINT,
		    0,
		    property_flags);
		break;
	      case G_TYPE_INT64:
		property_spec->param_spec = g_param_spec_int64(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MININT64,
		    G_MAXINT64,
		    0,
		    property_flags);
		break;
	      case G_TYPE_UINT64:
		property_spec->param_spec = g_param_spec_uint64(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MININT64,
		    G_MAXUINT64,
		    0,
		    property_flags);
		break;
	      case G_TYPE_LONG:
		property_spec->param_spec = g_param_spec_long(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MINLONG,
		    G_MAXLONG,
		    0,
		    property_flags);
		break;
	      case G_TYPE_ULONG:
		property_spec->param_spec = g_param_spec_ulong(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    G_MINLONG,
		    G_MAXULONG,
		    0,
		    property_flags);
		break;
	      case G_TYPE_STRING:
		property_spec->param_spec = g_param_spec_string(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    "",
		    property_flags);
		break;
	      case G_TYPE_POINTER:
		property_spec->param_spec = g_param_spec_pointer(
		    property_spec->property_name,
		    property_spec->property_name,
		    "",
		    property_flags);
		break;
	      default:
		continue;
	    }
	  }
	else
	  {
	    continue;
	  }
      }

      g_object_class_install_property(klass,property_id,property_spec->param_spec);
      property_iter_spec = g_list_next(property_iter_spec);
      if(property_iter_spec)
      property_spec = (GolemPropertySpec*)property_iter_spec->data;
    }
}


static GType
_golem_type_info_register_type(GolemTypeInfo * type_info,GolemModule * module,GError ** error)
{
  GolemClassInfo * self = GOLEM_CLASS_INFO(type_info);
  GType parent_type = G_TYPE_OBJECT;

  if(self->priv->parent_name)
    {
      parent_type = golem_type_from_name(self->priv->parent_name);
      if(!parent_type)
      return 0;
    }

  self->priv->gtype_parent = parent_type;

  GTypeQuery parent_query = {0,};
  g_type_query(self->priv->gtype_parent,&parent_query);

  const GTypeInfo info = {
	  parent_query.class_size,
	  (GBaseInitFunc) NULL,
	  (GBaseFinalizeFunc) NULL,
	  (GClassInitFunc)golem_llm_new_vfunction(golem_object_class_init,self),
	  NULL,
	  NULL,
	  parent_query.instance_size + sizeof(gpointer),
	  0,
	  (GInstanceInitFunc)golem_llm_new_vfunction(golem_object_init,self),
	  NULL
  };

  self->priv->private_offset = parent_query.instance_size;
  self->priv->module = module;

  self->priv->gtype = golem_module_register_type(
	module,
	GOLEM_TYPE_INFO(self),
        parent_type,
        self->priv->name,
        &info,
        0);

  return self->priv->gtype;
}


static gboolean
_golem_type_info_get_member(GolemTypeInfo * type_info,GValue * instance,const gchar * name,GValue * dest,GError ** error)
{
  GolemClassInfo * self = GOLEM_CLASS_INFO(type_info);
  GolemTypeInfo * parent_info = NULL;
  GValue * data_value = NULL;
  GParamSpec * property = NULL;

  gboolean done = FALSE;

  gpointer object_instance = g_value_get_object(instance);

  for(GList * iter = g_list_first(self->priv->functions);iter;iter = g_list_next(iter))
    {
      GolemFunctionSpec* func_spec = (GolemFunctionSpec*)iter->data;
      if(g_strcmp0(golem_closure_info_get_name(func_spec->info),name) == 0)
	{
	  GolemContext * context = golem_context_new(golem_module_get_context(self->priv->module));
	  golem_context_set_this(context,instance);
	  if(self->priv->private_offset)
	    {
	      GValue priv_value = G_VALUE_INIT;
	      g_value_init(&priv_value,GOLEM_TYPE_MAP);
	      g_value_set_boxed(&priv_value,(gpointer)golem_object_get_instance_private(self,object_instance));
	      golem_context_set_auto(context,"priv",&priv_value,error);
	      g_value_unset(&priv_value);
	    }

	  GolemClosure * closure = golem_function_new(func_spec->info,context,func_spec->body);
	  golem_closure_set_this(closure,instance);
	  g_value_init(dest,G_TYPE_CLOSURE);
	  g_value_take_boxed(dest,closure);
	  g_object_unref(context);
	  done = TRUE;
	  goto finish;
	}
    }


  if((property = g_object_class_find_property(G_OBJECT_GET_CLASS(object_instance),name)))
    {
      g_value_init(dest,property->value_type);
      g_object_get_property(G_OBJECT(object_instance),name,dest);
      done = TRUE;
      goto finish;
    }

  if((parent_info = golem_type_info_from_gtype(self->priv->gtype_parent)))
    {
      if((done = golem_type_info_get_member(parent_info,instance,name,dest,error)))
	{
	 goto finish;
	}
    }

   if((data_value = g_object_get_data(G_OBJECT(object_instance),name)))
    {
     g_value_init(dest,G_VALUE_TYPE(data_value));
     g_value_copy(data_value,dest);
     done = TRUE;
    }

finish:
  return done;
}

static gboolean
_golem_type_info_set_member(GolemTypeInfo * type_info,GValue * instance,const gchar * name,const GValue * src,GError ** error)
{
  GValue * data_value = NULL;
  GParamSpec * property = NULL;
  gboolean done = FALSE;

  gpointer object_instance = g_value_get_object(instance);

  if((property = g_object_class_find_property(G_OBJECT_GET_CLASS(object_instance),name)))
    {
      g_object_set_property(G_OBJECT(object_instance),name,src);
      done = TRUE;
      goto finish;
    }
  else
    {
      data_value = g_new0(GValue,1);
      g_value_init(data_value,G_VALUE_TYPE(src));
      g_value_copy(src,data_value);
      g_object_set_data_full(G_OBJECT(object_instance),name,data_value,(GDestroyNotify)g_value_free);
      done = TRUE;
      goto finish;
    }

finish:
  return done;
}


static void
golem_class_info_class_init(GolemClassInfoClass * info)
{
  GOLEM_TYPE_INFO_CLASS(info)->get_name = _golem_type_info_get_name;
  GOLEM_TYPE_INFO_CLASS(info)->register_type = _golem_type_info_register_type;
  GOLEM_TYPE_INFO_CLASS(info)->get_member = _golem_type_info_get_member;
  GOLEM_TYPE_INFO_CLASS(info)->set_member = _golem_type_info_set_member;
}


GolemStatement *
golem_class_info_get_init(GolemClassInfo * info)
{
  return info->priv->init;
}

void
golem_class_info_set_init(GolemClassInfo * info,GolemStatement * statement)
{
  g_clear_object(&(info->priv->init));
  info->priv->init = statement;
}

GolemStatement *
golem_class_info_get_dispose(GolemClassInfo * info)
{
  return info->priv->dispose;
}

void
golem_class_info_set_dispose(GolemClassInfo * info,GolemStatement * statement)
{
  g_clear_object(&(info->priv->dispose));
  info->priv->dispose = statement;
}

GolemStatement *
golem_class_info_get_constructed(GolemClassInfo * info)
{
  return info->priv->constructed;
}

void
golem_class_info_set_constructed(GolemClassInfo * info,GolemStatement * statement)
{
  g_clear_object(&(info->priv->constructed));
  info->priv->constructed = statement;
}

GolemClassInfo *
golem_class_info_new(const gchar * name)
{
  GolemClassInfo * type_info = GOLEM_CLASS_INFO(g_object_new(GOLEM_TYPE_CLASS_INFO,NULL));
  type_info->priv->name = g_strdup(name);
  type_info->priv->gtype = 0;
  return type_info;
}


void
golem_class_info_set_parent(GolemClassInfo * type_info,const gchar * base)
{
  type_info->priv->parent_name = g_strdup(base);
}

void
golem_class_info_add_function(GolemClassInfo * type_info,GolemFunctionSpec * function)
{
  type_info->priv->functions = g_list_append(type_info->priv->functions,function);
}

void
golem_class_info_add_property(GolemClassInfo * type_info,GolemPropertySpec * property)
{
  type_info->priv->properties = g_list_append(type_info->priv->properties,property);
}

void
_golem_closure_object_finalize(GolemClosure * closure,gpointer data)
{
  g_object_unref(data);
}

void
_golem_closure_value_finalize(GolemClosure * closure,gpointer data)
{
  g_value_free((GValue*)data);
}

GolemFunctionSpec *
golem_function_spec_new(GolemClosureInfo * info,GolemStatement * body)
{
  GolemFunctionSpec * function = g_new0(GolemFunctionSpec,1);
  function->info = info;
  function->body = body;
  return function;
}


GolemPropertySpec *
golem_property_spec_new(const gchar * type,const gchar * property_name,GolemStatement * get,GolemStatement * set)
{
  GolemPropertySpec * spec = g_new0(GolemPropertySpec,1);
  spec->type = g_strdup(type);
  spec->property_name = g_strdup(property_name);
  spec->param_spec = NULL;
  spec->getter = get;
  spec->setter = set;
  return spec;
}
