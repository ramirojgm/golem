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

struct _GolemPointerOfPrivate
{
	gchar * name;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemPointerOf,golem_pointer_of,GOLEM_TYPE_EXPRESSION)

static 	gboolean
_golem_pointer_of_evaluate(GolemExpression* expression, GolemContext * context, GValue * result, GError** error)
{
  GolemPointerOf * self = GOLEM_POINTER_OF(expression);
  gpointer address = golem_context_address_of(context,self->priv->name,error);
  if(address)
    {
      g_value_init(result,G_TYPE_POINTER);
      g_value_set_pointer(result,address);
      return TRUE;
    }
  return FALSE;
}

static void
golem_pointer_of_init(GolemPointerOf * self)
{
  self->priv = golem_pointer_of_get_instance_private(self);
}

static void
golem_pointer_of_class_init(GolemPointerOfClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = _golem_pointer_of_evaluate;
}


gboolean
golem_pointer_of_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"pointerof");
}

GolemExpression *
golem_pointer_of_parse(GolemParser * parser,GError ** error)
{
  GolemPointerOf * self = GOLEM_POINTER_OF(g_object_new(GOLEM_TYPE_POINTER_OF,NULL));
  gboolean done = FALSE;
  if(golem_parser_next_word_check(parser,"pointerof"))
    {
      if(golem_parser_next_word_check(parser,"("))
	{
	  if(golem_parser_check_is_named(parser))
	    {
	      self->priv->name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
	      if(golem_parser_next_word_check(parser,")"))
		{
		  done = TRUE;
		}
	      else
		{
		  golem_parser_error(error,parser,"was expected \")\"");
		}
	    }
	  else
	    {
	      golem_parser_error(error,parser,"was expected the variable name");
	    }
	}
      else
	{
	  golem_parser_error(error,parser,"was expected \"(\"");
	}
    }
  else
    {
      golem_parser_error(error,parser,"was expected \"pointerof\"");
    }

  if(!done)
    g_clear_object(&self);
  return GOLEM_EXPRESSION(self);
}
