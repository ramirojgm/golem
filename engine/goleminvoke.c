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

struct _GolemInvokePrivate
{
  GolemExpression * func_exp;
  GList * 	    args_exp;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemInvoke,golem_invoke,GOLEM_TYPE_EXPRESSION)

static gboolean
_golem_invoke_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemInvoke * self = GOLEM_INVOKE(expression);
  GolemClosureInvoke * invoke = NULL;
  GValue func = G_VALUE_INIT;
  gboolean done = TRUE;

  if((done = golem_expression_evaluate(self->priv->func_exp,context,&func,error)))
    {
      if(G_VALUE_HOLDS_CLOSURE(&func))
	{
	  invoke = golem_closure_invoke_new();
	  for(GList * iter_arg = g_list_first(self->priv->args_exp);iter_arg;iter_arg = iter_arg->next)
	    {
	      GValue value_arg = G_VALUE_INIT;
	      g_value_unset(&value_arg);
	      if(!(done = golem_expression_evaluate(GOLEM_EXPRESSION(iter_arg->data),context,&value_arg,error)))
		{
		  break;
		}
	      else
		{
		  golem_closure_invoke_push(invoke,&value_arg);
		}
	      g_value_unset(&value_arg);
	    }

	  GolemClosure * closure = (GolemClosure*)(g_value_get_boxed(&func));
	  if(!golem_closure_invoke(closure,invoke))
	    {
	      golem_throw_error(error,golem_closure_invoke_get_error(invoke));
	    }
	  g_closure_unref(G_CLOSURE(closure));
	}
      else
	{
	  //TODO: throw error no function invocable
	  done = FALSE;
	  g_print("error:(%d)\n",g_value_get_int(&func));
	}
    }

  if(invoke)
    golem_closure_invoke_free(invoke);

  g_value_unset(&func);
  return done;
}

static void
golem_invoke_init(GolemInvoke * self)
{
  self->priv = golem_invoke_get_instance_private(self);
  self->priv->args_exp = NULL;
}

static void
golem_invoke_class_init(GolemInvokeClass *  klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = _golem_invoke_evaluate;
}

gboolean
golem_invoke_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"(");
}

GolemExpression *
golem_invoke_parse(GolemParser * parser,GolemExpression * expression,GError ** error)
{
  GolemInvoke * self = GOLEM_INVOKE(g_object_new(GOLEM_TYPE_INVOKE,NULL));
  gboolean done = TRUE;
  if((done = golem_parser_next_word_check(parser,"(")))
    {
      self->priv->func_exp = expression;
      while(TRUE)
	{
	  if(golem_parser_next_word_check(parser,")"))
	    break;

	  if(golem_parser_next_word_check(parser,","))
	    {
	      done = FALSE;
	      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected a expression before \",\"");
	      break;
	    }

	  GolemExpression * arg_exp = golem_expression_complex_parse(parser,GOLEM_EXPRESSION_LIMIT_PARENTHESIS_COMA,error);
	  if(arg_exp)
	    {
	      self->priv->args_exp = g_list_append(self->priv->args_exp,arg_exp);
	    }
	  else
	    {
	      done = FALSE;
	      break;
	    }

	  if(!golem_parser_next_word_check(parser,","))
	    {
	      if(golem_parser_next_word_check(parser,")"))
		break;
	      else
		{
		  done = FALSE;
		  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected \",\" or \")\"");
		}
	    }
	}
    }
  if(!done)
    {
      //TODO: free expression
    }
  return GOLEM_EXPRESSION(self);
}
