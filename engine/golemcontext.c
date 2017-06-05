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
#include "gmodule.h"
#include <ctype.h>
#include <string.h>

typedef struct _GolemContextPrivate GolemContextPrivate;
typedef struct _GolemContextVariable GolemContextVariable;

struct _GolemContextPrivate
{
  GolemContext * parent;
  GObject * instance;
  GList * variables;
};

struct _GolemContextVariable{
  gchar * name;
  GType type;
  GValue value;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemContext,golem_context,G_TYPE_OBJECT)

static void
golem_context_variable_free(GolemContextVariable * variable)
{
  g_free(variable->name);
  g_value_unset(&(variable->value));
  g_free(variable);
}

static void
golem_context_dispose(GObject * object)
{
  GolemContextPrivate * priv;
  priv = golem_context_get_instance_private(GOLEM_CONTEXT(object));
  g_clear_object(&(priv->instance));
  g_list_free_full(priv->variables,(GDestroyNotify)golem_context_variable_free);
  G_OBJECT_CLASS(golem_context_parent_class)->dispose(object);
  g_mutex_clear(&(GOLEM_CONTEXT(object)->mutex));
}

static void
golem_context_init(GolemContext * self)
{
  GolemContextPrivate * priv;
  priv = golem_context_get_instance_private(self);
  priv->parent = NULL;
  priv->instance = NULL;
  priv->variables = NULL;
  g_mutex_init(&(self->mutex));
}

static void
golem_context_class_init(GolemContextClass * klass)
{
  G_OBJECT_CLASS(klass)->dispose = golem_context_dispose;
}

gboolean
golem_context_set_auto(GolemContext * context,const gchar * name,GValue *  value,GError ** error)
{
  if(golem_context_declare(context,name,G_VALUE_TYPE(value),error))
    {
      return golem_context_set(context,name,value,error);
    }
  else
    {
      return FALSE;
    }
}

void
golem_context_add_function(GolemContext * context,const gchar * name,GolemClosure * closure)
{
  GValue func_value = G_VALUE_INIT;
  g_value_init(&func_value,GOLEM_TYPE_CLOSURE);
  g_value_set_boxed(&func_value,closure);
  golem_context_set_auto(context,name,&func_value,NULL);
  g_value_unset(&func_value);
}


gboolean
golem_context_set(GolemContext * context,const gchar * name,GValue * value,GError ** error)
{
  if(!context)
    return FALSE;
  g_mutex_lock(&(context->mutex));

  GolemContextPrivate * priv;
  priv = golem_context_get_instance_private(context);

  for(GList * iter = g_list_first(priv->variables);iter;iter = g_list_next(iter))
    {
      GolemContextVariable * variable = (GolemContextVariable *)(iter->data);
      if(g_strcmp0(name,variable->name) == 0)
	{
	  if((variable->type == G_TYPE_VALUE)||(variable->value.g_type == value->g_type))
	    {
	      g_value_unset(&(variable->value));
	      g_value_init(&(variable->value),value->g_type);
	      g_value_copy(value,&(variable->value));
	      g_mutex_unlock(&(context->mutex));
	      return TRUE;
	    }
	  else if(g_value_type_transformable(value->g_type,variable->type))
	    {
	      g_value_unset(&(variable->value));
	      g_value_init(&(variable->value),variable->type);
	      g_value_transform(value, &(variable->value));
	      g_mutex_unlock(&(context->mutex));
	      return TRUE;
	    }
	  else
	    {
	      golem_runtime_error(error,
			  GOLEM_INVALID_CAST_ERROR,
			  "invalid cast from type \"%s\" to type \"%s\"",
			  g_type_name(value->g_type),
			  g_type_name(variable->value.g_type));
	      g_mutex_unlock(&(context->mutex));
	      return FALSE;
	    }
	}
    }

  if(priv->instance)
    {
      GObjectClass * klass = G_OBJECT_GET_CLASS(priv->instance);
      GParamSpec * property = g_object_class_find_property(klass,name);
      if(property)
	{
	  if(value->g_type == property->value_type)
	    {
	      g_object_set_property(priv->instance,name,value);
	      g_mutex_unlock(&(context->mutex));
	      return TRUE;
	    }
	  else if(g_value_type_transformable(value->g_type,property->value_type))
	    {
	      GValue property_value = G_VALUE_INIT;
	      g_value_init(&property_value,property->value_type);
	      g_value_transform(value,&property_value);
	      g_object_set_property(priv->instance,name,&property_value);
	      g_value_unset(&property_value);
	      g_mutex_unlock(&(context->mutex));
	      return TRUE;
	    }
	  else
	    {
	      golem_runtime_error(error,
			  GOLEM_INVALID_CAST_ERROR,
			  "invalid cast from type \"%s\" to type \"%s\"",
			  g_type_name(value->g_type),
			  g_type_name(property->value_type));
	      g_mutex_unlock(&(context->mutex));
	      return FALSE;
	    }
	}
    }

  if(priv->parent)
    {
      g_mutex_unlock(&(context->mutex));
      return golem_context_set(priv->parent,name,value,error);
    }
  else
    {
      golem_runtime_error(error,
      		    GOLEM_NOT_EXISTS_ERROR,
      		    "the variable \"%s\" not exists",
      		    name
      );
      g_mutex_unlock(&(context->mutex));
      return FALSE;
    }
}

