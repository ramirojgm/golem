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

typedef struct _GolemPrivateInstance GolemPrivateInstance;

static GList *	_golem_type_info = NULL;
GMutex 		_golem_type_info_mutex = G_STATIC_MUTEX_INIT;

struct _GolemTypeInfoPrivate {
  gchar * name;
  GType   gtype;
  GType   gtype_parent;
  goffset private_offset;

  GolemContext
    * define_context;

  GolemStatement
    * init,
    * constructed,
    * dispose,
    * finalize,
    * parse;

  void (*parent_dispose)(GObject * object);

  GList
    * bases,
    * functions,
    * properties;
};

struct _GolemTypeSpec
{
  GType 	type;
  GType		template_param;
  gchar * 	type_name;
  gchar * 	template_param_name;
};

struct _GolemFunctionSpec
{
  GolemClosureInfo * info;
  const gchar * name;
  GolemFunctionType type;
  union {
    GolemStatement * body;
    goffset offset;
    gchar * symbol_name;
    GolemClosureInvokeFunc func;
  } data;
};

struct _GolemPropertySpec {
  GolemTypeSpec * type_spec;
  gchar * property_name;
  GParamSpec * param_spec;
  GolemStatement * getter;
  GolemStatement * setter;
};

struct _GolemTypePrivatePrivate
{
  gpointer padding[5];
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemTypeInfo,golem_type_info,G_TYPE_OBJECT)
G_DEFINE_TYPE_WITH_PRIVATE(GolemTypePrivate,golem_type_private,G_TYPE_OBJECT)

static void
golem_type_info_init(GolemTypeInfo * info)
{
  GolemTypeInfoPrivate * priv = golem_type_info_get_instance_private(info);
  info->priv = priv;
  priv->gtype = 0;
  priv->gtype_parent = 0;
  priv->parent_dispose = NULL;
  priv->init = NULL;
  priv->parse = NULL;
  priv->constructed = NULL;
  priv->dispose = NULL;
  priv->name = NULL;
  priv->functions = NULL;
  priv->properties = NULL;
  g_mutex_init(&(info->mutex));
}

static void
golem_type_private_init(GolemTypePrivate * self)
{
  self->priv = golem_type_private_get_instance_private(self);
}

static void
golem_type_private_class_init(GolemTypePrivateClass * klass)
{

}

static GolemTypePrivate *
_golem_object_get_instance_private(GolemTypeInfo * info,gpointer instance)
{
  return GOLEM_TYPE_PRIVATE(*((GolemTypePrivate**)(instance + info->priv->private_offset)));
}

GolemTypePrivate *
golem_type_private_new()
{
  return GOLEM_TYPE_PRIVATE(g_object_new(GOLEM_TYPE_TYPE_PRIVATE,NULL));
}

static void
_golem_object_init(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemTypeInfo * info = GOLEM_TYPE_INFO(data);
  if(info)
    {
      GolemTypePrivate * priv = golem_type_private_new();
      *((GolemTypePrivate**)(instance + info->priv->private_offset)) = priv;
      if(info->priv->init)
	{
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,G_TYPE_FROM_INSTANCE(instance));
	  g_value_init(&priv_value,G_TYPE_OBJECT);
	  g_value_take_object(&this_value,instance);
	  g_value_take_object(&priv_value,priv);
	  GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  golem_statement_execute(info->priv->init,runtime,NULL);
	  golem_runtime_destroy(runtime);
	}
    }
}

