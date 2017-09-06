/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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

#include "golem.h"

typedef struct _GolemStructField GolemStructField;

struct _GolemStructField
{
  GType type;
  gchar * name;
  goffset offset;
  gsize size;
};

G_DEFINE_TYPE_WITH_CODE(GolemStructInfo,golem_struct_info,G_TYPE_OBJECT,{})

static void
golem_struct_info_init(GolemStructInfo * self)
{
  g_mutex_init(&self->mutex);
  self->fields = NULL;
  self->size = 0;
}

static void
golem_struct_info_class_init(GolemStructInfoClass * klass)
{

}

GolemStructInfo *
golem_struct_info_new(void)
{
  return GOLEM_STRUCT_INFO(g_object_new(GOLEM_TYPE_STRUCT_INFO,NULL));
}

void
golem_struct_info_add_field(GolemStructInfo * struct_info,GType type,const gchar * name)
{
  g_mutex_lock(&struct_info->mutex);
  GType fundamental = G_TYPE_FUNDAMENTAL(type);

  GolemStructField * field = g_new0(GolemStructField,1);
  field->name = g_strdup(name);
  field->type = type;

  switch(fundamental)
  {
    case G_TYPE_CHAR:
    case G_TYPE_UCHAR:
      field->size = sizeof(gchar);
      break;
    case G_TYPE_INT:
    case G_TYPE_UINT:
    case G_TYPE_FLOAT:
    case G_TYPE_FLAGS:
    case G_TYPE_ENUM:
      field->size = sizeof(gint);
      break;
    case G_TYPE_INT64:
    case G_TYPE_UINT64:
    case G_TYPE_DOUBLE:
      field->size = sizeof(gint64);
      break;
    case G_TYPE_LONG:
      field->size = sizeof(glong);
      break;
    default:
      field->size = sizeof(gpointer);
      break;
  }

  field->offset = GOLEM_OFFSET_WITH_PADDING(struct_info->size,field->size);
  struct_info->size = field->offset + field->size;
  struct_info->fields = g_list_append(struct_info->fields,field);
  g_mutex_unlock(&struct_info->mutex);
}

static GolemStructField *
_golem_struct_info_get_field(GolemStructInfo * struct_info,const gchar * name)
{
  GolemStructField * result = NULL;
  g_mutex_lock(&struct_info->mutex);
  for(GList * iter = g_list_first(struct_info->fields);iter; iter = g_list_next(iter))
    {
      GolemStructField * field = (GolemStructField*)iter->data;
      if(g_strcmp0(field->name,name) == 0)
	{
	  result = field;
	  break;
	}
    }
  g_mutex_unlock(&struct_info->mutex);
  return result;
}

goffset
golem_struct_info_get_field_offset(GolemStructInfo * struct_info,const gchar * name)
{
  goffset offset = -1;
  GolemStructField * field = _golem_struct_info_get_field(struct_info,name);
  if(field)
    {
      g_mutex_lock(&struct_info->mutex);
      offset = field->offset;
      g_mutex_unlock(&struct_info->mutex);
    }
  return offset;
}

gsize
golem_struct_info_get_field_size(GolemStructInfo * struct_info,const gchar * name)
{
  goffset size = 0;
  GolemStructField * field = _golem_struct_info_get_field(struct_info,name);
  if(field)
    {
      g_mutex_lock(&struct_info->mutex);
      size = field->size;
      g_mutex_unlock(&struct_info->mutex);
    }
  return size;
}

gpointer
golem_struct_info_new_instance(GolemStructInfo * struct_info)
{
  gsize instance_size = 0;
  g_mutex_lock(&struct_info->mutex);
  instance_size = struct_info->size;
  g_mutex_unlock(&struct_info->mutex);
  g_return_val_if_fail(instance_size > 0,NULL);

  return g_malloc0(instance_size);
}

gboolean
golem_struct_info_get(GolemStructInfo * struct_info,const gchar * name,GValue * dest,GError ** error)
{
  GolemStructField * field = _golem_struct_info_get_field(struct_info,name);
  if(field)
    {
      g_mutex_lock(&struct_info->mutex);
      g_value_unset(dest);
      g_value_init(dest,field->type);

      g_mutex_unlock(&struct_info->mutex);
      return TRUE;
    }
  else
    {
      golem_runtime_error(error,GOLEM_NOT_EXISTS_ERROR,"the field \"%s\" not exists");
      return FALSE;
    }
}

gboolean
golem_struct_info_set(GolemStructInfo * struct_info,gpointer instance,const gchar * name,const GValue * src,GError ** error)
{
  GolemStructField * field = _golem_struct_info_get_field(struct_info,name);
  if(field)
    {
      g_mutex_lock(&struct_info->mutex);
      GType fundamental = G_TYPE_FUNDAMENTAL(field->type);
      gpointer address = (instance + field->offset);
      switch(fundamental)
      {
	case G_TYPE_CHAR:
	  *((gchar*)address) = g_value_get_schar(src);
	  break;
	case G_TYPE_UCHAR:
	  *((guchar*)address) = g_value_get_uchar(src);
	  break;
	case G_TYPE_INT:
	  *((gint*)address) = g_value_get_int(src);
	  break;
	case G_TYPE_UINT:
	  *((guint*)address) = g_value_get_uint(src);
	  break;
	case G_TYPE_FLOAT:
	  *((gfloat*)address) = g_value_get_float(src);
	  break;
	case G_TYPE_FLAGS:
	  *((gint*)address) = g_value_get_flags(src);
	  break;
	case G_TYPE_ENUM:
	  *((gint*)address) = g_value_get_enum(src);
	  break;
	case G_TYPE_INT64:
	case G_TYPE_UINT64:
	case G_TYPE_DOUBLE:
	  field->size = sizeof(gint64);
	  break;
	case G_TYPE_LONG:
	  field->size = sizeof(glong);
	  break;
	default:
	  field->size = sizeof(gpointer);
	  break;
      }

      g_mutex_unlock(&struct_info->mutex);
      return TRUE;
    }
  else
    {
      golem_runtime_error(error,GOLEM_NOT_EXISTS_ERROR,"the field \"%s\" not exists");
      return FALSE;
    }
}

void
golem_struct_info_free_instance(GolemStructInfo * struct_info,gpointer instance)
{
  //Free instance
  g_free(instance);
}
