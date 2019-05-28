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
  GolemOperator op;
  GolemStatement * exp;
} GolemExpressionSingle;

GOLEM_DEFINE_STATEMENT(GolemExpression,golem_expression)

static gboolean
golem_expression_operation_compile(GolemExpressionOperation * exp,
				   GolemVMBody * body,
				   GolemScopeBuilder * scope_builder,
				   GError ** error);

static GolemMetadata *
golem_expression_operation_value_type(GolemExpressionOperation * exp,
				      GolemScopeBuilder * scope_builder,
				      GError ** error);

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
  else if (golem_statement_check(GOLEM_ACCESSOR_CLASS,parser))
      klass = GOLEM_ACCESSOR_CLASS;

  /* initialize and parse */
  if(klass)
    {
      statement = g_malloc0(klass->size);
      statement->klass = klass;
      statement->source = g_strdup(golem_parser_get_source_name(parser));
      statement->line = golem_parser_get_line(parser);
      klass->init(statement);
      ((GolemStatementExt*)statement)->base = base;
      if(!klass->parse(statement,parser,limit,error))
	{
	  golem_statement_free(statement);
	  statement = NULL;
	}
      else
	{
	  GolemStatement * next = golem_extend_expression_parse(parser,
								statement,
								limit,
								error);
	  if (next != statement)
	    statement = next;
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
  else if(golem_statement_check(GOLEM_NEG_CLASS,parser))
    klass = GOLEM_NEG_CLASS;
  else if(golem_statement_check(GOLEM_CONST_CLASS,parser))
    klass = GOLEM_CONST_CLASS;
  else if(golem_statement_check(GOLEM_CONTEXT_CLASS,parser))
    klass = GOLEM_CONTEXT_CLASS;


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
      g_print("Error expr");
      /*g_propagate_error(error,
	      g_error_new(GOLEM_ERROR,
			GOLEM_COMPILE_ERROR_SYNTAXES,
			"%s: %d: can't solve syntaxes \"%s\"",
			golem_parser_get_source_name(parser),
			golem_parser_get_line(parser),
			golem_parser_next_word(parser,FALSE))
      );*/
    }
  return statement;
}

static gbool_t
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
      op->op = GOLEM_OPERATOR_NON;
      op->value = single->exp;
    }
  else if(g_list_next(start) == end)
    {
      single = (GolemExpressionSingle*) end->data;
      op->op = single->op;
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
	  if(single_iter->op <= single->op)
	    min = iter;
	}
      single = (GolemExpressionSingle*) min->data;
      op->op = single->op;
      op->exp1 = golem_expression_operation_new(start,g_list_previous(min));
      op->exp2 = golem_expression_operation_new(min,end);
    }
  return op;
}

static gboolean
_golem_metadata_is_int32(GolemMetadata * metadata)
{
  return (metadata == GOLEM_TYPE_INT||
        metadata == GOLEM_TYPE_SHORT||
        metadata == GOLEM_TYPE_SBYTE||
        metadata == GOLEM_TYPE_CHAR||
	metadata == GOLEM_TYPE_UINT||
	metadata == GOLEM_TYPE_USHORT||
	metadata == GOLEM_TYPE_BYTE||
	metadata == GOLEM_TYPE_UCHAR)||
	metadata == GOLEM_TYPE_BOOL;
}

static gboolean
_golem_metadata_is_int(GolemMetadata * metadata)
{
  return (metadata == GOLEM_TYPE_INT128 ||
	  metadata == GOLEM_TYPE_UINT128 ||
          metadata == GOLEM_TYPE_LONG ||
	  metadata == GOLEM_TYPE_ULONG ||
  	  _golem_metadata_is_int32(metadata));
}

static gboolean
_golem_metadata_is_float(GolemMetadata * metadata)
{
  return (metadata == GOLEM_TYPE_FLOAT ||
          metadata == GOLEM_TYPE_DOUBLE ||
	  metadata == GOLEM_TYPE_QUAD);
}

