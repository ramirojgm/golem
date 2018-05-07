/*
	Copyright (C) 2018 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../golem.h"

struct _GolemScopeBuilderPrivate
{
  GList * scopes;
};

typedef struct
{
  GolemVMBody * m_body;
  GList * 	m_def;
  guint32	n_index;
  guint32	n_offset;
  guint32	n_size;
} GolemScopeInfo;

typedef struct
{
  GType n_type;
  gchar * m_name;
  guint32 n_offset;
  guint8 n_size;
} GolemScopeDefineInfo;

G_DEFINE_TYPE_WITH_PRIVATE(GolemScopeBuilder,golem_scope_builder,G_TYPE_OBJECT)

static void
golem_scope_builder_init(GolemScopeBuilder * self)
{
  self->priv = golem_scope_builder_get_instance_private(self);
  self->priv->scopes = NULL;
}

static void
golem_scope_builder_class_init(GolemScopeBuilderClass * klass)
{

}


GolemScopeBuilder *
golem_scope_builder_new()
{
  return GOLEM_SCOPE_BUILDER(g_object_new(GOLEM_TYPE_SCOPE_BUILDER,NULL));
}

gboolean
golem_scope_builder_define(GolemScopeBuilder * scope,
			   GType type,
			   const gchar * name,
			   GError ** error)
{
  g_return_val_if_fail(type != G_TYPE_NONE,FALSE);

  if(scope->priv->scopes)
    {
      GolemScopeInfo * scope_info = (GolemScopeInfo*)g_list_last(scope->priv->scopes)->data;

      //Check not exists
      for(GList * def_iter = g_list_first(scope_info->m_def); def_iter; def_iter = def_iter->next)
	{
	  GolemScopeDefineInfo * def = (GolemScopeDefineInfo *) def_iter->data;
	  if(g_strcmp0(def->m_name,name) == 0)
	    {
	      g_propagate_error(error,g_error_new(
	      	  g_quark_from_static_string("golem-error"),
	      	  1,
	      	  "the variable \"%s\" already exists",
		  name));
	      return FALSE;
	    }
	}

      //New definition
      GolemScopeDefineInfo * def = g_new(GolemScopeDefineInfo,1);
      def->m_name = g_strdup(name);
      def->n_type = type;
      def->n_offset = scope_info->n_size;
      switch(type)
      {
	case G_TYPE_CHAR:
	case G_TYPE_UCHAR:
	  def->n_size = sizeof(gint8);
	  break;
	case G_TYPE_INT16:
	case G_TYPE_UINT16:
	  def->n_size = sizeof(gint16);
	  break;
	case G_TYPE_INT:
	case G_TYPE_UINT:
	case G_TYPE_FLOAT:
	  def->n_size = sizeof(gint32);
	  break;
	case G_TYPE_INT64:
	case G_TYPE_UINT64:
	case G_TYPE_LONG:
	case G_TYPE_ULONG:
	case G_TYPE_DOUBLE:
	  def->n_size = sizeof(gint64);
	  break;
	case G_TYPE_POINTER:
	case G_TYPE_OBJECT:
	case G_TYPE_STRING:
	case G_TYPE_BOXED:
	  def->n_size = sizeof(gpointer);
	  break;
	default:
	  def->n_size = 0;
      }
      scope_info->n_size += def->n_size;
      scope_info->m_def = g_list_append(scope_info->m_def,def);
      golem_vm_body_update_op32(scope_info->m_body,
				scope_info->n_offset,
				scope_info->n_size);
    }
  else
    {
      g_propagate_error(error,g_error_new(
	  g_quark_from_static_string("golem-error"),
	  0,
	  "no scope allow"));
      return FALSE;
    }
  return TRUE;
}

gboolean
golem_scope_builder_argument(GolemScopeBuilder * scope,
			     GType type,
			     const gchar * name,
			     GError ** error)
{
  g_return_val_if_fail(type != G_TYPE_NONE,FALSE);
  gboolean done = FALSE;
  if(scope->priv->scopes)
    {
      GolemScopeInfo * scope_info = (GolemScopeInfo*)g_list_last(scope->priv->scopes)->data;
      done = golem_scope_builder_define(scope,type,name,error);
      if(done)
	{
	  golem_vm_body_write_op16(scope_info->m_body,GOLEM_OP_RA,type);
	  golem_scope_builder_set(scope,name,error);
	}
    }
  return done;
}

GType
golem_scope_builder_type(GolemScopeBuilder * scope,
			 const gchar * name)
{
  for(GList * scope_iter = g_list_first(scope->priv->scopes);
      scope_iter;
      scope_iter = g_list_next(scope_iter))
    {
      GolemScopeInfo * scope_info = (GolemScopeInfo*) scope_iter->data;
      for(GList * def_iter = g_list_first(scope_info->m_def);
	  def_iter;
	  def_iter = g_list_next(def_iter))
	{
	  GolemScopeDefineInfo * def_info = (GolemScopeDefineInfo*)def_iter->data;
	  if(g_strcmp0(def_info->m_name,name) == 0)
	    return def_info->n_type;
	}
    }
  return G_TYPE_INVALID;
}

gboolean
golem_scope_builder_enter(GolemScopeBuilder * scope,
			  GolemVMBody * body,
			  GError ** error)
{
  GolemScopeInfo * info = g_new(GolemScopeInfo,1);
  info->m_body = body;
  info->m_def = NULL;
  info->n_size = 0;
  info->n_index = g_list_length(scope->priv->scopes);
  info->n_offset = golem_vm_body_get_offset(body);
  golem_vm_body_write_op32(body,GOLEM_OP_SE,0);
  scope->priv->scopes = g_list_append(scope->priv->scopes,info);
  return TRUE;
}

gboolean
golem_scope_builder_get(GolemScopeBuilder * scope,
			const gchar * name,
			GError ** error)
{
  for(GList * scope_iter = g_list_first(scope->priv->scopes);
       scope_iter;
       scope_iter = g_list_next(scope_iter))
     {
       GolemScopeInfo * scope_info = (GolemScopeInfo*) scope_iter->data;
       for(GList * def_iter = g_list_first(scope_info->m_def);
 	  def_iter;
 	  def_iter = g_list_next(def_iter))
 	{
 	  GolemScopeDefineInfo * def_info = (GolemScopeDefineInfo*)def_iter->data;
 	  if(g_strcmp0(def_info->m_name,name) == 0)
 	    {
 	      golem_vm_body_write_ops(scope_info->m_body,
				      GOLEM_OP_PP,
				      scope_info->n_index,
				      def_info->n_offset,
				      def_info->n_size);
 	      return TRUE;
 	    }
 	}
     }
   return FALSE;
}

gboolean
golem_scope_builder_set(GolemScopeBuilder * scope,
			const gchar * name,
			GError ** error)
{
  for(GList * scope_iter = g_list_first(scope->priv->scopes);
       scope_iter;
       scope_iter = g_list_next(scope_iter))
     {
       GolemScopeInfo * scope_info = (GolemScopeInfo*) scope_iter->data;
       for(GList * def_iter = g_list_first(scope_info->m_def);
 	  def_iter;
 	  def_iter = g_list_next(def_iter))
 	{
 	  GolemScopeDefineInfo * def_info = (GolemScopeDefineInfo*)def_iter->data;
 	  if(g_strcmp0(def_info->m_name,name) == 0)
 	    {
 	      golem_vm_body_write_ops(scope_info->m_body,
				      GOLEM_OP_PH,
				      scope_info->n_index,
				      def_info->n_offset,
				      def_info->n_size);
 	      return TRUE;
 	    }
 	}
     }
  return FALSE;
}

gboolean
golem_scope_builder_exit(GolemScopeBuilder * scope,
			 GError ** error)
{
  GolemScopeInfo * scope_info = (GolemScopeInfo*) g_list_last(scope->priv->scopes)->data;
  scope->priv->scopes = g_list_remove(scope->priv->scopes,scope_info);
  golem_vm_body_write_op32(scope_info->m_body,GOLEM_OP_SX,scope_info->n_index);
  //TODO: free scope
  return TRUE;
}
