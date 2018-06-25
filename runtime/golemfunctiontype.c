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

typedef struct _GolemFunctionTypePrivate GolemFunctionTypePrivate;
struct _GolemFunctionTypePrivate
{
  GolemType ** m_arguments;
  GolemType * m_ret;
  guint16 n_arguments;
  gint16 n_throw_error;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemFunctionType,golem_function_type,GOLEM_TYPE_METADATA)

static void
golem_function_type_init(GolemFunctionType * self)
{
  GolemFunctionTypePrivate * priv = golem_function_type_get_instance_private(self);
  priv->m_arguments = NULL;
  priv->n_arguments = 0;
}

static void
golem_function_type_finalize(GObject * obj)
{
  GolemFunctionTypePrivate * priv = golem_function_type_get_instance_private(GOLEM_FUNCTION_TYPE(obj));
  for(guint index = 0; index < priv->n_arguments; index ++)
      g_object_unref(priv->m_arguments[index]);
  g_free(priv->m_arguments);
}

static void
golem_function_type_class_init(GolemFunctionTypeClass * klass)
{
  G_OBJECT_CLASS(klass)->finalize = golem_function_type_finalize;
}

GolemFunctionType *
golem_function_type_new(GolemType * ret_type,
			guint16 count,
			GolemType ** types,
			gint16 throw_error)
{
  GolemFunctionType * func_type = GOLEM_FUNCTION_TYPE(g_object_new(GOLEM_TYPE_FUNCTION_TYPE,NULL));
  GolemFunctionTypePrivate * priv = golem_function_type_get_instance_private(func_type);
  priv->n_arguments = count;
  priv->m_arguments = g_new0(GolemType*,count + 1);
  for(guint32 index = 0; index < count; index ++)
    priv->m_arguments[index] = GOLEM_TYPE(g_object_ref(types[index]));
  priv->m_ret = ret_type;
  priv->n_throw_error = throw_error;
  return func_type;
}

GolemType**
golem_function_type_get_arguments(GolemFunctionType * func_type,guint16 * length)
{
  GolemFunctionTypePrivate * priv = golem_function_type_get_instance_private(func_type);
  if(length)
    *length = priv->n_arguments;
  return priv->m_arguments;
}
