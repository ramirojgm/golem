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

struct _GolemBuilderClosurePrivate
{
  GolemClosureInfo * info;
  GolemBlock * block;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuilderClosure,golem_builder_closure,GOLEM_TYPE_EXPRESSION)

static gboolean
_golem_builder_closure_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemBuilderClosure * self = GOLEM_BUILDER_CLOSURE(expression);
  GolemBuilderClosurePrivate *priv = golem_builder_closure_get_instance_private(self);
  if(golem_closure_info_resolve(priv->info,context,error))
    {
      GolemClosure * closure = golem_function_new(priv->info,context, GOLEM_STATEMENT(priv->block));
      g_value_init(result,GOLEM_TYPE_CLOSURE);
      g_value_set_boxed(result,closure);
      return TRUE;
    }
  else
    {
      return FALSE;
    }

}

static void
golem_builder_closure_init(GolemBuilderClosure * self)
{
  self->priv = golem_builder_closure_get_instance_private(self);
}


static void
golem_builder_closure_class_init(GolemBuilderClosureClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = _golem_builder_closure_evaluate;
}

gboolean
golem_builder_closure_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"do");
}

GolemExpression *
golem_builder_closure_parse(GolemParser * parser,GError ** error)
{
  GolemBuilderClosure * self = GOLEM_BUILDER_CLOSURE(g_object_new(GOLEM_TYPE_BUILDER_CLOSURE,NULL));
  gboolean done = TRUE;
  if(golem_parser_next_word_check(parser,"do"))
    {
      if(golem_parser_is_next_word(parser,"("))
	{
	  self->priv->info = golem_closure_info_parse_anonymous(parser,error);
	  if(self->priv->info)
	    {
	      if(golem_parser_is_next_word(parser,"{"))
		{
		  self->priv->block = golem_block_parse(parser,error);
		  if(!self->priv->block)
		    {
		      //TODO: error
		    }
		}
	      else
		{
		  //TODO: expected {

		}
	    }
	  else
	    {
	      //TODO: error
	    }
	}
      else
	{
	  //TODO:expected (
	}
    }
  else
    {
      //TODO: expected func
    }

  if(!done)
    {
      //free all
    }
  return GOLEM_EXPRESSION(self);
}
