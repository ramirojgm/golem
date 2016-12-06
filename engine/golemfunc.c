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

typedef struct _GolemFuncPrivate GolemFuncPrivate;

struct _GolemFuncPrivate
{
  GolemFuncMetaData * meta_data;
  gpointer address;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemFunc,golem_func,G_TYPE_OBJECT)

gboolean
_golem_func_invoke_real(GolemFunc * func,GValue ** args,GValue * result,GError ** error)
{
  GolemFuncPrivate * priv = golem_func_get_instance_private(func);
  gpointer func_mem = g_malloc(1024);

  g_free(func_mem);
  return TRUE;
}

gpointer
_golem_func_get_address_real(GolemFunc * func)
{
  GolemFuncPrivate * priv = golem_func_get_instance_private(func);
  return priv->address;
}

static void
golem_func_init(GolemFunc * self)
{
  GolemFuncPrivate * priv = golem_func_get_instance_private(self);
  priv->meta_data = NULL;
  priv->address = NULL;
}

static void
golem_func_class_init(GolemFuncClass * klass)
{
  klass->invoke = _golem_func_invoke_real;
  klass->get_address = _golem_func_get_address_real;
}

GolemFunc *
golem_func_new(GolemFuncMetaData * meta_data,gpointer address)
{
  GolemFunc * self = GOLEM_FUNC(g_object_new(GOLEM_TYPE_FUNC,NULL));
  GolemFuncPrivate * priv = golem_func_get_instance_private(self);
  priv->meta_data = meta_data;
  priv->address = address;
  return self;
}

gboolean
golem_func_invoke(GolemFunc * func,GValue ** args,GValue * result,GError ** error)
{
  GolemFuncClass * klass = GOLEM_FUNC_GET_CLASS(func);
  return klass->invoke(func,args,result,error);
}

gpointer
golem_func_get_address(GolemFunc * func)
{
  GolemFuncClass * klass = GOLEM_FUNC_GET_CLASS(func);
  return klass->get_address(func);
}


GolemFuncMetaData *
golem_func_meta_data_new()
{
  GolemFuncMetaData * self = g_new0(GolemFuncMetaData,1);
  self->params = NULL;
  self->return_type = G_TYPE_NONE;
  return self;
}

GolemFuncMetaData *
golem_func_meta_data_parse(GolemParser * parser,gchar ** object_name,gchar ** function_name,GError ** error)
{
  if(golem_parser_check_is_named(parser))
    {

    }
  else
    {

    }
}

void
golem_func_meta_data_set_return_type(GolemFuncMetaData * meta_data,GType return_type)
{
  meta_data->return_type = return_type;
}

GType
golem_func_meta_data_get_return_type(GolemFuncMetaData * meta_data)
{
  return meta_data->return_type;
}

void
golem_func_meta_data_add_param(GolemFuncMetaData * meta_data,const gchar * name,GType type,gboolean is_reference,gboolean is_array)
{
  GolemFuncParam * param = g_new0(GolemFuncParam,1);
  param->name = g_strdup(name);
  param->type = type;
  param->is_array = is_array;
  param->is_reference = is_reference;
  param->catch_exception = FALSE;
  meta_data->params = g_list_append(meta_data->params,param);
}

void
golem_func_meta_data_catch_exception(GolemFuncMetaData * meta_data)
{
  GolemFuncParam * param = g_new0(GolemFuncParam,1);
  param->name = NULL;
  param->type = G_TYPE_ERROR;
  param->is_array = FALSE;
  param->is_reference = TRUE;
  param->catch_exception = TRUE;
  meta_data->params = g_list_append(meta_data->params,param);
}
