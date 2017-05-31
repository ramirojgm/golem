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

static GList *	_golem_type_info = NULL;
GMutex 		_golem_type_info_mutex = G_STATIC_MUTEX_INIT;

struct _GolemTypeInfoPrivate {
  gchar * name;
  GType   gtype;

  GolemContext
    * define_context;

  GolemStatement
    * init,
    * constructed,
    * dispose,
    * finalize,
    * parse;

  GList
    * functions,
    * properties;

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

G_DEFINE_TYPE_WITH_PRIVATE(GolemTypeInfo,golem_type_info,G_TYPE_OBJECT)

/*static void
golem_instance_generic_dispose(GObject * instance)
{

}

static void
golem_instance_generic_finalize(GObject * instance)
{

}

static void
golem_instance_generic_init(GObject * instance)
{

}

static void
golem_instance_generic_constructed(GObject * instance)
{

}

static void
golem_instance_generic_set_property(GObject        *object,
                                    guint           property_id,
                                    const GValue   *value,
                                    GParamSpec     *pspec)
{
  GolemTypeInfo *  info = GOLEM_TYPE_INFO(g_object_get_data(object,"_type_info_"));

}
*/
/*static void
golem_instance_generic_get_property(GObject        *object,
                                    guint           property_id,
                                    GValue         *value,
                                    GParamSpec     *pspec)
{
  GolemTypeInfo *  info = GOLEM_TYPE_INFO(g_object_get_data(object,"_type_info_"));
  GObject * priv = G_OBJECT(g_object_get_data(object,"_priv_"));
  for(GList * prop_iter = g_list_first(info->priv->properties);prop_iter;prop_iter = g_list_next(prop_iter))
    {
      GolemProperty * prop = (GolemProperty*)(prop_iter->data);
      if(prop->param == pspec)
	{
	  GolemContext * context = golem_context_new(info->priv->define_context);
	  GValue priv_value = G_VALUE_INIT;
	  g_value_init(&priv_value,G_TYPE_OBJECT);
	  g_value_set_object(&priv_value,priv);
	  golem_context_set_auto(context,"priv",&priv_value,NULL);
	  g_value_unset(&priv_value);

	  g_object_unref(context);
	  return;
	}
    }
}

static void
golem_instance_generic_class_init(GObjectClass * klass)
{
  klass->constructed = golem_instance_generic_constructed;
  klass->finalize = golem_instance_generic_finalize;
  klass->dispose = golem_instance_generic_dispose;
  klass->set_property = golem_instance_generic_set_property;
  klass->get_property = golem_instance_generic_get_property;
}*/

static void
golem_type_info_init(GolemTypeInfo * info)
{
  GolemTypeInfoPrivate * priv = golem_type_info_get_instance_private(info);
  info->priv = priv;
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
golem_type_info_class_init(GolemTypeInfoClass * info)
{

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


const gchar *
golem_type_info_get_name(GolemTypeInfo * type_info)
{
  return type_info->priv->name;
}

/*
void
golem_type_info_set_init(GolemTypeInfo * type_info,GolemStatement * statement)
{

}

GolemStatement*
golem_type_info_get_init(GolemTypeInfo * type_info)
{

}

GolemStatement *
golem_type_info_get_complete(GolemTypeInfo * type_info)
{

}

void
golem_type_info_set_complete(GolemTypeInfo * type_info,GolemStatement * statement)
{

}

void
golem_type_info_set_constructed(GolemTypeInfo * type_info,GolemStatement * statement)
{

}

GolemStatement*
golem_type_info_get_constructed(GolemTypeInfo * type_info)
{

}

void
golem_type_info_set_dispose(GolemTypeInfo * type_info,GolemStatement * statement)
{

}

GolemStatement*
golem_type_info_get_dispose(GolemTypeInfo * type_info)
{

}*/

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
_golem_closure_attached_finalize(GolemClosure * closure,gpointer data)
{
  g_object_unref(data);
}

gboolean
golem_type_info_get(gpointer instance,const gchar * name,GValue * dest,GError ** error)
{
  GType	gtype = G_TYPE_FROM_INSTANCE(instance);
  GType gtype_function = G_TYPE_NONE;
  GObjectClass * klass = G_OBJECT_GET_CLASS(instance);
  GolemFunctionSpec * function = NULL;
  GParamSpec *  property = NULL;
  GolemClosure * closure = NULL;

  gboolean done = FALSE;

  //find function
  if((function = _golem_type_info_find_function(gtype,name,&gtype_function)))
    {
      done = TRUE;
      if(function->type == GOLEM_FUNCTION_SYMBOLIC)
	{
	  gpointer symbol = NULL;
	  GModule * global = g_module_open(NULL,G_MODULE_BIND_LOCAL);
	  g_module_symbol(global,function->data.symbol_name,&symbol);
	  g_module_close(global);
	  closure = golem_symbol_new(function->info,symbol);
	  golem_closure_set_instance(closure,instance);
	  g_value_init(dest,G_TYPE_CLOSURE);
	  g_value_set_boxed(dest,closure);
	  g_closure_unref(G_CLOSURE(closure));
	  g_print("%s:%p\n",function->data.symbol_name,symbol);
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
	      struct_function = g_type_interface_peek(instance,gtype_function);
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
	      golem_closure_set_instance(closure,instance);
	      g_value_init(dest,G_TYPE_CLOSURE);
	      g_value_set_boxed(dest,closure);
	      g_closure_unref(G_CLOSURE(closure));
	    }
	}
      else if(function->type == GOLEM_FUNCTION_INTERNAL)
	{
	  GolemContext * context = g_object_get_data(instance,"_this_context_");
	  if(!context)
	    {
	      GolemTypeInfo * type_info = golem_type_info_from_gtype(gtype);
	      context = golem_context_new(type_info->priv->define_context);
	      golem_context_set_instance(context,instance);
	      g_object_set_data_full(instance,"_this_context_",g_object_ref(context),g_object_unref);
	    }
	  closure = golem_function_new(function->info,context,function->data.body);
	  g_value_init(dest,G_TYPE_CLOSURE);
	  g_value_set_boxed(dest,closure);
	  g_closure_unref(G_CLOSURE(closure));
	}
      else if(function->type == GOLEM_FUNCTION_CLOSURED)
	{
	  closure = golem_closure_new(function->data.func,_golem_closure_attached_finalize,g_object_ref(instance));
	  g_value_init(dest,G_TYPE_CLOSURE);
	  g_value_set_boxed(dest,closure);
	  g_closure_unref(G_CLOSURE(closure));
	}
    }

  //find property
  else if((property = g_object_class_find_property(klass,name)))
    {
      done = TRUE;
      GParamSpec * property = g_object_class_find_property(klass,name);
      if(property)
	{
	  g_value_init(dest,property->value_type);
	  g_object_get_property(instance,name,dest);
	  return TRUE;
	}
    }
  //find data
  else
    {
      g_value_init(dest,G_TYPE_INT);
      g_value_set_int(dest,0);
    }
  g_print("%s\n",name);
  return done;
}

gboolean
golem_type_info_set(gpointer instance,const gchar * name,const GValue * src,GError ** error)
{

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