static GolemMetadata *
golem_expression_operation_op_type(GolemExpressionOperation * exp,
				   GolemScopeBuilder * scope_builder,
				   GError ** error)
{
  if(exp->op == GOLEM_OPERATOR_NON)
    return golem_statement_value_type(exp->value,scope_builder,error);

  GolemMetadata * type1 = golem_expression_operation_value_type(exp->exp1,
							     scope_builder,
							     error);

  GolemMetadata * type2 = golem_expression_operation_value_type(exp->exp2,
							   scope_builder,
							   error);

  if (type1 == type2)
    {
      return type1;
    }
  else
    {
      if (_golem_metadata_is_float(type1) && _golem_metadata_is_float(type2))
	{
	  //Float operation
	  if (type1 == GOLEM_TYPE_QUAD || type2 == GOLEM_TYPE_QUAD)
	    return GOLEM_TYPE_QUAD;
	  else if (type1 == GOLEM_TYPE_DOUBLE || type2 == GOLEM_TYPE_DOUBLE)
	    return GOLEM_TYPE_DOUBLE;
	  else
	    return GOLEM_TYPE_FLOAT;
	}
      else if (_golem_metadata_is_int(type1) && _golem_metadata_is_int(type2))
      	{
      	  //Integer operation
	  if (type1 == GOLEM_TYPE_INT128 || type2 == GOLEM_TYPE_INT128)
	    return GOLEM_TYPE_INT128;
	  else if (type1 == GOLEM_TYPE_LONG || type2 == GOLEM_TYPE_LONG)
	    return GOLEM_TYPE_LONG;
	  else if (type1 == GOLEM_TYPE_INT || type2 == GOLEM_TYPE_INT)
	    return GOLEM_TYPE_INT;
	  else if (type1 == GOLEM_TYPE_SHORT || type2 == GOLEM_TYPE_SHORT)
	    return GOLEM_TYPE_SHORT;
	  else
	    return GOLEM_TYPE_SBYTE;
      	}
      else if (
	  (_golem_metadata_is_float(type1) && _golem_metadata_is_int(type2))||
	  (_golem_metadata_is_int(type1) && _golem_metadata_is_float(type2)))
      	{
      	  //Float and Integer operation
	  if (type1 == GOLEM_TYPE_QUAD || type2 == GOLEM_TYPE_QUAD)
	     return GOLEM_TYPE_QUAD;
	  else if (type1 == GOLEM_TYPE_DOUBLE || type2 == GOLEM_TYPE_DOUBLE)
	     return GOLEM_TYPE_DOUBLE;
	  else
	     return GOLEM_TYPE_FLOAT;
      	}
      else
	{
	  //TODO: Throw exception invalid operation types
	  g_print("Invalid");
	  return NULL;
	}
    }

}

static GolemMetadata *
golem_expression_operation_value_type(GolemExpressionOperation * exp,
				      GolemScopeBuilder * scope_builder,
				      GError ** error)
{
  switch(exp->op)
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
      return GOLEM_TYPE_BOOL;
    case GOLEM_OPERATOR_EXP:
      return GOLEM_TYPE_QUAD;
    default:
      return golem_expression_operation_op_type(exp,scope_builder,error);
  }
}

static void
golem_expression_operation_cast(GolemExpressionOperation * exp,
				GolemMetadata * type,
				GolemVMBody * body,
				GolemScopeBuilder * scope_builder,
				GError ** error)
{
  GolemMetadata * exp_type = golem_expression_operation_value_type(exp,
								   scope_builder,
								   error);
  if (type == GOLEM_TYPE_QUAD && _golem_metadata_is_int(exp_type))
    golem_vm_body_write_op(body,GOLEM_OP_I128TF128);
  else if (type == GOLEM_TYPE_DOUBLE && _golem_metadata_is_int(exp_type))
    golem_vm_body_write_op(body,GOLEM_OP_I64TF64);
  else if (type == GOLEM_TYPE_FLOAT && _golem_metadata_is_int(exp_type))
    golem_vm_body_write_op(body,GOLEM_OP_I32TF32);
}

