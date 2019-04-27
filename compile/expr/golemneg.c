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


#include "../../golem.h"

GOLEM_DEFINE_STATEMENT(GolemNeg,golem_neg)

static void
golem_neg_init(GolemNeg * negative)
{
  negative->value = NULL;
}

static GolemMetadata *
golem_neg_value_type(GolemNeg * negative,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
    return golem_statement_value_type(negative->value,scope_builder,error);
}


static gboolean
golem_neg_compile(GolemNeg * negative,
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
      GolemMetadata * metadata = golem_statement_value_type(negative->value,
      						       scope_builder,
      						       error);
      //TODO: check is primitive

      GolemPrimitiveType type_code = golem_primitive_get_primitive_type(
	  GOLEM_PRIMITIVE(metadata));

      switch(type_code)
      {
	case GOLEM_PRIMITIVE_TYPE_BOOL:
	case GOLEM_PRIMITIVE_TYPE_CHAR:
	case GOLEM_PRIMITIVE_TYPE_UCHAR:
	case GOLEM_PRIMITIVE_TYPE_INT8:
	case GOLEM_PRIMITIVE_TYPE_UINT8:
	case GOLEM_PRIMITIVE_TYPE_INT16:
	case GOLEM_PRIMITIVE_TYPE_UINT16:
	case GOLEM_PRIMITIVE_TYPE_INT32:
	case GOLEM_PRIMITIVE_TYPE_UINT32:
	  golem_vm_body_write_op(body,GOLEM_OP_NI32);
	  break;
	case GOLEM_PRIMITIVE_TYPE_INT64:
	case GOLEM_PRIMITIVE_TYPE_UINT64:
	  golem_vm_body_write_op(body,GOLEM_OP_NI64);
	  break;
	case GOLEM_PRIMITIVE_TYPE_INT128:
	case GOLEM_PRIMITIVE_TYPE_UINT128:
	  golem_vm_body_write_op(body,GOLEM_OP_NI128);
	  break;
	case GOLEM_PRIMITIVE_TYPE_FLOAT32:
	  golem_vm_body_write_op(body,GOLEM_OP_NF32);
	  break;
	case GOLEM_PRIMITIVE_TYPE_FLOAT64:
	  golem_vm_body_write_op(body,GOLEM_OP_NF64);
	  break;
	case GOLEM_PRIMITIVE_TYPE_FLOAT128:
	  golem_vm_body_write_op(body,GOLEM_OP_NF128);
	  break;
	default:
	  done = FALSE;
	  g_print("Type unsupported");
	  //TODO: throw type unsupported
      }
    }
  return done;
}


static gboolean
golem_neg_parse(GolemNeg * negative,
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
golem_neg_dispose(GolemNeg * negative)
{
  if(negative->value)
    golem_statement_free(negative->value);
}

static gboolean
golem_neg_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"-");
}
