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
  GolemStatementClass * klass = NULL;
  GolemStatement * statement = NULL;

  /* search class */
  if(golem_statement_check(GOLEM_CALL_CLASS,parser))
    klass = GOLEM_CALL_CLASS;

  /* initialize and parse */
  if(klass)
    {
      statement = g_malloc0(klass->size);
      statement->klass = klass;
      statement->source = g_strdup(golem_parser_get_source_name(parser));
      statement->line = golem_parser_get_line(parser);
      ((GolemStatementExt*)statement)->base = base;
      klass->init(statement);
      if(!klass->parse(statement,parser,limit,error))
      {
	golem_statement_free(statement);
	statement = NULL;
      }
    }
  else
    {
      statement = base;
    }
  return statement;
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
    return GOLEM_OPERATOR_LESI;
  else if(golem_parser_check(parser,">="))
    return GOLEM_OPERATOR_GREI;
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
      op->exp2 = golem_expression_operation_new(min,end);
    }
  return op;
}

static gboolean
golem_expression_operation_compile(GolemExpressionOperation * exp,
				   GolemVMBody * body,
				   GolemScopeBuilder * scope_builder,
				   GError ** error);

static GType
golem_expression_operation_value_type(GolemExpressionOperation * exp,
				      GolemScopeBuilder * scope_builder,
				      GError ** error);


static GType
golem_expression_operation_op_type(GolemExpressionOperation * exp,
				  GolemScopeBuilder * scope_builder,
				  GError ** error)
{
  if(exp->operator == GOLEM_OPERATOR_NON)
    return golem_statement_value_type(exp->value,scope_builder,error);

  GType type1 = golem_expression_operation_value_type(exp->exp1,
							     scope_builder,
							     error);

  GType type2 = golem_expression_operation_value_type(exp->exp2,
							   scope_builder,
							   error);

  if(type1 == G_TYPE_POINTER || type2 == G_TYPE_POINTER)
    return G_TYPE_POINTER;
  else if(type1 == G_TYPE_DOUBLE || type2 == G_TYPE_DOUBLE)
    return G_TYPE_DOUBLE;
  else if(type1 == G_TYPE_FLOAT || type2 == G_TYPE_FLOAT)
    return G_TYPE_FLOAT;
  else if(type1 == G_TYPE_INT64 || type2 == G_TYPE_INT64)
    return G_TYPE_INT64;
  else if(type1 == G_TYPE_INT || type2 == G_TYPE_INT)
    return G_TYPE_INT;
  else if(type1 == G_TYPE_INT16 || type2 == G_TYPE_INT16)
    return G_TYPE_INT16;
  else
    return G_TYPE_CHAR;
}

static GType
golem_expression_operation_value_type(GolemExpressionOperation * exp,
				      GolemScopeBuilder * scope_builder,
				      GError ** error)
{
  switch(exp->operator)
  {
    case GOLEM_OPERATOR_NON:
      return golem_statement_value_type(exp->value,scope_builder,error);
    case GOLEM_OPERATOR_IQL:
    case GOLEM_OPERATOR_DST:
    case GOLEM_OPERATOR_GRE:
    case GOLEM_OPERATOR_LES:
    case GOLEM_OPERATOR_GREI:
    case GOLEM_OPERATOR_LESI:
    case GOLEM_OPERATOR_LAND:
    case GOLEM_OPERATOR_LOR:
      return G_TYPE_BOOLEAN;
    case GOLEM_OPERATOR_EXP:
      return G_TYPE_DOUBLE;
    default:
      return golem_expression_operation_op_type(exp,scope_builder,error);
  }
}

static void
golem_expression_operation_cast(GolemExpressionOperation * exp,
				GType type)
{

}

static gboolean
golem_expression_operation_write_op(GolemExpressionOperation * exp,
				   GolemVMBody * body,
				   GolemScopeBuilder * scope_builder,
				   GType type,
				   GolemVMOpCode code,
				   GError ** error)
{
   gboolean done = golem_expression_operation_compile(exp->exp1,
						    body,
						    scope_builder,
						    error);
  if(done)
    {
      golem_expression_operation_cast(exp->exp1,type);
      done = golem_expression_operation_compile(exp->exp2,
						body,
						scope_builder,
						error);
      if(done)
      	{
	  golem_expression_operation_cast(exp->exp2,type);
      	  golem_vm_body_write_op(body,code);
      	}
    }
  return done;
}

