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

GOLEM_DEFINE_STATEMENT(GolemContext,golem_context)

static void
golem_context_init(GolemContext * ctx)
{
  ctx->variable_name = NULL;
  ctx->value = NULL;
}

static GolemMetadata *
golem_context_value_type(GolemContext * ctx,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
  GolemMetadata * type = golem_scope_builder_type(scope_builder,ctx->variable_name);
  if(type == NULL)
    {
      g_propagate_error(error,
			g_error_new(g_quark_from_static_string("golem"),
				    0,
				    "the variable \"%s\" not exists",
				    ctx->variable_name));
    }
  return type;
}


static gboolean
golem_context_compile(GolemContext * ctx,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = TRUE;
  if(ctx->value)
    {
      done = golem_statement_compile(ctx->value,
				    body,
				    scope_builder,
				    error);
      if(done)
	{
	  golem_vm_body_write_op(body,GOLEM_OP_DUP);
	  done = golem_scope_builder_set(
		  scope_builder,
		  ctx->variable_name,
		  error);
	}
    }
  else
    {
      done = golem_scope_builder_get(scope_builder,
				     ctx->variable_name,
				     error);
    }
  return done;
}


static gboolean
golem_context_parse(GolemContext * ctx,
		GolemParser * parser,
		GolemExpressionLimit limit,
		GError ** error)
{
  gboolean done = TRUE;
  ctx->variable_name = g_strdup(golem_parser_next_word(parser,TRUE));
  if(golem_parser_check(parser,"="))
    {
      ctx->value = golem_expression_parse_new(parser,limit,error);
      done = ctx->value != NULL;
    }
  return done;
}

static void
golem_context_dispose(GolemContext * ctx)
{
  g_free(ctx->variable_name);
  if(ctx->value)
    golem_statement_free(ctx->value);
}

static gboolean
golem_context_check(GolemParser * parser)
{
  return golem_parser_check_is_named(parser);
}
