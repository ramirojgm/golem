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


#include "../golem.h"

GOLEM_DEFINE_STATEMENT(GolemReturn,golem_return)

static void
golem_return_init(GolemReturn * ret)
{
  ret->m_expression = NULL;
}

static GolemTypeCode
golem_return_value_type(GolemReturn * ret,
		       GolemScopeBuilder *scope_builder,
		       GError ** error)
{
  return GOLEM_TYPE_CODE_UNDEFINED;
}


static gboolean
golem_return_compile(GolemReturn * ret,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done;
  done = golem_statement_compile(ret->m_expression,
				 body,
				 scope_builder,
				 error);
  if(done)
      golem_vm_body_write_op(body,GOLEM_OP_RT);
  return done;
}

static gboolean
golem_return_parse(GolemReturn * ret,
		   GolemParser * parser,
		   GolemExpressionLimit limit,
		   GError ** error)
{
  gboolean done = golem_parser_check(parser,"return");
  if(done)
    {
      GolemStatement * exp = golem_expression_parse_new(parser,
      						GOLEM_EXPRESSION_LIMIT_SEMICOLON,
      						error);

      if(exp)
	{
	  ret->m_expression = exp;
	  if(!golem_parser_check(parser,";"))
	    {
	      done = FALSE;
	      //TODO: expected ';'
	    }
	}
      else
	{
	  done = FALSE;
	}
    }
  else
    {
      //TODO: expected 'return'
    }
  return done;
}

static void
golem_return_dispose(GolemReturn * ret)
{
  if(ret->m_expression)
    golem_statement_free(ret->m_expression);
}

static gboolean
golem_return_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"return");
}
