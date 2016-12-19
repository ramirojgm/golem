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

struct _GolemConstantPrivate
{
  GValue value;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemConstant,golem_constant,GOLEM_TYPE_EXPRESSION)

static void
_golem_constant_dispose(GObject * object)
{
  GolemConstant * self = GOLEM_CONSTANT(object);
  g_value_unset(&(self->priv->value));
  G_OBJECT_CLASS(golem_constant_parent_class)->dispose(object);
}

gboolean
_golem_constant_evalue(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemConstant * self = GOLEM_CONSTANT(expression);
  g_value_unset(result);
  g_value_init(result,G_VALUE_TYPE(&(self->priv->value)));
  g_value_copy(result,&(self->priv->value));
  return TRUE;
}

static void
golem_constant_init(GolemConstant * self)
{
  self->priv = golem_constant_get_instance_private(self);
}

static void
golem_constant_class_init(GolemConstantClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evalue = _golem_constant_evalue;
  G_OBJECT_CLASS(klass)->dispose = _golem_constant_dispose;
}

