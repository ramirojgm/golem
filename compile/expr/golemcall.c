/*
	Copyright (C) 2018 Ramiro Jose Garcia Moraga

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

#include <golem.h>

GOLEM_DEFINE_STATEMENT(GolemCall,golem_call)

static void
golem_call_init(GolemCall * call)
{
  call->parent.base = NULL;
  call->arguments = NULL;
}

static GolemMetadata *
golem_call_value_type(GolemCall * call,
		      GolemScopeBuilder *scope_builder,
		      GError ** error)
{
  GolemMetadata *
  callable = golem_statement_value_type(call->parent.base,
					scope_builder,
					error);
  if (GOLEM_IS_FUNCTION(callable))
      return golem_function_get_return_type(GOLEM_FUNCTION(callable));
  else
      return NULL;
}


static gboolean
golem_call_compile(GolemCall * call,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  g_print("Yep\n");
  gboolean done = TRUE;
  for (GList * iter = g_list_first(call->arguments);iter; iter = iter->next)
    {
      GolemStatement * exp = (GolemStatement*)(iter->data);
      if ((done = golem_statement_compile(exp,body,scope_builder,error)))
	  golem_vm_body_write_op(body,GOLEM_OP_APT);
      else
	  break;
    }

    if (done)
      {
	  if (((GolemStatementExt*)call)->base->klass == GOLEM_ACCESSOR_CLASS)
	    {
	      done = golem_statement_compile(call->parent.base,
					     body,
					     scope_builder,
					     error);
	      if (done)
		{
		  GolemStatementExt * self =
		      (GolemStatementExt*)(call->parent.base);
		  done = golem_statement_compile(self->base,
						  body,
						  scope_builder,
						  error);
		  if (done)
		    {
		      golem_vm_body_write_op16(body,
					       GOLEM_OP_CAL,
					       g_list_length(call->arguments));
		    }
		}
	    }
	  else
	    {
	      done = FALSE;
	      g_set_error(error,
			  GOLEM_ERROR,
			  GOLEM_ERROR_COMPILE,
			  "can't implement");
	    }
      }
  return done;
}


static gboolean
golem_call_parse(GolemCall * call,
		 GolemParser * parser,
		 GolemExpressionLimit limit,
		 GError ** error)
{
  gboolean done = TRUE;
  if(golem_parser_check(parser,"("))
    {
      if (golem_parser_check(parser,")"))
	{
	  //Empty call
	  call->arguments = NULL;
	}
      else
	{
	  do
	    {
	      GolemStatement * exp =
		  golem_expression_parse_new(parser,
					    GOLEM_EXPRESSION_LIMIT_SEMICOLON,
					    error);
	      if (exp)
		call->arguments = g_list_append(call->arguments,exp);
	      else
		{
		  done = FALSE;
		  break;
		}

	    } while (golem_parser_check(parser,","));

	  if (done && !golem_parser_check(parser,")"))
	    {
	      g_set_error(error,
			  GOLEM_ERROR,
			  GOLEM_ERROR_SYNTAXIS,
			  "')' was expected");
	    }
	}
    }
  return done;
}

static void
golem_call_dispose(GolemCall * call)
{
  if(call->parent.base)
    golem_statement_free(call->parent.base);
  g_list_free_full(call->arguments,(GDestroyNotify)golem_statement_free);
}

static gboolean
golem_call_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"(");
}
