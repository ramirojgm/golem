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

struct _GolemIfPrivate
{
  GolemExpression * conditional;
  GolemStatement * true_statement;
  GolemStatement * false_statement;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemIf,golem_if,GOLEM_TYPE_STATEMENT)

gboolean
_golem_if_execute(GolemStatement * statement,GolemRuntime * runtime,GError ** error)
{
  gboolean done = FALSE;
  GolemIf * self = GOLEM_IF(statement);
  GValue condition = G_VALUE_INIT;
  if(golem_expression_evaluate(GOLEM_EXPRESSION(self->priv->conditional),golem_runtime_get_context(runtime),&condition,error))
    {
      if(condition.data[0].v_int)
	{
	  done = golem_statement_execute(self->priv->true_statement,runtime,error);
	}
      else if(self->priv->false_statement)
	{
	  done = golem_statement_execute(self->priv->false_statement,runtime,error);
	}
      else
	{
	  done = TRUE;
	}
    }
  g_value_unset(&condition);
  return done;
}

static void
golem_if_init(GolemIf * self)
{
  self->priv = golem_if_get_instance_private(self);
}

static void
golem_if_class_init(GolemIfClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_if_execute;
}

gboolean
golem_if_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"if");
}

GolemIf *
golem_if_parse(GolemParser * parser,GError ** error)
{
  gboolean done = FALSE;
  GolemIf * instance = GOLEM_IF(g_object_new(GOLEM_TYPE_IF,NULL));
  if(golem_parser_next_word_check(parser,"if"))
    {
      if(golem_parser_next_word_check(parser,"("))
	{
	  instance->priv->conditional = golem_expression_complex_parse(parser,GOLEM_EXPRESSION_LIMIT_PARENTHESIS,error);
	  if(instance->priv->conditional)
	    {
	      if(golem_parser_next_word_check(parser,")"))
		{
		  instance->priv->true_statement = golem_statement_parse(parser,error);
		  if(instance->priv->true_statement)
		    {
		      if(golem_parser_next_word_check(parser,"else"))
			{
			  instance->priv->false_statement = golem_statement_parse(parser,error);
			  if(instance->priv->false_statement)
			    {
			      done = TRUE;
			    }
			}
		      else
			{
			  done = TRUE;
			}
		    }
		}
	      else
		{
		  golem_parser_error(error,parser,"was expected \")\"");
		}
	    }
	}
      else
	{
	  golem_parser_error(error,parser,"was expected \"(\"");
	}
    }
  else
    {
      golem_parser_error(error,parser,"was expected \"if\"");
    }

  if(!done)
    {
      g_object_unref(instance);
      instance = NULL;
    }

  return instance;
}
