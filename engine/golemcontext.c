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

typedef struct _GolemContextPrivate GolemContextPrivate;
typedef struct _GolemContextVariable GolemContextVariable;

struct _GolemContextPrivate
{
  GolemContext * parent;
  GValue this_value;
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
  if(GOLEM_CONTEXT(object)->is_disposed)
    {
      GolemContextPrivate * priv;
      priv = golem_context_get_instance_private(GOLEM_CONTEXT(object));
      if(priv->this_value.g_type)
	  g_value_unset(&priv->this_value);
      g_list_free_full(priv->variables,(GDestroyNotify)golem_context_variable_free);
      G_OBJECT_CLASS(golem_context_parent_class)->dispose(object);
      if(priv->parent)
	  g_object_unref(priv->parent);
      g_mutex_clear(&(GOLEM_CONTEXT(object)->mutex));
      GOLEM_CONTEXT(object)->is_disposed = TRUE;
    }
}

static void
golem_context_init(GolemContext * self)
{
  GolemContextPrivate * priv;
  priv = golem_context_get_instance_private(self);
  priv->parent = NULL;
  priv->variables = NULL;
  self->is_disposed = FALSE;
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

gboolean
golem_context_get(GolemContext * context,const gchar * name, GValue * value,GError ** error)
{
  //Check for type
  GType type = golem_type_from_name(name);
  if(type)
    {
      g_value_init(value,G_TYPE_GTYPE);
      g_value_set_gtype(value,type);
      return TRUE;
    }
  else if(g_strcmp0(name,"true") == 0)
    {
      g_value_init(value,G_TYPE_BOOLEAN);
      g_value_set_boolean(value,TRUE);
      return TRUE;
    }
  else if(g_strcmp0(name,"false") == 0)
    {
      g_value_init(value,G_TYPE_BOOLEAN);
      g_value_set_boolean(value,FALSE);
      return TRUE;
    }
  else if(g_strcmp0(name,"null") == 0)
    {
      g_value_init(value,G_TYPE_POINTER);
      g_value_set_pointer(value,NULL);
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
	  g_value_init(value,G_VALUE_TYPE(&variable->value));
	  g_value_copy(&(variable->value),value);
	  g_mutex_unlock(&(context->mutex));
	  return TRUE;
	}
    }


  if(priv->this_value.g_type)
      {
	if(g_strcmp0(name,"this") == 0)
	  {
	    g_mutex_unlock(&(context->mutex));
	    g_value_unset(value);
	    g_value_init(value,G_VALUE_TYPE(&priv->this_value));
	    g_value_copy(&priv->this_value,value);
	    return TRUE;
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
golem_context_set_this(GolemContext * context,const GValue * instance)
{
  GolemContextPrivate * priv = golem_context_get_instance_private(context);
  if(priv->this_value.g_type)
    g_value_unset(&priv->this_value);
  g_value_init(&priv->this_value,G_VALUE_TYPE(instance));
  g_value_copy(instance,&priv->this_value);
}

gpointer
golem_context_address_of(GolemContext * context,const gchar * name,GError ** error)
{
  g_mutex_lock(&(context->mutex));
  GolemContextPrivate * priv;
  GolemContextVariable * variable;

  priv = golem_context_get_instance_private(context);
  for(GList * iter = g_list_first(priv->variables);iter;iter = g_list_next(iter))
    {
      variable = (GolemContextVariable *)(iter->data);
      if(g_strcmp0(name,variable->name) == 0)
	{
	  gpointer result = NULL;
	  if(variable->type == G_TYPE_VALUE)
	      result = &(variable->value);
	  else
	      result = &(variable->value.data[0].v_pointer);
	  g_mutex_unlock(&(context->mutex));
	  return result;
	}
    }


  if(priv->this_value.g_type)
      {
	if(g_strcmp0(name,"this") == 0)
	  {
	    g_mutex_unlock(&(context->mutex));
	    return &(priv->this_value.data[0].v_pointer);
	  }
      }

    if(priv->parent)
      {
	g_mutex_unlock(&(context->mutex));
        return golem_context_address_of(priv->parent,name,error);
      }
    else
      {
	golem_runtime_error(error,
		    GOLEM_NOT_EXISTS_ERROR,
		    "\"%s\" is undefined",
		    name
	);
	g_mutex_unlock(&(context->mutex));
        return NULL;
      }
}
