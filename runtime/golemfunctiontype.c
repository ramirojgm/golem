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
  GolemArgument ** m_arguments;
  guint16 n_arguments;
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
    {
      g_free(priv->m_arguments[index]->name);
      g_free(priv->m_arguments[index]);
    }
  g_free(priv->m_arguments);
}

static void
golem_function_type_class_init(GolemFunctionTypeClass * klass)
{
  G_OBJECT_CLASS(klass)->finalize = golem_function_type_finalize;
}

GolemFunctionType*
golem_function_type_new(guint16 count)
{
  GolemFunctionType * func_type = GOLEM_FUNCTION_TYPE(g_object_new(GOLEM_TYPE_FUNCTION_TYPE,NULL));
  GolemFunctionTypePrivate * priv = golem_function_info_get_instance_private(func_type);
  priv->n_arguments = count;
  priv->m_arguments = g_new0(GolemArgument*,count + 1);
  return func_type;
}

void
golem_function_type_set_argument(GolemFunctionType * func_type,
				 guint16 index,
				 const gchar * name,
				 GolemType * type)
{
  GolemFunctionTypePrivate * priv = golem_function_type_get_instance_private(func_type);
  g_return_if_fail(index >= 0 && index < priv->n_arguments);

  if(priv->m_arguments[index])
    g_free(priv->m_arguments[index]->name);
  else
    priv->m_arguments[index] = g_new0(GolemArgument,1);

  priv->m_arguments[index]->name = g_strdup(name);
  priv->m_arguments[index]->type = type;
}

GolemArgument**
golem_function_type_get_arguments(GolemFunctionType * func_type,gsize * length)
{
  GolemFunctionTypePrivate * priv = golem_function_type_get_instance_private(func_type);
  if(length)
    *length = priv->n_arguments;
  return priv->m_arguments;
}
