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

GOLEM_DEFINE_STATEMENT(GolemNot,golem_not)

static void
golem_not_init(GolemNot * not)
{
  not->value = NULL;
}

static GType
golem_not_value_type(GolemNot * not,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
    return G_TYPE_BOOLEAN;
}


static gboolean
golem_not_compile(GolemNot * not,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = golem_statement_compile(not->value,
				  body,
				  scope_builder,
				  error);
  if(done)
      golem_vm_body_write_op(body,GOLEM_OP_NOT);

  return done;
}


static gboolean
golem_not_parse(GolemNot * not,
		GolemParser * parser,
		GolemExpressionLimit limit,
		GError ** error)
{
  gboolean done = TRUE;
  if((done = golem_parser_check(parser,"!")))
    {
      not->value = golem_simple_expression_parse(parser,
						 limit,
						 error);
      done = not->value != NULL;
    }
  return done;
}

static void
golem_not_dispose(GolemNot * not)
{
  if(not->value)
    golem_statement_free(not->value);
}

static gboolean
golem_not_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"!");
}
