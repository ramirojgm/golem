/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "golem.h"

typedef struct _GolemExpressionComplexPart GolemExpressionComplexPart;
typedef struct _GolemExpressionComplexPhase GolemExpressionComplexPhase;
typedef enum _GolemOperator GolemOperator;


enum _GolemOperator
{
  GOLEM_OPERATOR_EMP,
  GOLEM_OPERATOR_DIV,
  GOLEM_OPERATOR_MUL,
  GOLEM_OPERATOR_ADD,
  GOLEM_OPERATOR_SUB,
  GOLEM_OPERATOR_IS,
  GOLEM_OPERATOR_IN,
  GOLEM_OPERATOR_EQU,
  GOLEM_OPERATOR_DIF,
  GOLEM_OPERATOR_AND_BIT,
  GOLEM_OPERATOR_OR_BIT,
  GOLEM_OPERATOR_OR,
  GOLEM_OPERATOR_AND,
  GOLEM_OPERATOR_NOT,
  GOLEM_OPERATOR_NONE
};

struct _GolemExpressionComplexPart
{
  GolemOperator operator;
  GolemExpression * expression;
};

struct _GolemExpressionComplexPhase
{
  GolemOperator operator;
  GolemExpression * a, *b;
};

static GType _golem_expression_complex_result_type(GValue * a,GValue * b)
{
  if((G_VALUE_TYPE(a) == G_TYPE_NONE)||(G_VALUE_TYPE(b) == G_TYPE_NONE))
    return G_TYPE_NONE;
  if((G_VALUE_TYPE(a) == G_TYPE_DOUBLE)||(G_VALUE_TYPE(b) == G_TYPE_DOUBLE))
    return G_TYPE_DOUBLE;
  else if((G_VALUE_TYPE(a) == G_TYPE_FLOAT)||(G_VALUE_TYPE(b) == G_TYPE_FLOAT))
    return G_TYPE_FLOAT;
  else if((G_VALUE_TYPE(a) == G_TYPE_LONG)||(G_VALUE_TYPE(b) == G_TYPE_LONG))
    return G_TYPE_LONG;
  else if((G_VALUE_TYPE(a) == G_TYPE_INT64)||(G_VALUE_TYPE(b) == G_TYPE_INT64))
    return G_TYPE_INT64;
  else if((G_VALUE_TYPE(a) == G_TYPE_INT)||(G_VALUE_TYPE(b) == G_TYPE_INT))
    return G_TYPE_INT;
  else if((G_VALUE_TYPE(a) == G_TYPE_BOOLEAN)||(G_VALUE_TYPE(b) == G_TYPE_BOOLEAN))
    return G_TYPE_BOOLEAN;
  else if((G_VALUE_TYPE(a) == G_TYPE_CHAR)||(G_VALUE_TYPE(b) == G_TYPE_CHAR))
    return G_TYPE_CHAR;
  else if((G_VALUE_TYPE(a) == G_TYPE_ULONG)||(G_VALUE_TYPE(b) == G_TYPE_ULONG))
     return G_TYPE_ULONG;
   else if((G_VALUE_TYPE(a) == G_TYPE_UINT64)||(G_VALUE_TYPE(b) == G_TYPE_UINT64))
     return G_TYPE_UINT64;
   else if((G_VALUE_TYPE(a) == G_TYPE_UINT)||(G_VALUE_TYPE(b) == G_TYPE_UINT))
     return G_TYPE_UINT;
   else if((G_VALUE_TYPE(a) == G_TYPE_UCHAR)||(G_VALUE_TYPE(b) == G_TYPE_UCHAR))
     return G_TYPE_UCHAR;
   else
     return G_TYPE_POINTER;
}

static void
_golem_expression_complex_value_set(GValue * dest,gdouble value){
  switch(G_VALUE_TYPE(dest)){
    case G_TYPE_CHAR:
      g_value_set_schar(dest,(gchar)value);
      break;
    case G_TYPE_INT:
      g_value_set_int(dest,(gint)value);
      break;
    case G_TYPE_LONG:
      g_value_set_long(dest,(glong)value);
      break;
    case G_TYPE_INT64:
      g_value_set_int64(dest,(gint64)value);
      break;
    case G_TYPE_UCHAR:
      g_value_set_uchar(dest,(guchar)value);
      break;
    case G_TYPE_UINT:
      g_value_set_uint(dest,(guint)value);
      break;
    case G_TYPE_ULONG:
      g_value_set_long(dest,(gulong)value);
      break;
    case G_TYPE_UINT64:
      g_value_set_uint64(dest,(guint64)value);
      break;
    case G_TYPE_DOUBLE:
      g_value_set_double(dest,(gdouble)value);
      break;
    case G_TYPE_FLOAT:
      g_value_set_float(dest,(gfloat)value);
      break;
  }
}

static gboolean
_golem_expression_complex_phase_evaluate(GolemExpressionComplexPhase * phase,GolemContext * context,GValue * result,GError ** error)
{
  GValue a = G_VALUE_INIT,
	 b = G_VALUE_INIT;
  gboolean done = TRUE;
  if(phase->operator == GOLEM_OPERATOR_EMP)
    {
      done = golem_expression_evaluate(phase->a,context,result,error);
    }
  else if(phase->operator >= GOLEM_OPERATOR_DIV && phase->operator <= GOLEM_OPERATOR_OR)
    {
      if((done = golem_expression_evaluate(phase->a,context,&a,error)))
	{
	  if((done = golem_expression_evaluate(phase->b,context,&b,error)))
	    {
	      g_value_init(result,_golem_expression_complex_result_type(&a,&b));
	      if(phase->operator == GOLEM_OPERATOR_DIV){
		  gdouble value_a = g_value_get_double(&a);
		  gdouble value_b = g_value_get_double(&b);
		  _golem_expression_complex_value_set(result,value_a / value_b);
	      }
	      else if(phase->operator == GOLEM_OPERATOR_MUL){
		  gdouble value_a = g_value_get_double(&a);
		  gdouble value_b = g_value_get_double(&b);
		  _golem_expression_complex_value_set(result,value_a * value_b);
	      }
	      else if(phase->operator == GOLEM_OPERATOR_ADD){
		  gdouble value_a = g_value_get_double(&a);
		  gdouble value_b = g_value_get_double(&b);
		  _golem_expression_complex_value_set(result,value_a + value_b);
	      }
	      else if(phase->operator == GOLEM_OPERATOR_SUB){
		  gdouble value_a = g_value_get_double(&a);
		  gdouble value_b = g_value_get_double(&b);
		  _golem_expression_complex_value_set(result,value_a - value_b);
	      }
	    }
	}
    }
  g_value_unset(&a);
  g_value_unset(&b);
  return done;
}
