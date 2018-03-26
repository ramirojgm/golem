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


typedef struct
{
  GolemOperator operator;
  GolemStatement * exp;
} GolemExpressionSingle;

GOLEM_DEFINE_STATEMENT(GolemExpression,golem_expression)

static GolemStatement *
golem_extend_expression_parse(GolemParser * parser,
			 GolemStatement * base,
			 GolemExpressionLimit limit,
			 GError ** error)
{

  return base;
}

GolemStatement *
golem_simple_expression_parse(GolemParser * parser,
		      GolemExpressionLimit limit,
		      GError ** error)
{
  GolemStatementClass * klass = NULL;
  GolemStatement * statement = NULL;

  /* search class */
  if(golem_statement_check(GOLEM_NOT_CLASS,parser))
    klass = GOLEM_NOT_CLASS;
  else if(golem_statement_check(GOLEM_NEGATIVE_CLASS,parser))
    klass = GOLEM_NEGATIVE_CLASS;
  else if(golem_statement_check(GOLEM_CONST_CLASS,parser))
    klass = GOLEM_CONST_CLASS;
  else if(golem_statement_check(GOLEM_GSVAR_CLASS,parser))
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
      else
	{
	  statement = golem_extend_expression_parse(parser,
						    statement,
						    limit,
						    error);
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

static gboolean
golem_expression_limit_check(GolemParser * parser,
			     GolemExpressionLimit limit)
{
  if(!golem_parser_is_end(parser))
    {
      switch(limit)
      {
	case GOLEM_EXPRESSION_LIMIT_BRACKET:
	  return golem_parser_is_next_word(parser,"}");
	case GOLEM_EXPRESSION_LIMIT_BRACKET_COMA:
	  return golem_parser_is_next_word(parser,",") || golem_parser_is_next_word(parser,"}");
	case GOLEM_EXPRESSION_LIMIT_PARENTHESIS:
	  return golem_parser_is_next_word(parser,")");
	case GOLEM_EXPRESSION_LIMIT_PARENTHESIS_COMA:
	  return golem_parser_is_next_word(parser,",") || golem_parser_is_next_word(parser,")");
	case GOLEM_EXPRESSION_LIMIT_SEMICOLON:
	  return golem_parser_is_next_word(parser,";");
	case GOLEM_EXPRESSION_LIMIT_SEMICOLON_COMA:
	  return golem_parser_is_next_word(parser,",") || golem_parser_is_next_word(parser,";");
	case GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET:
	  return  golem_parser_is_next_word(parser,"]");
	case GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET_COMA:
	  return golem_parser_is_next_word(parser,",") || golem_parser_is_next_word(parser,"]");
	default:
	  return FALSE;
      }
    }
  else
    {
      return TRUE;
    }
}

GolemStatement *
golem_expression_parse_new(GolemParser * parser,
			   GolemExpressionLimit limit,
			   GError ** error)
{
  GolemStatementClass * klass = GOLEM_EXPRESSION_CLASS;
  GolemStatement * statement = NULL;
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
  return statement;
}


static GolemOperator
golem_operator_parse(GolemParser * parser)
{
  if(golem_parser_check(parser,"+"))
    return GOLEM_OPERATOR_ADD;
  else if(golem_parser_check(parser,"-"))
    return GOLEM_OPERATOR_SUB;
  else if(golem_parser_check(parser,"*"))
    return GOLEM_OPERATOR_MUL;
  else if(golem_parser_check(parser,"/"))
    return GOLEM_OPERATOR_DIV;
  else if(golem_parser_check(parser,"**"))
    return GOLEM_OPERATOR_EXP;
  else if(golem_parser_check(parser,"%"))
    return GOLEM_OPERATOR_MOD;
  else if(golem_parser_check(parser,"&"))
    return GOLEM_OPERATOR_BAND;
  else if(golem_parser_check(parser,"|"))
    return GOLEM_OPERATOR_BOR;
  else if(golem_parser_check(parser,"&&"))
    return GOLEM_OPERATOR_LAND;
  else if(golem_parser_check(parser,"||"))
    return GOLEM_OPERATOR_LOR;
  else if(golem_parser_check(parser,"<"))
    return GOLEM_OPERATOR_LES;
  else if(golem_parser_check(parser,">"))
    return GOLEM_OPERATOR_GRE;
  else if(golem_parser_check(parser,"<="))
    return GOLEM_OPERATOR_ILES;
  else if(golem_parser_check(parser,">="))
    return GOLEM_OPERATOR_IGRE;
  else if(golem_parser_check(parser,"=="))
    return GOLEM_OPERATOR_IQL;
  else if(golem_parser_check(parser,"!="))
    return GOLEM_OPERATOR_DST;
  else
    return GOLEM_OPERATOR_NON;
}

static void
golem_expression_single_free(GolemExpressionSingle * single)
{
  if(single->exp)
    golem_statement_free(single->exp);
  g_free(single->exp);
}

static GolemExpressionOperation *
golem_expression_operation_new(GList * start,GList * end)
{
  GolemExpressionOperation * op = g_new(GolemExpressionOperation,1);
  GolemExpressionSingle * single;
  if(start == end)
    {
      single = (GolemExpressionSingle*) start->data;
      op->operator = GOLEM_OPERATOR_NON;
      op->value = single->exp;
    }
  else if(g_list_next(start) == end)
    {
      single = (GolemExpressionSingle*) end->data;
      op->operator = single->operator;
      op->exp1 = golem_expression_operation_new(start,start);
      op->exp2 = golem_expression_operation_new(end,end);
    }
  else
    {
      GList * min = end;
      GolemExpressionSingle * single_iter;
      for(GList * iter = end; iter != start; iter = g_list_previous(iter))
	{
	  single = (GolemExpressionSingle*) min->data;
	  single_iter = (GolemExpressionSingle*) iter->data;
	  if(single_iter->operator <= single->operator)
	    min = iter;
	}
      single = (GolemExpressionSingle*) min->data;
      op->operator = single->operator;
      op->exp1 = golem_expression_operation_new(start,g_list_previous(min));
      op->exp1 = golem_expression_operation_new(min,end);
    }
  return op;
}

static gboolean
golem_expression_operation_compile(GolemExpressionOperation * exp,
				   GolemVMBody * body,
				   GolemScopeBuilder * scope_builder,
				   GError ** error)
{

}

static gboolean
golem_expression_parse(GolemExpression * exp,
		       GolemParser * parser,
		       GolemExpressionLimit limit,
		       GError ** error)
{
  gboolean done = TRUE;
  GList * operations = NULL;
  GolemOperator operator = GOLEM_OPERATOR_NON;

  while(!golem_expression_limit_check(parser,limit))
    {
      GolemExpressionSingle * single = g_new(GolemExpressionSingle,1);
      single->operator = operator;
      single->exp = golem_simple_expression_parse(parser,limit,error);

      if(single->exp)
	{
	  operations = g_list_append(operations,single);
	  if(golem_expression_limit_check(parser,limit))
	    {
	      break;
	    }
	  else
	    {
	      operator = golem_operator_parse(parser);
	      if(operator == GOLEM_OPERATOR_NON)
		{
		  done = FALSE;
		  //TODO: throw expected a operator
		  break;
		}
	    }
	}
      else
	{
	  done = FALSE;
	  golem_expression_single_free(single);
	  break;
	}
    }

  if(done)
    {
      exp->op = golem_expression_operation_new(
	  g_list_first(operations),
	  g_list_last(operations));
    }

  g_list_free_full(operations,
		   (GDestroyNotify)golem_expression_single_free);
  return done;
}

static void
golem_expression_init(GolemExpression * exp)
{
  g_print("Init\n");
  exp->op = NULL;
}

static GolemTypeCode
golem_expression_value_type(GolemExpression * exp,
			    GolemScopeBuilder *scope_builder,
			    GError ** error)
{
  return GOLEM_TYPE_CODE_VARIANT;
}


static gboolean
golem_expression_compile(GolemExpression * exp,
			  GolemVMBody * body,
			  GolemScopeBuilder * scope_builder,
			  GError ** error)
{
  gboolean done = TRUE;
  return done;
}

static void
golem_expression_dispose(GolemExpression * exp)
{

}

static gboolean
golem_expression_check(GolemParser * parser)
{
  return !golem_parser_is_end(parser);
}
