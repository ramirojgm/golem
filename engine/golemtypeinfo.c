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
    * methods,
    * properties;

};

struct _GolemMethod
{
  GolemMethodType type;
  GolemClosureInfo * info;
  goffset offset;
  GCallback callback;
};

struct _GolemProperty {
  GParamSpec * param;
  GolemStatement * get;
  GolemStatement * set;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemTypeInfo,golem_type_info,G_TYPE_OBJECT)

static void
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

static void
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
}

static void
golem_type_info_init(GolemTypeInfo * info)
{
  GolemTypeInfoPrivate * priv = golem_type_info_get_instance_private(info);
  info->priv = priv;
  priv->init = NULL;
  priv->complete = NULL;
  priv->constructed = NULL;
  priv->dispose = NULL;
  priv->name = NULL;
  priv->methods = NULL;
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

gboolean
golem_type_info_register(GolemTypeInfo * type_info,GolemContext * context,GError ** error)
{

}

const gchar *
golem_type_info_get_name(GolemTypeInfo * type_info)
{
  return type_info->priv->name;
}

void
golem_type_info_set_name(GolemTypeInfo * type_info,const gchar * name)
{
  g_clear_pointer(&(type_info->priv->name),g_free);
  type_info->priv->name = g_strdup(name);
}

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

}

void
golem_type_info_add_method(GolemTypeInfo * type_info,GolemMethod * method)
{
  type_info->priv->methods = g_list_append(type_info->priv->methods,method);
}

void
golem_type_info_add_property(GolemTypeInfo * type_info,GolemProperty * property)
{
  type_info->priv->properties = g_list_append(type_info->priv->properties,property);
}

GolemMethod *
golem_type_info_get_method(GType type,const gchar * name,GType * type_container)
{
  GType parent_type = g_type_parent(type);
  GolemTypeInfo * type_info = golem_type_info_from_gtype(type);

  for(GList * method_iter = g_list_first(type_info->priv->methods);method_iter;method_iter = g_list_next(method_iter))
    {
      GolemMethod * method = (GolemMethod*)method_iter->data;
      if(g_strcmp0(golem_closure_info_get_name(method->info),name) == 0)
	{
	  if(type_container)
	    *type_container = type;
	  return method;
	}
    }

  GType * interfaces = g_type_interfaces(type,NULL);
  GolemMethod * interface_method = NULL;
  for(GType * itype = interfaces;*itype; itype += sizeof(GType))
    {
      if((interface_method = golem_type_info_get_method(*itype,name,type_container)))
	break;
    }
  g_free(interfaces);

  if(interface_method)
    return interface_method;
  else if((parent_type != G_TYPE_OBJECT) && parent_type)
    return golem_type_info_get_method(parent_type,name,type_container);
  else
    return NULL;
}

gboolean
golem_type_info_get_static(GType type,const gchar * name,GValue * dest,GError ** error)
{

}

gboolean
golem_type_info_get(gpointer instance,const gchar * name,GValue * dest,GError ** error)
{
  GType	gtype = G_TYPE_FROM_INSTANCE(instance);
  GType gtype_method = G_TYPE_NONE;
  GObjectClass * klass = G_OBJECT_GET_CLASS(instance);
  GolemMethod * method = NULL;
  GParamSpec *  property = NULL;

  gboolean done = FALSE;

  //Find method
  if((method = golem_type_info_get_method(gtype,name,&gtype_method)))
    {
      done = TRUE;
      gpointer callback = NULL;
      if(method->callback)
	{
	  callback = method->callback;
	}
      else
	{
	  GTypeQuery gtype_query = {0,};
	  GTypeQuery gtype_parent_query = {0,};
	  GType gtype_parent = g_type_parent(gtype_method);
	  gpointer * struct_method = NULL;

	  g_type_query(gtype_method,&gtype_query);

	  if(G_TYPE_IS_INTERFACE(gtype_method))
	    {
	      struct_method = g_type_interface_peek(instance,gtype_method);
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
	      struct_method = (gpointer)klass + gtype_offset;
	    }

	  if(gtype_query.class_size > method->offset)
	    {
	      callback = *((gpointer*)(struct_method + method->offset));
	    }
	  else
	    {
	      callback = NULL;
	      //TODO: bad offset
	    }
	}
      /*GolemClosure * symbol = golem_symbol_instanced_new(method->info,(gpointer)callback,(gpointer)instance);
      g_value_init(dest,G_TYPE_CLOSURE);
      g_value_set_boxed(dest,symbol);*/
    }
  //Find property
  else if((property = g_object_class_find_property(klass,name)))
    {
      done = TRUE;

    }
  //Find data
  else
    {

    }
  return done;
}

gboolean
golem_type_info_set(gpointer instance,const gchar * name,const GValue * src,GError ** error)
{

}

GolemProperty *
golem_property_new(GParamSpec * property,GolemStatement *  get,GolemStatement * set)
{

}

void
golem_property_free(GolemProperty *  property)
{

}

GolemMethod *
golem_method_new(GolemMethodType type,GolemClosureInfo * info,GCallback callback,goffset offset)
{
  GolemMethod * method = g_new0(GolemMethod,1);
  method->type = type;
  method->info = info;
  method->offset = offset;
  method->callback = callback;
  return method;
}

void
golem_method_free(GolemMethod * method)
{

}
