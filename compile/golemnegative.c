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

GOLEM_DEFINE_STATEMENT(GolemNegative,golem_negative)

static void
golem_negative_init(GolemNegative * negative)
{
  negative->value = NULL;
}

static GolemTypeCode
golem_negative_value_type(GolemNegative * negative,
			   GolemScopeBuilder *scope_builder,
			   GError ** error)
{
    return golem_statement_value_type(negative->value,scope_builder,error);
}


static gboolean
golem_negative_compile(GolemNegative * negative,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = golem_statement_compile(negative->value,
				  body,
				  scope_builder,
				  error);
  if(done)
    {
      GolemTypeCode type_code = golem_statement_value_type(negative->value,
      						       scope_builder,
      						       error);
      switch(type_code)
      {
	case GOLEM_TYPE_CODE_INT8:
	case GOLEM_TYPE_CODE_UINT8:
	case GOLEM_TYPE_CODE_INT16:
	case GOLEM_TYPE_CODE_UINT16:
	case GOLEM_TYPE_CODE_INT32:
	case GOLEM_TYPE_CODE_UINT32:
	  golem_vm_body_write_op(body,GOLEM_OP_NI32);
	  break;
	case GOLEM_TYPE_CODE_INT64:
	case GOLEM_TYPE_CODE_UINT64:
	  golem_vm_body_write_op(body,GOLEM_OP_NI64);
	  break;
	case GOLEM_TYPE_CODE_FLOAT:
	  golem_vm_body_write_op(body,GOLEM_OP_NF32);
	  break;
	case GOLEM_TYPE_CODE_DOUBLE:
	  golem_vm_body_write_op(body,GOLEM_OP_ND64);
	  break;
	default:
	  done = FALSE;
	  //TODO: throw type unsupported
      }
    }
  return done;
}


static gboolean
golem_negative_parse(GolemNegative * negative,
		GolemParser * parser,
		GolemExpressionLimit limit,
		GError ** error)
{
  gboolean done = TRUE;
  if((done = golem_parser_check(parser,"-")))
    {
      negative->value = golem_simple_expression_parse(parser,
						 limit,
						 error);
      done = negative->value != NULL;
    }
  return done;
}

static void
golem_negative_dispose(GolemNegative * negative)
{
  if(negative->value)
    golem_statement_free(negative->value);
}

static gboolean
golem_negative_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"-");
}
