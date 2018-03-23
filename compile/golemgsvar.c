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

GOLEM_DEFINE_STATEMENT(GolemGSVar,golem_gsvar)

static void
golem_const_init(GolemGSVar * gsvar)
{
  gsvar->variable_name = NULL;
  gsvar->value = NULL;
}

static GolemTypeCode
golem_const_value_type(GolemConst * cnst,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{

  return cnst->type;
}


static gboolean
golem_gsvar_compile(GolemGSVar * gsvar,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = TRUE;
  return done;
}


static gboolean
golem_gsvar_parse(GolemGSVar * gsvar,
		GolemParser * parser,
		GolemExpressionLimit limit,
		GError ** error)
{
  gboolean done = TRUE;

  return done;
}

static void
golem_gsvar_dispose(GolemGSVar * gsvar)
{
  g_free(gsvar->variable_name);
  if(gsvar->value)
    golem_statement_free(gsvar->value);
}

static gboolean
golem_gsvar_check(GolemParser * parser)
{
  return golem_parser_check_is_named(parser);
}
