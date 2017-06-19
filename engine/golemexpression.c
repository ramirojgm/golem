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

G_DEFINE_TYPE_WITH_CODE(GolemExpression,golem_expression,GOLEM_TYPE_STATEMENT,{})

static gboolean
_golem_expression_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  golem_runtime_error(error,GOLEM_NOT_IMPLEMENTED_ERROR,"expression evaluate not implemented yet");
  return FALSE;
}

static gboolean
_golem_expression_execute(GolemStatement * sentence,GolemRuntime * runtime,GError ** error)
{
  GValue result = G_VALUE_INIT;
  gboolean done = golem_expression_evaluate(GOLEM_EXPRESSION(sentence),golem_runtime_get_context(runtime),&result,error);
  g_value_unset(&result);
  return done;
}

static void
golem_expression_init(GolemExpression * self)
{
  golem_expression_get_instance_private(self);
}

static void
golem_expression_class_init(GolemExpressionClass * klass)
{
  klass->evaluate = _golem_expression_evaluate;
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_expression_execute;
}

gboolean
golem_expression_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  if(G_VALUE_TYPE(result) != G_TYPE_NONE)
    g_value_unset(result);
  return GOLEM_EXPRESSION_GET_CLASS(expression)->evaluate(expression,context,result,error);
}

GolemExpression *
golem_expression_parse(GolemParser * parser,GError ** error)
{
  GolemExpression * expression = NULL;
  expression = golem_expression_complex_parse(parser,GOLEM_EXPRESSION_LIMIT_SEMICOLON,error);

  if(!golem_parser_next_word_check(parser,";"))
    {
      g_clear_object(&expression);
      golem_parser_error(error,parser,"expected \";\"");
    }
  return expression;
}
