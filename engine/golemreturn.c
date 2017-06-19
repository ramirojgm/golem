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

struct _GolemReturnPrivate
{
  GolemExpression * value;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemReturn,golem_return,GOLEM_TYPE_STATEMENT)

static gboolean
_golem_return_execute(GolemStatement * statement,GolemRuntime * runtime,GError ** error)
{
  GolemReturn * self = GOLEM_RETURN(statement);
  if(self->priv->value)
    {
      GValue result = G_VALUE_INIT;
      if(golem_expression_evaluate(self->priv->value,golem_runtime_get_context(runtime),&result,error))
	{
	  golem_runtime_return(runtime,&result);
	  g_value_unset(&result);
	  return TRUE;
	}
      else
	{
	  return FALSE;
	}
    }
  else
    {
      golem_runtime_return(runtime,NULL);
      return TRUE;
    }
}

static void
golem_return_class_init(GolemReturnClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_return_execute;
}

static void
golem_return_init(GolemReturn * self)
{
  self->priv = golem_return_get_instance_private(self);
}

gboolean
golem_return_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"return");
}

GolemStatement *
golem_return_parse(GolemParser * parser,GError ** error)
{
  GolemReturn * self = NULL;
  if(golem_parser_next_word_check(parser,"return"))
    {
      if(golem_parser_next_word_check(parser,";"))
	{
	  self = GOLEM_RETURN(g_object_new(GOLEM_TYPE_RETURN,NULL));
	}
      else
	{
	  GolemExpression * value = golem_expression_complex_parse(parser,GOLEM_EXPRESSION_LIMIT_SEMICOLON,error);
	  if(value)
	    {
	      if(golem_parser_next_word_check(parser,";"))
		{
		  self = GOLEM_RETURN(g_object_new(GOLEM_TYPE_RETURN,NULL));
		  self->priv->value = value;
		}
	      else
		{
		  golem_parser_error(error,parser,"was expected \";\"");
		}
	    }
	}
    }
  return GOLEM_STATEMENT(self);
}
