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

GOLEM_DEFINE_STATEMENT(GolemCall,golem_call)

static void
golem_call_init(GolemCall * call)
{
  call->parent.base = NULL;
  call->arguments = NULL;
}

static GType
golem_call_value_type(GolemCall * call,
		      GolemScopeBuilder *scope_builder,
		      GError ** error)
{
  //TODO: check for type return
  return G_TYPE_INT;
}


static gboolean
golem_call_compile(GolemCall * call,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = golem_statement_compile(call->parent.base,
				  body,
				  scope_builder,
				  error);

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
      while(TRUE)
	{

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
