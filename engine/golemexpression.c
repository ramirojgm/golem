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

G_DEFINE_TYPE_WITH_CODE(GolemExpression,golem_expression,GOLEM_TYPE_SENTENCE,{})

static gboolean
_golem_expression_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  golem_throw(error,GOLEM_NOT_IMPLEMENTED_ERROR,"expression evaluate not implemented yet");
  return FALSE;
}

static gboolean
_golem_expression_execute(GolemSentence * sentence,GolemContext * context,GError ** error)
{
  GValue result;
  gboolean done = golem_expression_evaluate(GOLEM_EXPRESSION(sentence),context,&result,error);
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
  GOLEM_SENTENCE_CLASS(klass)->execute = _golem_expression_execute;
}

GolemExpression *
golem_expression_parse(GolemParser * parser,GError ** error)
{
  GolemExpression * expression = NULL;
  if(golem_constant_check(parser))
    expression = golem_constant_parse(parser,error);

  if(!golem_parser_next_word_check(parser,";"))
    {
      g_clear_object(&expression);
      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"expected \";\"");
    }
  return expression;
}

gboolean
golem_expression_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  g_print("evaluated");
  return GOLEM_EXPRESSION_GET_CLASS(expression)->evaluate(expression,context,result,error);
}