gboolean
golem_context_declare(GolemContext * context,const gchar * name,GType type,GError ** error)
{
  g_mutex_lock(&(context->mutex));
  GolemContextPrivate * priv;
  GolemContextVariable * variable;
  priv = golem_context_get_instance_private(context);
  for(GList * iter = g_list_first(priv->variables);iter;iter = g_list_next(iter))
    {
      GolemContextVariable * variable = (GolemContextVariable *)(iter->data);
      if(g_strcmp0(name,variable->name) == 0)
	{
	  golem_runtime_error(error,
		      GOLEM_ALREADY_EXISTS_ERROR,
		      "the variable \"%s\" already exists",
		      name
	  );
	  g_mutex_unlock(&(context->mutex));
	  return FALSE;
	}
    }

  variable = g_new0(GolemContextVariable,1);
  variable->name = g_strdup(name);
  variable->type = type;
  g_value_unset(&(variable->value));
  g_value_init(&(variable->value),type);
  priv->variables = g_list_append(priv->variables,variable);
  g_mutex_unlock(&(context->mutex));
  return TRUE;
}

static GType
golem_context_get_type_from_name(const gchar * name)
{
#ifdef GOLEM_TYPE_IMPORT
   if(g_strcmp0(name,"void") == 0)
     return G_TYPE_NONE;
   else if(g_strcmp0(name,"var") == 0)
     return G_TYPE_VALUE;
   else if(g_strcmp0(name,"bool") == 0)
       return G_TYPE_BOOLEAN;
   else if(g_strcmp0(name,"string") == 0)
     return G_TYPE_STRING;
   else if(g_strcmp0(name,"byte") == 0 || g_strcmp0(name,"char") == 0)
     return G_TYPE_CHAR;
   else if(g_strcmp0(name,"int") == 0)
     return G_TYPE_INT;
   else if(g_strcmp0(name,"long") == 0)
     return G_TYPE_LONG;
   else if(g_strcmp0(name,"ubyte") == 0 || g_strcmp0(name,"uchar") == 0)
       return G_TYPE_UCHAR;
   else if(g_strcmp0(name,"uint") == 0)
     return G_TYPE_UINT;
   else if(g_strcmp0(name,"ulong") == 0)
     return G_TYPE_ULONG;
   else if(g_strcmp0(name,"pointer") == 0)
     return G_TYPE_POINTER;
   else if(g_strcmp0(name,"float") == 0)
       return G_TYPE_FLOAT;
   else if(g_strcmp0(name,"double") == 0)
       return G_TYPE_DOUBLE;
   else if(g_strcmp0(name,"function") == 0)
       return GOLEM_TYPE_CLOSURE;
   else if(g_strcmp0(name,"object") == 0)
       return G_TYPE_OBJECT;
   else if(g_strcmp0(name,"array") == 0)
         return G_TYPE_ARRAY;
   else
     {
       GType type = g_type_from_name(name);
       static gchar type_named[256] = {0,};
       memset(type_named,0,256);
       if(type == 0)
       	{
       	  GModule * module = g_module_open(NULL,0);
       	  guint type_named_index = 0;
       	  for(const gchar * iter = name;*iter;iter ++)
       	    {
       	      if(isupper(*iter) && (iter != name))
       		{
       		  type_named[type_named_index] = '_';
       		  type_named_index++;

       		}
       	      type_named[type_named_index] = tolower(*iter);
       	      type_named_index++;
       	    }
       	  strcat(type_named,"_get_type");
       	  GType (*get_type)() = 0;
       	  g_module_symbol(module,type_named,(gpointer*)&get_type);
       	  if(get_type)
       	    type = get_type();
       	  else
       	    type = 0;
       	  g_module_close(module);
       	}
       return type;
     }
#else
  return 0;
#endif
}

