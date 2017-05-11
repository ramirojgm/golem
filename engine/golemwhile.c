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

struct _GolemWhilePrivate
{
  GolemExpression * conditional;
  GolemStatement * do_statement;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemWhile,golem_while,GOLEM_TYPE_STATEMENT)

gboolean
_golem_while_execute(GolemStatement * statement,GolemContext * context,GError ** error)
{
  gboolean done = TRUE;
  GolemWhile * self = GOLEM_WHILE(statement);
  GValue condition = G_VALUE_INIT;
  while(done)
    {
      if(golem_expression_evaluate(GOLEM_EXPRESSION(self->priv->conditional),context,&condition,error))
	{
	  if(condition.data[0].v_int)
	    {
	      done = golem_statement_execute(self->priv->do_statement,context,error);
	      g_value_unset(&condition);
	    }
	  else
	    {
	      g_value_unset(&condition);
	      break;
	    }
	}
      else
	{
	  done = FALSE;
	  break;
	}
    }
  return done;
}

static void
golem_while_init(GolemWhile * self)
{
  self->priv = golem_while_get_instance_private(self);
}

static void
golem_while_class_init(GolemWhileClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_while_execute;
}

gboolean
golem_while_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"while");
}


GolemWhile *
golem_while_parse(GolemParser * parser,GError ** error)
{
  gboolean done = FALSE;
  GolemWhile * instance = GOLEM_WHILE(g_object_new(GOLEM_TYPE_WHILE,NULL));
  if(golem_parser_next_word_check(parser,"while"))
    {
      if(golem_parser_next_word_check(parser,"("))
	{
	  instance->priv->conditional = golem_expression_complex_parse(parser,GOLEM_EXPRESSION_LIMIT_PARENTHESIS,error);
	  if(instance->priv->conditional)
	    {
	      if(golem_parser_next_word_check(parser,")"))
		{
		  instance->priv->do_statement = golem_statement_parse(parser,error);
		  if(instance->priv->do_statement)
		    {
		      done = TRUE;
		    }
		}
	      else
		{
		  //TODO: expected )
		}
	    }
	}
      else
	{
	  //TODO: expected (
	}
    }
  else
    {
      //TODO: expected if
    }

  if(!done)
    {
      g_object_unref(instance);
      instance = NULL;
    }

  return instance;
}