static void
_golem_object_constructed(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemTypeInfo * info = GOLEM_TYPE_INFO(data);
  if(info)
    {
      GolemTypePrivate * priv = _golem_object_get_instance_private(info,instance);
      if(info->priv->constructed)
	{
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,G_TYPE_FROM_INSTANCE(instance));
	  g_value_init(&priv_value,G_TYPE_OBJECT);
	  g_value_take_object(&this_value,instance);
	  g_value_take_object(&priv_value,priv);
	  GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
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
_golem_object_dispose(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemTypeInfo * info = GOLEM_TYPE_INFO(data);
  if(info)
    {
      GolemTypePrivate * priv = _golem_object_get_instance_private(info,instance);
      if(info->priv->dispose)
	{
	  GValue priv_value = G_VALUE_INIT;
	  GValue this_value = G_VALUE_INIT;
	  g_value_init(&priv_value,GOLEM_TYPE_TYPE_PRIVATE);
	  g_value_init(&this_value,info->priv->gtype);
	  g_value_take_object(&priv_value,priv);
	  g_value_take_object(&this_value,instance);
	  GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
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
_golem_object_get_property(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemTypeInfo * info = GOLEM_TYPE_INFO(data);
  guint property_id = golem_llm_invoke_get_guint(invoke);
  GValue * value = (GValue*)golem_llm_invoke_get_gpointer(invoke);

  g_mutex_lock(&info->mutex);
  GolemPropertySpec * property = (GolemPropertySpec *)g_list_nth_data(g_list_first( info->priv->properties),property_id - 1);
  g_mutex_unlock(&info->mutex);

  if(property && property->getter)
    {
      GolemTypePrivate * priv = _golem_object_get_instance_private(info,instance);
      GValue priv_value = G_VALUE_INIT;
      GValue this_value = G_VALUE_INIT;
      GValue return_value = G_VALUE_INIT;
      g_value_init(&priv_value,GOLEM_TYPE_TYPE_PRIVATE);
      g_value_init(&this_value,info->priv->gtype);
      g_value_take_object(&priv_value,priv);
      g_value_take_object(&this_value,instance);
      GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
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
_golem_object_set_property(gpointer instance, GolemLLMInvoke * invoke,gpointer data)
{
  GolemTypeInfo * info = GOLEM_TYPE_INFO(data);
  guint property_id = golem_llm_invoke_get_guint(invoke);
  GValue * value = (GValue*)golem_llm_invoke_get_gpointer(invoke);

  g_mutex_lock(&info->mutex);
  GolemPropertySpec * property = (GolemPropertySpec *)g_list_nth_data(g_list_first( info->priv->properties),property_id - 1);
  g_mutex_unlock(&info->mutex);

  if(property && property->setter)
    {
      GolemTypePrivate * priv = _golem_object_get_instance_private(info,instance);
      GValue priv_value = G_VALUE_INIT;
      GValue this_value = G_VALUE_INIT;
      g_value_init(&priv_value,GOLEM_TYPE_TYPE_PRIVATE);
      g_value_init(&this_value,info->priv->gtype);
      g_value_take_object(&priv_value,priv);
      g_value_take_object(&this_value,instance);
      GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
      golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
      golem_context_set_auto(golem_runtime_get_context(runtime),"value",value,NULL);
      golem_statement_execute(property->setter,runtime,NULL);
      golem_runtime_destroy(runtime);
    }
}

static void
_golem_object_class_init(gpointer klass, GolemLLMInvoke * invoke,gpointer data)
{
  GolemTypeInfo * info = GOLEM_TYPE_INFO(data);

  info->priv->parent_dispose = G_OBJECT_CLASS(klass)->dispose;

  G_OBJECT_CLASS(klass)->dispose = golem_llm_new_vfunction(_golem_object_dispose,info);
  G_OBJECT_CLASS(klass)->constructed = golem_llm_new_vfunction(_golem_object_constructed,info);
  G_OBJECT_CLASS(klass)->set_property = golem_llm_new_vfunction(_golem_object_set_property,info);
  G_OBJECT_CLASS(klass)->get_property = golem_llm_new_vfunction(_golem_object_get_property,info);

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
	  GType property_type = golem_type_spec_get(property_spec->type_spec,info->priv->define_context,NULL);
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

static void
golem_type_info_class_init(GolemTypeInfoClass * info)
{

}

GType
golem_type_info_register(GolemTypeInfo * info,GolemContext * context,GError ** error)
{
  GType parent_type = G_TYPE_OBJECT;
  GTypeQuery parent_query = {0,};
  if(info->priv->bases)
    {
      GList * first_base = g_list_first(info->priv->bases);
      parent_type = golem_type_spec_get((GolemTypeSpec*)first_base->data,context,error);
      if(!parent_type)
	return 0;
    }

  g_type_query(parent_type,&parent_query);
  info->priv->define_context = GOLEM_CONTEXT(g_object_ref(context));
  info->priv->gtype = g_type_register_static_simple (
				 parent_type,
				 info->priv->name,
				 parent_query.class_size,
				 golem_llm_new_vfunction(_golem_object_class_init,info),
				 parent_query.instance_size + sizeof(GolemTypePrivate*),
				 golem_llm_new_vfunction(_golem_object_init,info),
				 0);

  info->priv->private_offset = parent_query.instance_size;
  _golem_type_info = g_list_append(_golem_type_info,info);
  return info->priv->gtype;
}

GolemStatement *
golem_type_info_get_init(GolemTypeInfo * info)
{
  return info->priv->init;
}

void
golem_type_info_set_init(GolemTypeInfo * info,GolemStatement * statement)
{
  g_clear_object(&(info->priv->init));
  info->priv->init = statement;
}

GolemStatement *
golem_type_info_get_dispose(GolemTypeInfo * info)
{
  return info->priv->dispose;
}

void
golem_type_info_set_dispose(GolemTypeInfo * info,GolemStatement * statement)
{
  g_clear_object(&(info->priv->dispose));
  info->priv->dispose = statement;
}

GolemStatement *
golem_type_info_get_constructed(GolemTypeInfo * info)
{
  return info->priv->constructed;
}

void
golem_type_info_set_constructed(GolemTypeInfo * info,GolemStatement * statement)
{
  g_clear_object(&(info->priv->constructed));
  info->priv->constructed = statement;
}

GolemTypeInfo*
golem_type_info_from_gtype(GType type)
{
  GolemTypeInfo * type_info = NULL;
  g_mutex_lock(&_golem_type_info_mutex);
  for(GList *  iter = g_list_first(_golem_type_info);iter;iter = g_list_next(iter))
    {
      GolemTypeInfo * type_iter = GOLEM_TYPE_INFO(iter->data);
      if(type_iter->priv->gtype == type)
	{
	  type_info = type_iter;
	  break;
	}
    }
  if(!type_info)
    {
      type_info = GOLEM_TYPE_INFO(g_object_new(GOLEM_TYPE_TYPE_INFO,NULL));
      type_info->priv->name = g_strdup(g_type_name(type));
      type_info->priv->gtype = type;
      _golem_type_info = g_list_append(_golem_type_info,type_info);
    }
  g_mutex_unlock(&_golem_type_info_mutex);
  return type_info;
}

GolemTypeInfo *
golem_type_info_new(const gchar * name)
{
  GolemTypeInfo * type_info = GOLEM_TYPE_INFO(g_object_new(GOLEM_TYPE_TYPE_INFO,NULL));
  type_info->priv->name = g_strdup(name);
  type_info->priv->gtype = 0;
  return type_info;
}


const gchar *
golem_type_info_get_name(GolemTypeInfo * type_info)
{
  return type_info->priv->name;
}

void
golem_type_info_add_base(GolemTypeInfo * type_info,GolemTypeSpec * base)
{
  type_info->priv->bases = g_list_append(type_info->priv->bases,base);
}

void
golem_type_info_add_function(GolemTypeInfo * type_info,GolemFunctionSpec * function)
{
  type_info->priv->functions = g_list_append(type_info->priv->functions,function);
}

void
golem_type_info_add_property(GolemTypeInfo * type_info,GolemPropertySpec * property)
{
  type_info->priv->properties = g_list_append(type_info->priv->properties,property);
}

GolemFunctionSpec *
_golem_type_info_find_function(GType type,const gchar * name,GType * type_container)
{
  GType parent_type = g_type_parent(type);
  GolemTypeInfo * type_info = golem_type_info_from_gtype(type);
  for(GList * function_iter = g_list_first(type_info->priv->functions);function_iter;function_iter = g_list_next(function_iter))
    {
      GolemFunctionSpec * function_spec = (GolemFunctionSpec*)function_iter->data;
      const gchar * function_name = function_spec->name;
      if(!function_name)
	function_name = golem_closure_info_get_name(function_spec->info);
      if(g_strcmp0(function_name,name) == 0)
	{
	  if(type_container)
	    *type_container = type;
	  return function_spec;
	}
    }

  guint n_interfaces = 0;
  GType * interfaces = g_type_interfaces(type,&n_interfaces);
  GolemFunctionSpec * interface_function_spec = NULL;
  for(guint itype = 0;itype < n_interfaces; itype++)
    {
      if((interface_function_spec = _golem_type_info_find_function(interfaces[itype],name,type_container)))
	break;
    }
  g_free(interfaces);

  if(interface_function_spec)
    return interface_function_spec;
  else if(parent_type)
    return _golem_type_info_find_function(parent_type,name,type_container);
  else
    return NULL;
}

gboolean
golem_type_info_get_static(GType type,const gchar * name,GValue * dest,GError ** error)
{
  return FALSE;
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

void
golem_type_info_set_context(GolemTypeInfo * info,GolemContext * context)
{
  GolemTypeInfoPrivate * priv = golem_type_info_get_instance_private(info);
  if(!priv->define_context)
    priv->define_context = GOLEM_CONTEXT(g_object_ref(context));
}

gboolean
golem_type_info_get(const GValue * instance,const gchar * name,GValue * dest,GError ** error)
{
  GType	gtype;
  gpointer object_instance = NULL;
  GObjectClass * object_class = NULL;
  GEnumClass * enum_class = NULL;
  GFlagsClass * flags_class = NULL;

  if(G_VALUE_HOLDS_GTYPE(instance))
    {
      gtype = g_value_get_gtype(instance);
      if(G_TYPE_IS_ENUM(gtype))
	enum_class = (GEnumClass*)g_type_class_peek(gtype);
      else if(G_TYPE_IS_FLAGS(gtype))
	flags_class = (GFlagsClass*)g_type_class_peek(gtype);
      else if(G_TYPE_IS_OBJECT(gtype))
	object_class = (GObjectClass*)g_type_class_peek(gtype);
    }
  else
    {
      gtype = G_VALUE_TYPE(instance);
      if(G_VALUE_HOLDS_OBJECT(instance))
	{
	  object_instance = g_value_get_object(instance);
	  object_class = G_OBJECT_GET_CLASS(object_instance);
	}
    }

  GolemTypeInfo * type_info = golem_type_info_from_gtype(gtype);
  GType gtype_function = G_TYPE_NONE;

  GolemFunctionSpec * function = NULL;
  GParamSpec *  property = NULL;
  GolemClosure * closure = NULL;
  gboolean done = FALSE;
  gchar * dashed_name = g_strdup(name);



  //make dashed named property
  for(gchar * dn = dashed_name;*dn;dn++)
    {
      if(*dn == '_')
	*dn = '-';
    }

  //find function
  if((function = _golem_type_info_find_function(gtype,name,&gtype_function)))
    {
      if((function->info == NULL)||golem_closure_info_resolve(function->info,type_info->priv->define_context,error))
	{
	  done = TRUE;
	  if(function->type == GOLEM_FUNCTION_SYMBOLIC)
	    {
	      gpointer symbol = NULL;
	      GModule * global = g_module_open(NULL,G_MODULE_BIND_LOCAL);
	      g_module_symbol(global,function->data.symbol_name,&symbol);
	      g_module_close(global);
	      closure = golem_symbol_new(function->info,symbol);
	      if(!G_VALUE_HOLDS_GTYPE(instance))
		golem_closure_set_this(closure,instance);
	      g_value_init(dest,G_TYPE_CLOSURE);
	      g_value_set_boxed(dest,closure);
	      g_closure_unref(G_CLOSURE(closure));
	    }
	  else if(function->type == GOLEM_FUNCTION_VIRTUAL)
	    {
	      GTypeQuery gtype_query = {0,};
	      GTypeQuery gtype_parent_query = {0,};
	      GType gtype_parent = g_type_parent(gtype_function);
	      gpointer * struct_function = NULL;

	      g_type_query(gtype_function,&gtype_query);

	      if(G_TYPE_IS_INTERFACE(gtype_function))
		{
		  struct_function = g_type_interface_peek(object_instance,gtype_function);
		}
	      else
		{
		  goffset gtype_offset = 0;
		  if((gtype_parent != G_TYPE_OBJECT) && gtype_parent)
		    {
		      GTypeQuery parent_query = {0,};
		      g_type_query(gtype_parent,&gtype_parent_query);
		      gtype_offset = parent_query.class_size;
		    }
		  struct_function = (gpointer)object_class + gtype_offset;
		}

	      if(gtype_query.class_size > function->data.offset)
		{
		  closure = golem_symbol_new(function->info,(struct_function + function->data.offset));
		  golem_closure_set_this(closure,instance);
		  g_value_init(dest,G_TYPE_CLOSURE);
		  g_value_set_boxed(dest,closure);
		  g_closure_unref(G_CLOSURE(closure));
		}
	    }
	  else if(function->type == GOLEM_FUNCTION_INTERNAL)
	    {
	      GolemContext * context = golem_context_new(type_info->priv->define_context);
	      golem_context_set_this(context,instance);

	      if(object_instance)
		{
		  GolemTypeInfo * type_info_function = NULL;
		  if(gtype_function != gtype)
		    {
		      type_info_function = golem_type_info_from_gtype(gtype_function);
		    }
		  else
		    {
		      type_info_function = type_info;
		    }

		  if(type_info_function->priv->private_offset)
		    {
		      GValue priv_value = G_VALUE_INIT;
		      g_value_init(&priv_value,GOLEM_TYPE_TYPE_PRIVATE);
		      g_value_set_object(&priv_value,_golem_object_get_instance_private(type_info_function,object_instance));
		      golem_context_set_auto(context,"priv",&priv_value,error);
		      g_value_unset(&priv_value);
		    }
		}

	      closure = golem_function_new(function->info,context,function->data.body);
	      golem_closure_set_this(closure,instance);
	      g_value_init(dest,G_TYPE_CLOSURE);
	      g_value_take_boxed(dest,closure);
	      g_object_unref(context);
	    }
	  else if(function->type == GOLEM_FUNCTION_CLOSURED)
	    {
	      if(object_instance)
		{
		  closure = golem_closure_new(function->data.func,_golem_closure_object_finalize,g_object_ref(object_instance));
		}
	      else
		{
		  GValue * instance_copy = g_new0(GValue,1);
		  g_value_init(instance_copy,G_VALUE_TYPE(instance));
		  g_value_copy(instance,instance_copy);
		  closure = golem_closure_new(function->data.func,_golem_closure_value_finalize,instance_copy);
		}
	      g_value_init(dest,G_TYPE_CLOSURE);
	      g_value_set_boxed(dest,closure);
	      g_closure_unref(G_CLOSURE(closure));
	    }
	}
    }
  else if(G_TYPE_IS_ENUM(gtype))
    {
      //find enumeration member
      GEnumValue * enum_value = g_enum_get_value_by_nick(enum_class,dashed_name);
      g_value_init(dest,gtype);
      if(enum_value)
	  g_value_set_enum(dest,enum_value->value);
      else
	  g_value_set_enum(dest,0);
      done = TRUE;
    }
  else if(G_TYPE_IS_FLAGS(gtype))
    {
      //find enumeration member
      GFlagsValue * flags_value = g_flags_get_value_by_nick(flags_class,dashed_name);
      g_value_init(dest,gtype);
      if(flags_value)
	{
	  g_value_set_flags(dest,flags_value->value);
	}
      else
	{
	  g_value_set_flags(dest,0);
	}
      done = TRUE;
    }
  else if(object_instance)
    {
      //find property
      if((property = g_object_class_find_property(object_class,name))||(property = g_object_class_find_property(object_class,dashed_name)))
	{
	  g_value_init(dest,property->value_type);
	  g_object_get_property(object_instance,property->name,dest);
	  done = TRUE;
	}
      else
	{
	  GValue * data_value = (GValue*)(g_object_get_data(object_instance,name));
	  if(!data_value)
	    {
	      data_value =  (GValue*)(g_object_get_data(object_instance,dashed_name));
	    }

	  if(data_value)
	    {
	      done = TRUE;
	      g_value_init(dest,G_VALUE_TYPE(data_value));
	      g_value_copy(data_value,dest);
	    }
	}
    }
  else
    {
      done = TRUE;
      g_value_init(dest,G_TYPE_POINTER);
      g_value_set_pointer(dest,NULL);
    }

  g_free(dashed_name);
  return done;
}

gboolean
golem_type_info_set(const GValue * instance,const gchar * name,const GValue * src,GError ** error)
{
  gboolean done = FALSE;
  gpointer object_instance = NULL;
  GObjectClass * klass = NULL;
  GParamSpec * property = NULL;
  gchar * dashed_name = g_strdup(name);

  //make dashed named property
  for(gchar * dn = dashed_name;*dn;dn++)
    {
      if(*dn == '_')
	*dn = '-';
    }

  if(G_VALUE_HOLDS_OBJECT(instance))
    {
      object_instance = g_value_get_object(instance);
      klass = G_OBJECT_GET_CLASS(object_instance);

      //find property
      if((property = g_object_class_find_property(klass,name))||(property = g_object_class_find_property(klass,dashed_name)))
      	{
	  g_object_set_property(object_instance,property->name,src);
	  done = TRUE;
      	}
      else
      	{
	  GValue * data_value = g_new0(GValue,1);
	  g_value_init(data_value,G_VALUE_TYPE(src));
	  g_value_copy(src,data_value);
	  g_object_set_data_full(object_instance,name,data_value,(GDestroyNotify)g_value_free);
	  done = TRUE;
      	}
     }
  g_free(dashed_name);
  return done;
}

GolemFunctionSpec *
golem_function_symbol_new(GolemClosureInfo * info,const gchar * symbol_name)
{
  GolemFunctionSpec * function = g_new0(GolemFunctionSpec,1);
  function->name = NULL;
  function->info = info;
  function->type = GOLEM_FUNCTION_SYMBOLIC;
  function->data.symbol_name = g_strdup(symbol_name);
  return function;
}

GolemFunctionSpec *
golem_function_virtual_new(GolemClosureInfo * info,goffset offset)
{
  GolemFunctionSpec * function = g_new0(GolemFunctionSpec,1);
  function->name = NULL;
  function->info = info;
  function->type = GOLEM_FUNCTION_VIRTUAL;
  function->data.offset = offset;
  return function;
}

GolemFunctionSpec *
golem_function_internal_new(GolemClosureInfo * info,GolemStatement * body)
{
  GolemFunctionSpec * function = g_new0(GolemFunctionSpec,1);
  function->name = NULL;
  function->info = info;
  function->type = GOLEM_FUNCTION_INTERNAL;
  function->data.body = body;
  return function;
}

GolemFunctionSpec *
golem_function_closured_new(const gchar * name,GolemClosureInvokeFunc func)
{
  GolemFunctionSpec * function = g_new0(GolemFunctionSpec,1);
  function->name = name;
  function->info = NULL;
  function->type = GOLEM_FUNCTION_CLOSURED;
  function->data.func = func;
  return function;
}

GolemTypeSpec *
golem_type_spec_new(const gchar * type_name)
{
  GolemTypeSpec * type_spec = g_new0(GolemTypeSpec,1);
  type_spec->type_name = g_strdup(type_name);
  type_spec->type = 0;
  type_spec->template_param_name = NULL;
  type_spec->template_param = 0;
  return type_spec;
}

GolemTypeSpec *
golem_type_spec_parse(GolemParser * parser,GError ** error)
{
  if(golem_parser_check_is_named(parser))
    {
      GolemTypeSpec * spec = g_new0(GolemTypeSpec,1);
      spec->type_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
      if(golem_parser_next_word_check(parser,"<"))
	{
	  spec->template_param_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
	  if(!golem_parser_next_word_check(parser,">"))
	    {
	      golem_parser_error(error,parser,"was expected \">\"");
	      g_free(spec->type_name);
	      g_free(spec->template_param_name);
	      g_free(spec);
	      spec = NULL;
	    }
	}
      return spec;
    }
  else
    {
      golem_parser_error(error,parser,"a type name was expected");
      return NULL;
    }
}

GType
golem_type_spec_get(GolemTypeSpec * type_spec,GolemContext * context,GError ** error)
{
  if(!type_spec->type)
    {
      type_spec->type = golem_context_get_type_define(context,type_spec->type_name,error);
    }
  return type_spec->type;
}

GolemPropertySpec *
golem_property_spec_new(GolemTypeSpec * type_spec,const gchar * property_name,GolemStatement * get,GolemStatement * set)
{
  GolemPropertySpec * spec = g_new0(GolemPropertySpec,1);
  spec->type_spec = type_spec;
  spec->property_name = g_strdup(property_name);
  spec->param_spec = NULL;
  spec->getter = get;
  spec->setter = set;
  return spec;
}