GType
golem_context_get_type_define( GolemContext * context,const gchar * name,GError ** error)
{
  GValue type_value = G_VALUE_INIT;
  GType result = 0;
  golem_context_get(context,name,&type_value,error);
  if(G_VALUE_HOLDS_GTYPE(&type_value))
    {
      result = g_value_get_gtype(&type_value);
    }
  g_value_unset(&type_value);
  return result;
}


gboolean
golem_context_get(GolemContext * context,const gchar * name, GValue * value,GError ** error)
{
  //Check for type
  GType type = golem_context_get_type_from_name(name);
  if(type)
    {
      g_value_init(value,G_TYPE_GTYPE);
      g_value_set_gtype(value,type);
      return TRUE;
    }

  g_mutex_lock(&(context->mutex));
  GolemContextPrivate * priv;
  GolemContextVariable * variable;

  priv = golem_context_get_instance_private(context);
  for(GList * iter = g_list_first(priv->variables);iter;iter = g_list_next(iter))
    {
      variable = (GolemContextVariable *)(iter->data);
      if(g_strcmp0(name,variable->name) == 0)
	{
	  g_value_unset(value);
	  g_value_init(value,variable->type);
	  g_value_copy(&(variable->value),value);
	  g_mutex_unlock(&(context->mutex));
	  return TRUE;
	}
    }

  if(priv->instance)
      {
	if(g_strcmp0(name,"this") == 0)
	  {
	    g_value_unset(value);
	    g_value_init(value,G_TYPE_FROM_INSTANCE(priv->instance));
	    g_value_set_object(value,priv->instance);
	    return TRUE;
	  }
	else
	  {
	    GObjectClass * klass = G_OBJECT_GET_CLASS(priv->instance);
	    GParamSpec * property = g_object_class_find_property(klass,name);
	    if(property)
	      {
		g_value_unset(value);
		g_value_init(value,property->value_type);
		g_object_get_property(priv->instance,name,value);
		g_mutex_unlock(&(context->mutex));
		return TRUE;
	      }
	  }
      }

    if(priv->parent)
      {
	g_mutex_unlock(&(context->mutex));
        return golem_context_get(priv->parent,name,value,error);
      }
    else
      {
	golem_runtime_error(error,
		    GOLEM_NOT_EXISTS_ERROR,
		    "\"%s\" is undefined",
		    name
	);
	g_mutex_unlock(&(context->mutex));
        return FALSE;
      }
}

GolemContext *
golem_context_new(GolemContext * parent)
{
  GolemContext * self = GOLEM_CONTEXT(g_object_new(GOLEM_TYPE_CONTEXT,NULL));
  GolemContextPrivate * priv = golem_context_get_instance_private(self);
  if(parent)
    {
      priv->parent = GOLEM_CONTEXT(g_object_ref(parent));
    }
  return self;
}

void
golem_context_set_instance(GolemContext * context,GObject * instance)
{
  GolemContextPrivate * priv = golem_context_get_instance_private(context);
  if(priv->instance)
    g_object_unref(priv->instance);
  priv->instance = instance;
}
