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
  GParamSpec * param;
  GolemStatement * get;
  GolemStatement * set;
};

struct _GolemPrivateInstance
{
  gpointer priv_instance;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemTypeInfo,golem_type_info,G_TYPE_OBJECT)

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

static gpointer
_golem_object_get_instance_private(GolemTypeInfo * info,gpointer instance)
{
  GolemPrivateInstance * priv = (GolemPrivateInstance *)(instance + info->priv->private_offset);
  return priv->priv_instance;
}

static void
_golem_object_init(GTypeInstance * instance, gpointer klass)
{
  GolemTypeInfo * info = golem_type_info_from_gtype(G_TYPE_FROM_INSTANCE(instance));
  if(info)
    {
      GolemPrivateInstance * priv = (GolemPrivateInstance *)(instance + info->priv->private_offset);
      priv->priv_instance = g_object_new(G_TYPE_OBJECT,NULL);
      if(info->priv->init)
	{
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,G_TYPE_FROM_INSTANCE(instance));
	  g_value_init(&priv_value,G_TYPE_OBJECT);
	  g_value_set_object(&this_value,instance);
	  g_value_set_object(&priv_value,priv->priv_instance);
	  GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  golem_statement_execute(info->priv->init,runtime,NULL);
	  golem_runtime_exit(runtime);
	  g_value_unset(&this_value);
	  g_value_unset(&priv_value);
	}
    }
}

static void
_golem_object_constructed(GObject * instance)
{
  GolemTypeInfo * info = golem_type_info_from_gtype(G_TYPE_FROM_INSTANCE(instance));
  if(info)
    {
      gpointer * priv = _golem_object_get_instance_private(info,instance);
      if(info->priv->constructed)
	{
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,G_TYPE_FROM_INSTANCE(instance));
	  g_value_init(&priv_value,G_TYPE_OBJECT);
	  g_value_set_object(&this_value,instance);
	  g_value_set_object(&priv_value,priv);
	  GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  golem_statement_execute(info->priv->constructed,runtime,NULL);
	  golem_runtime_exit(runtime);
	  g_value_unset(&this_value);
	  g_value_unset(&priv_value);
	}
    }
}

static void
_golem_object_run_dispose(GType type,GObject * instance)
{
  GolemTypeInfo * info = golem_type_info_from_gtype(type);

  if(info)
    {
      gpointer * priv = _golem_object_get_instance_private(info,instance);
      if(info->priv->dispose)
	{
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,G_TYPE_FROM_INSTANCE(instance));
	  g_value_init(&priv_value,G_TYPE_OBJECT);
	  g_value_set_object(&this_value,instance);
	  g_value_set_object(&priv_value,priv);
	  GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  golem_statement_execute(info->priv->dispose,runtime,NULL);
	  golem_runtime_exit(runtime);
	  g_value_unset(&this_value);
	  g_value_unset(&priv_value);
	}
      g_object_unref(priv);
    }
}

static void
_golem_object_dispose(GObject * instance)
{
  GolemTypeInfo * info = golem_type_info_from_gtype(0);
  if(info)
    {
      gpointer * priv = _golem_object_get_instance_private(info,instance);
      if(info->priv->dispose)
	{
	  GValue this_value = G_VALUE_INIT;
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&this_value,G_TYPE_FROM_INSTANCE(instance));
	  g_value_init(&priv_value,G_TYPE_OBJECT);
	  g_value_set_object(&this_value,instance);
	  g_value_set_object(&priv_value,priv);
	  GolemRuntime * runtime = golem_runtime_new(info->priv->define_context);
	  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"this",&this_value,NULL);
	  golem_context_set_auto(golem_runtime_get_context(runtime),"priv",&priv_value,NULL);
	  golem_statement_execute(info->priv->dispose,runtime,NULL);
	  golem_runtime_exit(runtime);
	  g_value_unset(&this_value);
	  g_value_unset(&priv_value);
	}
      g_object_unref(priv);
    }
}

static void
_golem_object_class_init(gpointer klass,gpointer klass_data)
{
  G_OBJECT_CLASS(klass)->dispose = _golem_object_dispose;
  G_OBJECT_CLASS(klass)->constructed = _golem_object_constructed;
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
				 g_intern_static_string(info->priv->name),
				 parent_query.class_size + sizeof(gpointer),
				 _golem_object_class_init,
				 parent_query.instance_size + sizeof(gpointer),
				 _golem_object_init,
				 0);
  info->priv->private_offset = g_type_add_instance_private(info->priv->gtype,sizeof(GolemPrivateInstance));
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

gboolean
golem_type_info_get_classed(GType type,const gchar * name,GValue * dest,GError ** error)
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
  GType	gtype = G_VALUE_TYPE(instance);
  GolemTypeInfo * type_info = golem_type_info_from_gtype(gtype);
  GType gtype_function = G_TYPE_NONE;
  gpointer object_instance = NULL;
  GObjectClass * klass = NULL;
  GolemFunctionSpec * function = NULL;
  GParamSpec *  property = NULL;
  GolemClosure * closure = NULL;
  gboolean done = FALSE;
  gchar * dashed_name = g_strdup(name);

  if(G_VALUE_HOLDS_OBJECT(instance))
    {
      object_instance = g_value_get_object(instance);
      klass = G_OBJECT_GET_CLASS(object_instance);
    }

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
		  struct_function = (gpointer)klass + gtype_offset;
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

	      GolemContext * context = NULL;
	      if(object_instance)
		{
		  context = GOLEM_CONTEXT(g_object_get_data(object_instance,"_ctx_"));
		  if(!context)
		    {
		      context = golem_context_new(type_info->priv->define_context);
		      golem_context_set_this(context,instance);
		      g_object_set_data_full(object_instance,"_ctx_",g_object_ref(context),g_object_unref);
		    }
		}
	      else
		{
		  context = golem_context_new(type_info->priv->define_context);
		  golem_context_set_this(context,instance);

		}

	      closure = golem_function_new(function->info,context,function->data.body);
	      golem_closure_set_this(closure,instance);
	      g_value_init(dest,G_TYPE_CLOSURE);
	      g_value_set_boxed(dest,closure);
	      g_closure_unref(G_CLOSURE(closure));
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
  else if(object_instance)
    {
      //find property
      if((property = g_object_class_find_property(klass,name))||(property = g_object_class_find_property(klass,dashed_name)))
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
