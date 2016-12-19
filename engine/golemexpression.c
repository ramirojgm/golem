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

typedef struct _GolemExpressionPrivate GolemExpressionPrivate;

struct _GolemExpressionPrivate
{

};

G_DEFINE_TYPE_WITH_PRIVATE(GolemExpression,golem_expression,GOLEM_TYPE_SENTENCE)

static gboolean
_golem_expression_evalue(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  golem_throw(error,GOLEM_NOT_IMPLEMENTED_ERROR,"expression evaluate not implemented yet");
  return FALSE;
}


static void
golem_expression_init(GolemExpression * self)
{
  golem_expression_get_instance_private(self);
}

static void
golem_expression_class_init(GolemExpressionClass * klass)
{
  klass->evalue = _golem_expression_evalue;
}

GolemExpression *
golem_expression_parse(GolemParser * parser,GError ** error)
{
  /*if(golem_constant_check(parser))
    return golem_constant_parse(parser,error);
  else
    return NULL;*/
}

gboolean
golem_expression_evalue(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  return GOLEM_EXPRESSION_CLASS(expression)->evalue(expression,context,result,error);
}
