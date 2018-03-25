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

typedef enum
{
  GOLEM_OPERATOR_NON = 0,
  GOLEM_OPERATOR_ADD,
  GOLEM_OPERATOR_SUB,
  GOLEM_OPERATOR_MUL,
  GOLEM_OPERATOR_DIV,
  GOLEM_OPERATOR_IDIV,
  GOLEM_OPERATOR_EXP,
  GOLEM_OPERATOR_MOD,
  GOLEM_OPERATOR_IQL,
  GOLEM_OPERATOR_DST,
  GOLEM_OPERATOR_LES,
  GOLEM_OPERATOR_GRE,
  GOLEM_OPERATOR_ILES,
  GOLEM_OPERATOR_IGRE,
  GOLEM_OPERATOR_LAND,
  GOLEM_OPERATOR_LOR,
  GOLEM_OPERATOR_BAND,
  GOLEM_OPERATOR_BOR
} GolemOperator;

typedef struct
{
  GolemOperator operator;
  GolemStatement * exp1;
  GolemStatement * exp2;
} GolemExpressionOperation;

typedef struct
{
  GolemOperator operator;
  GolemStatement * exp;
} GolemExpressionSingle;

static GolemStatement *
golem_expression_extends_parse(GolemParser * parser,
			 GolemStatement * base,
			 GolemExpressionLimit limit,
			 GError ** error)
{

  return base;
}

static GolemStatement *
golem_expression_single_parse(GolemParser * parser,
		      GolemExpressionLimit limit,
		      GError ** error)
{
  GolemStatementClass * klass = NULL;
  GolemStatement * statement = NULL;

  /* search class */
  if(golem_statement_check(GOLEM_CONST_CLASS,parser))
    klass = GOLEM_CONST_CLASS;
  if(golem_statement_check(GOLEM_GSVAR_CLASS,parser))
    klass = GOLEM_GSVAR_CLASS;

  /* initialize and parse */
  if(klass)
    {
      statement = g_malloc0(klass->size);
      statement->klass = klass;
      statement->source = g_strdup(golem_parser_get_source_name(parser));
      statement->line = golem_parser_get_line(parser);
      klass->init(statement);
      if(!klass->parse(statement,parser,limit,error))
      {
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

GolemStatement *
golem_expression_parse(GolemParser * parser,
		       GolemExpressionLimit limit,
		       GError ** error)
{
  return golem_expression_single_parse(parser,limit,error);
}
