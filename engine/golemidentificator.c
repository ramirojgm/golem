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

struct _GolemIdentificatorPrivate
{
  gchar * var_name;
  GolemExpression * value;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemIdentificator,golem_identificator,GOLEM_TYPE_EXPRESSION)

static gboolean
golem_identificator_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemIdentificator * self = GOLEM_IDENTIFICATOR(expression);
  gboolean done;
  if(self->priv->value)
    {
      GValue result_value = G_VALUE_INIT;
      if((done = golem_expression_evaluate(self->priv->value,context,&result_value,error)))
	{
	  done = golem_context_set(context,self->priv->var_name,&result_value,error);
	  g_value_init(result,G_VALUE_TYPE(&result_value));
	  g_value_copy(&result_value,result);
	  g_value_unset(&result_value);
	}
    }
  else
    {
      done = golem_context_get(context,self->priv->var_name,result,error);
    }
  return done;
}

static void
golem_identificator_init(GolemIdentificator * self)
{
  self->priv = golem_identificator_get_instance_private(self);
}

static void
golem_identificator_class_init(GolemIdentificatorClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = golem_identificator_evaluate;
}

gboolean
golem_identificator_check(GolemParser * parser)
{
  return golem_parser_check_is_named(parser);
}

GolemExpression *
golem_identificator_parse(GolemParser * parser,GolemExpressionLimit limit,GError ** error)
{
  GolemIdentificator * expression = GOLEM_IDENTIFICATOR(g_object_new(GOLEM_TYPE_IDENTIFICATOR,NULL));
  expression->priv->var_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
  g_print("var:%s\n",expression->priv->var_name);
  if(golem_parser_next_word_check(parser,"="))
    {
      expression->priv->value = golem_expression_complex_parse(parser,limit,NULL);
    }
  else
    {
      expression->priv->value = NULL;
    }
  return GOLEM_EXPRESSION(expression);
}
