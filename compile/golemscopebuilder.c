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
  guint32	n_size;
} GolemScopeInfo;

typedef struct
{
  GolemTypeCode n_type;
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
			   GolemTypeCode type,
			   const gchar * name,
			   GError ** error)
{
  g_return_val_if_fail(type != GOLEM_TYPE_CODE_UNDEFINED,FALSE);

  if(scope->priv->scopes)
    {
      GolemScopeInfo * scope_info = (GolemScopeInfo*)scope->priv->scopes->data;

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
	case GOLEM_TYPE_CODE_INT8:
	case GOLEM_TYPE_CODE_UINT8:
	  def->n_size = sizeof(gint8);
	  break;
	case GOLEM_TYPE_CODE_INT16:
	case GOLEM_TYPE_CODE_UINT16:
	  def->n_size = sizeof(gint16);
	  break;
	case GOLEM_TYPE_CODE_INT32:
	case GOLEM_TYPE_CODE_UINT32:
	case GOLEM_TYPE_CODE_FLOAT:
	  def->n_size = sizeof(gint32);
	  break;
	case GOLEM_TYPE_CODE_INT64:
	case GOLEM_TYPE_CODE_UINT64:
	case GOLEM_TYPE_CODE_DOUBLE:
	  def->n_size = sizeof(gint64);
	  break;
	case GOLEM_TYPE_CODE_OBJECT:
	case GOLEM_TYPE_CODE_STRING:
	case GOLEM_TYPE_CODE_STRUCT:
	  def->n_size = sizeof(gpointer);
	  break;
	default:
	  def->n_size = 0;
      }
      scope_info->n_size += def->n_size;
      scope_info->m_def = g_list_append(scope_info->m_def,def);
      golem_vm_body_update_op32(scope_info->m_body,
				scope_info->n_index,
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

GolemTypeCode
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
  return GOLEM_TYPE_CODE_UNDEFINED;
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
  return TRUE;
}

gboolean
golem_scope_builder_get(GolemScopeBuilder * scope,
			GolemVMBody * body,
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

 	    }
 	}
     }
   return FALSE;
}

gboolean
golem_scope_builder_set(GolemScopeBuilder * scope,
			GolemVMBody * body,
			const gchar * name,
			GError ** error)
{

}

gboolean
golem_scope_builder_exit(GolemScopeBuilder * scope,
			 GolemVMBody * body,
			 GError ** error)
{

}