static gboolean
golem_expression_operation_compile(GolemExpressionOperation * exp,
				   GolemVMBody * body,
				   GolemScopeBuilder * scope_builder,
				   GError ** error)
{
  GType type = golem_expression_operation_op_type(exp,
						  scope_builder,
						  error);
  gboolean done = TRUE;
  switch(exp->operator)
  {
    case GOLEM_OPERATOR_NON:
      done = golem_statement_compile(exp->value,body,scope_builder,error);
      break;
    case GOLEM_OPERATOR_ADD:
      {
      	switch(type)
      	{
      	  case G_TYPE_CHAR:
      	  case G_TYPE_INT16:
      	  case G_TYPE_INT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_AI32,
      						       error);
      	    break;
      	  case G_TYPE_INT64:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_AI64,
      						       error);
      	    break;
      	  case G_TYPE_FLOAT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_AF32,
      						       error);
      	    break;
      	  case G_TYPE_DOUBLE:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_AD64,
      						       error);
      	    break;
      	  default:
      	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
      	}
      }
      break;
    case GOLEM_OPERATOR_SUB:
      {
      	switch(type)
      	{
      	 case G_TYPE_CHAR:
	  case G_TYPE_INT16:
	  case G_TYPE_INT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_SI32,
      						       error);
      	    break;
      	  case G_TYPE_INT64:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_SI64,
      						       error);
      	    break;
      	  case G_TYPE_FLOAT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_SF32,
      						       error);
      	    break;
      	  case G_TYPE_DOUBLE:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_SD64,
      						       error);
      	    break;
      	  default:
      	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
      	}
      }
      break;
    case GOLEM_OPERATOR_MUL:
      {
      	switch(type)
      	{
      	  case G_TYPE_CHAR:
      	  case G_TYPE_INT16:
      	  case G_TYPE_INT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_MI32,
      						       error);
      	    break;
      	  case G_TYPE_INT64:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_MI64,
      						       error);
      	    break;
      	  case G_TYPE_FLOAT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_MF32,
      						       error);
      	    break;
      	  case G_TYPE_DOUBLE:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_MD64,
      						       error);
      	    break;
      	  default:
      	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
      	}
      }
      break;
    case GOLEM_OPERATOR_DIV:
      {
      	switch(type)
      	{
      	  case G_TYPE_CHAR:
      	  case G_TYPE_INT16:
      	  case G_TYPE_INT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_DI32,
      						       error);
      	    break;
      	  case G_TYPE_INT64:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_DI64,
      						       error);
      	    break;
      	  case G_TYPE_FLOAT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_DF32,
      						       error);
      	    break;
      	  case G_TYPE_DOUBLE:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_DD64,
      						       error);
      	    break;
      	  default:
      	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
      	}
      }
      break;
    case GOLEM_OPERATOR_MOD:
      {
      	switch(type)
      	{
      	  case G_TYPE_CHAR:
      	  case G_TYPE_INT16:
      	  case G_TYPE_INT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_RI32,
      						       error);
      	    break;
      	  case G_TYPE_INT64:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_RI64,
      						       error);
      	    break;
      	  case G_TYPE_FLOAT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_RF32,
      						       error);
      	    break;
      	  case G_TYPE_DOUBLE:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_RD64,
      						       error);
      	    break;
      	  default:
      	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
      	}
      }
      break;
    case GOLEM_OPERATOR_EXP:
      done = golem_expression_operation_write_op(exp,
						 body,
						 scope_builder,
						 G_TYPE_DOUBLE,
						 GOLEM_OP_PD64,
						 error);
      break;
    case GOLEM_OPERATOR_IQL:
	switch(type)
	{
	  case G_TYPE_CHAR:
	  case G_TYPE_INT16:
	  case G_TYPE_INT:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_II32,
						       error);
	    break;
	  case G_TYPE_INT64:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_II64,
						       error);
	    break;
	  case G_TYPE_FLOAT:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_IF32,
						       error);
	    break;
	  case G_TYPE_DOUBLE:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_ID64,
						       error);
	    break;
	  case G_TYPE_POINTER:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_IP,
						       error);
	    break;
	  default:
	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
	}
      break;
    case GOLEM_OPERATOR_DST:
      switch(type)
      	{
      	  case G_TYPE_CHAR:
      	  case G_TYPE_INT16:
      	  case G_TYPE_INT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_II32,
      						       error);
      	    if(done)
      	      golem_vm_body_write_op(body,GOLEM_OP_NOT);
      	    break;
      	  case G_TYPE_INT64:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_II64,
      						       error);
      	    if(done)
	      golem_vm_body_write_op(body,GOLEM_OP_NOT);
      	    break;
      	  case G_TYPE_FLOAT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_IF32,
      						       error);
      	    if(done)
	      golem_vm_body_write_op(body,GOLEM_OP_NOT);
      	    break;
      	  case G_TYPE_DOUBLE:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_ID64,
      						       error);
      	    if(done)
	      golem_vm_body_write_op(body,GOLEM_OP_NOT);
      	    break;
      	  case G_TYPE_POINTER:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_IP,
      						       error);
      	    if(done)
	      golem_vm_body_write_op(body,GOLEM_OP_NOT);
      	    break;
      	  default:
      	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
      	}
      break;
    case GOLEM_OPERATOR_GRE:
  	switch(type)
  	{
  	  case G_TYPE_CHAR:
  	  case G_TYPE_INT16:
  	  case G_TYPE_INT:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_GI32,
  						       error);
  	    break;
  	  case G_TYPE_INT64:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_GI64,
  						       error);
  	    break;
  	  case G_TYPE_FLOAT:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_GF32,
  						       error);
  	    break;
  	  case G_TYPE_DOUBLE:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_GD64,
  						       error);
  	    break;
  	  case G_TYPE_POINTER:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_GP,
  						       error);
  	    break;
  	  default:
  	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
  	}
        break;
    case GOLEM_OPERATOR_LES:
  	switch(type)
  	{
  	  case G_TYPE_CHAR:
  	  case G_TYPE_INT16:
  	  case G_TYPE_INT:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_LI32,
  						       error);
  	    break;
  	  case G_TYPE_INT64:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_LI64,
  						       error);
  	    break;
  	  case G_TYPE_FLOAT:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_LF32,
  						       error);
  	    break;
  	  case G_TYPE_DOUBLE:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_LD64,
  						       error);
  	    break;
  	  case G_TYPE_POINTER:
  	    done = golem_expression_operation_write_op(exp,
  						       body,
  						       scope_builder,
  						       type,
  						       GOLEM_OP_LP,
  						       error);
  	    break;
  	  default:
  	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
  	}
        break;
    case GOLEM_OPERATOR_GREI:
	switch(type)
	{
	  case G_TYPE_CHAR:
	  case G_TYPE_INT16:
	  case G_TYPE_INT:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_GII32,
						       error);
	    break;
	  case G_TYPE_INT64:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_GII64,
						       error);
	    break;
	  case G_TYPE_FLOAT:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_GIF32,
						       error);
	    break;
	  case G_TYPE_DOUBLE:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_GID64,
						       error);
	    break;
	  case G_TYPE_POINTER:
	    done = golem_expression_operation_write_op(exp,
						       body,
						       scope_builder,
						       type,
						       GOLEM_OP_GIP,
						       error);
	    break;
	  default:
	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
	}
        break;
    case GOLEM_OPERATOR_LESI:
      switch(type)
      	{
      	  case G_TYPE_CHAR:
      	  case G_TYPE_INT16:
      	  case G_TYPE_INT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_LII32,
      						       error);
      	    break;
      	  case G_TYPE_INT64:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_LII64,
      						       error);
      	    break;
      	  case G_TYPE_FLOAT:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_LIF32,
      						       error);
      	    break;
      	  case G_TYPE_DOUBLE:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_LID64,
      						       error);
      	    break;
      	  case G_TYPE_POINTER:
      	    done = golem_expression_operation_write_op(exp,
      						       body,
      						       scope_builder,
      						       type,
      						       GOLEM_OP_LIP,
      						       error);
      	    break;
      	  default:
      	    golem_vm_body_write_op(body,GOLEM_OP_NULL);
      	}
      break;
    case GOLEM_OPERATOR_LAND:
    case GOLEM_OPERATOR_LOR:
      return G_TYPE_CHAR;
    default:
      {
	GType type1 = golem_expression_operation_value_type(exp->exp1,
								 scope_builder,
								 error);

	GType type2 = golem_expression_operation_value_type(exp->exp2,
								 scope_builder,
								 error);

	if(type1 == G_TYPE_DOUBLE || type2 == G_TYPE_DOUBLE)
	  return G_TYPE_DOUBLE;
	else if(type1 == G_TYPE_FLOAT || type2 == G_TYPE_FLOAT)
	  return G_TYPE_FLOAT;
	else if(type1 == G_TYPE_INT64 || type2 == G_TYPE_INT64)
	  return G_TYPE_INT64;
	else if(type1 == G_TYPE_INT || type2 == G_TYPE_INT)
	  return G_TYPE_INT;
	else if(type1 == G_TYPE_INT16 || type2 == G_TYPE_INT16)
	  return G_TYPE_INT16;
	else
	  return G_TYPE_CHAR;
      }
  }
  return done;
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
      single->exp = NULL;
      if(golem_parser_check(parser,"("))
	{
	  single->exp = golem_expression_parse_new(parser,GOLEM_EXPRESSION_LIMIT_PARENTHESIS,error);
	  if(single->exp)
	    {
	      if(!golem_parser_check(parser,")"))
		{
		  done = FALSE;
		  golem_statement_free(single->exp);
		  golem_expression_single_free(single);
		  //TODO: Expected ")"
		}
	    }
	  else
	    {
	      done = FALSE;
	    }
	}
      else
	{
	  single->exp = golem_simple_expression_parse(parser,limit,error);
	}

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
      //golem_expression_operation_print(exp->op);
    }

  g_list_free_full(operations,g_free);
  return done;
}

static void
golem_expression_init(GolemExpression * exp)
{
  exp->op = NULL;
}

static GType
golem_expression_value_type(GolemExpression * exp,
			    GolemScopeBuilder *scope_builder,
			    GError ** error)
{
  return golem_expression_operation_value_type(exp->op,scope_builder,error);
}


static gboolean
golem_expression_compile(GolemExpression * exp,
			  GolemVMBody * body,
			  GolemScopeBuilder * scope_builder,
			  GError ** error)
{
  gboolean done = golem_expression_operation_compile(exp->op,
						     body,
						     scope_builder,
						     error);
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
