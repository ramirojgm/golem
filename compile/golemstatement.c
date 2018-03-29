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

GolemStatement *
golem_statement_parse(GolemParser * parser,
		      GError ** error)
{
  GolemStatementClass * klass = NULL;
  GolemStatement * statement = NULL;
  while(golem_parser_check(parser,";"));

  /* search class */
  if(golem_statement_check(GOLEM_BLOCK_CLASS,parser))
    klass = GOLEM_BLOCK_CLASS;
  else if(golem_statement_check(GOLEM_RETURN_CLASS,parser))
    klass = GOLEM_RETURN_CLASS;
  else if(golem_statement_check(GOLEM_VAR_CLASS,parser))
    klass = GOLEM_VAR_CLASS;
  else
    klass = GOLEM_EXPRESSION_CLASS;

  /* initialize and parse */
  if(klass)
    {
      statement = g_malloc0(klass->size);
      statement->klass = klass;
      statement->source = g_strdup(golem_parser_get_source_name(parser));
      statement->line = golem_parser_get_line(parser);
      klass->init(statement);
      if(!klass->parse(statement,parser,GOLEM_EXPRESSION_LIMIT_SEMICOLON,error))
	{
	  golem_statement_free(statement);
	  statement = NULL;
	}
      else if( klass == GOLEM_EXPRESSION_CLASS && !golem_parser_check(parser,";"))
	{
	  g_propagate_error(error,
	  		g_error_new(GOLEM_ERROR,
	  			  GOLEM_COMPILE_ERROR_SYNTAXES,
	  			  "%s: %d: was expected \";\" instead \"%s\"",
	  			  golem_parser_get_source_name(parser),
	  			  golem_parser_get_line(parser),
	  			  golem_parser_next_word(parser,FALSE))
			    );

	  golem_statement_free(statement);
	  statement = NULL;
	}
    }
  else
    {
      g_propagate_error(error,
		g_error_new(GOLEM_ERROR,
			  GOLEM_COMPILE_ERROR_SYNTAXES,
			  "%s: %d: can't solve syntaxes \"%s\"",
			  golem_parser_get_source_name(parser),
			  golem_parser_get_line(parser),
			  golem_parser_next_word(parser,FALSE))
      );
    }
  return statement;
}

gboolean
golem_statement_check(GolemStatementClass * klass,
		      GolemParser* parser)
{
  g_return_val_if_fail(klass != NULL,FALSE);
  return klass->check(parser);
}

gboolean
golem_statement_compile(GolemStatement * statement,
			GolemVMBody * body,
			GolemScopeBuilder * scope_builder,
			GError ** error)
{
  g_return_val_if_fail(statement != NULL,FALSE);
  return statement->klass->compile(statement,
				   body,
				   scope_builder,
				   error);
}

GolemTypeCode
golem_statement_value_type(GolemStatement * statement,
			GolemScopeBuilder * scope_builder,
			GError ** error)
{
  g_return_val_if_fail(statement != NULL,FALSE);
  return statement->klass->value_type(statement,
				   scope_builder,
				   error);
}

void
golem_statement_free(GolemStatement * statement)
{
  g_return_if_fail(statement != NULL);
  statement->klass->dispose(statement);
  g_free(statement->source);
  g_free(statement);
}