static gboolean
golem_expression_operation_write_op(GolemExpressionOperation * exp,
				   GolemVMBody * body,
				   GolemScopeBuilder * scope_builder,
				   GolemMetadata * type,
				   GolemVMOpCode code,
				   GError ** error)
{
   gboolean done = golem_expression_operation_compile(exp->exp1,
						    body,
						    scope_builder,
						    error);
  if(done)
    {
      golem_expression_operation_cast(exp->exp1,type,body,scope_builder,error);
      done = golem_expression_operation_compile(exp->exp2,
						body,
						scope_builder,
						error);
      if(done)
      	{
	  golem_expression_operation_cast(exp->exp2,type,body,scope_builder,error);
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
  #define OP_EXPR(OP) \
  switch (type)\
  {\
  case GOLEM_PRIMITIVE_TYPE_BOOL:\
  case GOLEM_PRIMITIVE_TYPE_CHAR:\
  case GOLEM_PRIMITIVE_TYPE_UCHAR:\
  case GOLEM_PRIMITIVE_TYPE_INT8:\
  case GOLEM_PRIMITIVE_TYPE_UINT8:\
  case GOLEM_PRIMITIVE_TYPE_INT16:\
  case GOLEM_PRIMITIVE_TYPE_UINT16:\
  case GOLEM_PRIMITIVE_TYPE_INT32:\
  case GOLEM_PRIMITIVE_TYPE_UINT32:\
    done = golem_expression_operation_write_op(\
	exp,\
	body,\
	scope_builder,\
	metadata,\
	GOLEM_OP_##OP##I32,\
	error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_INT64:\
  case GOLEM_PRIMITIVE_TYPE_UINT64:\
    done = golem_expression_operation_write_op(\
	exp,\
	body,\
	scope_builder,\
	metadata,\
	GOLEM_OP_##OP##I64,\
	error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_INT128:\
  case GOLEM_PRIMITIVE_TYPE_UINT128:\
    done = golem_expression_operation_write_op(\
	  exp,\
	  body,\
	  scope_builder,\
	  metadata,\
	  GOLEM_OP_##OP##I128,\
	  error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_FLOAT32:\
    done = golem_expression_operation_write_op(\
	  exp,\
	  body,\
	  scope_builder,\
	  metadata,\
	  GOLEM_OP_##OP##F32,\
	  error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_FLOAT64:\
    done = golem_expression_operation_write_op(\
	  exp,\
	  body,\
	  scope_builder,\
	  metadata,\
	  GOLEM_OP_##OP##F64,\
	  error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_FLOAT128:\
    done = golem_expression_operation_write_op(\
	  exp,\
	  body,\
	  scope_builder,\
	  metadata,\
	  GOLEM_OP_##OP##F128,\
	  error);\
    break;\
  default:\
    break;\
  }\

  #define OP_CMP(OP) \
  switch (type)\
  {\
  case GOLEM_PRIMITIVE_TYPE_BOOL:\
  case GOLEM_PRIMITIVE_TYPE_CHAR:\
  case GOLEM_PRIMITIVE_TYPE_UCHAR:\
  case GOLEM_PRIMITIVE_TYPE_INT8:\
  case GOLEM_PRIMITIVE_TYPE_UINT8:\
  case GOLEM_PRIMITIVE_TYPE_INT16:\
  case GOLEM_PRIMITIVE_TYPE_UINT16:\
  case GOLEM_PRIMITIVE_TYPE_INT32:\
  case GOLEM_PRIMITIVE_TYPE_UINT32:\
    done = golem_expression_operation_write_op(\
	  exp,\
	  body,\
	  scope_builder,\
	  metadata,\
	  GOLEM_OP_##OP##I32,\
	  error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_INT64:\
  case GOLEM_PRIMITIVE_TYPE_UINT64:\
    done = golem_expression_operation_write_op(\
	  exp,\
	  body,\
	  scope_builder,\
	  metadata,\
	  GOLEM_OP_##OP##I64,\
	  error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_INT128:\
  case GOLEM_PRIMITIVE_TYPE_UINT128:\
    done = golem_expression_operation_write_op(\
	    exp,\
	    body,\
	    scope_builder,\
	    metadata,\
	    GOLEM_OP_##OP##I128,\
	    error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_FLOAT32:\
    done = golem_expression_operation_write_op(\
	    exp,\
	    body,\
	    scope_builder,\
	    metadata,\
	    GOLEM_OP_##OP##F32,\
	    error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_FLOAT64:\
    done = golem_expression_operation_write_op(\
	    exp,\
	    body,\
	    scope_builder,\
	    metadata,\
	    GOLEM_OP_##OP##F64,\
	    error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_FLOAT128:\
    done = golem_expression_operation_write_op(\
	    exp,\
	    body,\
	    scope_builder,\
	    metadata,\
	    GOLEM_OP_##OP##F128,\
	    error);\
    break;\
  case GOLEM_PRIMITIVE_TYPE_POINTER:\
    done = golem_expression_operation_write_op(\
	    exp,\
	    body,\
	    scope_builder,\
	    metadata,\
	    GOLEM_OP_##OP##P,\
	    error);\
    break;\
  default:\
    break;\
  }\


  GolemMetadata * metadata = golem_expression_operation_op_type(exp,
						  scope_builder,
						  error);

  GolemPrimitiveType type = GOLEM_PRIMITIVE_TYPE_INT32;

  if (!GOLEM_IS_PRIMITIVE(metadata))
    {
      g_print("None: %d\n",exp->op);
      //TODO: throw exception non primitive operation
      return FALSE;
    }
  else
    {
      type = golem_primitive_get_primitive_type(GOLEM_PRIMITIVE(metadata));
    }

  gboolean done = TRUE;
  switch(exp->op)
  {
  case GOLEM_OPERATOR_NON:
    done = golem_statement_compile(exp->value,body,scope_builder,error);
    break;
  case GOLEM_OPERATOR_ADD:
    OP_EXPR(A)
    break;
  case GOLEM_OPERATOR_MUL:
    OP_EXPR(M)
    break;
  case GOLEM_OPERATOR_SUB:
    OP_EXPR(S)
    break;
  case GOLEM_OPERATOR_DIV:
    OP_EXPR(D)
    break;
  case GOLEM_OPERATOR_IQL:
    OP_CMP(I)
    break;
  case GOLEM_OPERATOR_GRE:
    OP_CMP(G)
    break;
  case GOLEM_OPERATOR_LES:
    OP_CMP(L)
    break;
  case GOLEM_OPERATOR_GREI:
    OP_CMP(GI)
    break;
  case GOLEM_OPERATOR_LESI:
    OP_CMP(LI)
    break;
  case GOLEM_OPERATOR_DST:
    OP_CMP(I)
    switch (type)
    {
      case GOLEM_PRIMITIVE_TYPE_INT128:
      case GOLEM_PRIMITIVE_TYPE_UINT128:
      case GOLEM_PRIMITIVE_TYPE_FLOAT128:
      	golem_vm_body_write_op(body,GOLEM_OP_NT128);
      	break;
      case GOLEM_PRIMITIVE_TYPE_INT64:
      case GOLEM_PRIMITIVE_TYPE_UINT64:
      case GOLEM_PRIMITIVE_TYPE_FLOAT64:
	golem_vm_body_write_op(body,GOLEM_OP_NT64);
	break;
      default:
	golem_vm_body_write_op(body,GOLEM_OP_NT32);
    }
    break;
  default:
    break;
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
      single->op = operator;
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
	      else
		{
		  single->exp = golem_extend_expression_parse(parser,
							      single->exp,
							      limit,
							      error);
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
    }

  g_list_free_full(operations,g_free);
  return done;
}

static void
golem_expression_init(GolemExpression * exp)
{
  exp->op = NULL;
}

static GolemMetadata *
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
