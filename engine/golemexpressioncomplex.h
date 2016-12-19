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

#ifndef GOLEMEXPRESSIONCOMPLEX_H_
#define GOLEMEXPRESSIONCOMPLEX_H_

typedef struct _GolemExpressionComplexPart GolemExpressionComplexPart;
typedef struct _GolemExpressionComplexPhase GolemExpressionComplexPhase;
typedef enum _GolemOperator GolemOperator;
typedef enum _GolemExpressionLimit GolemExpressionLimit;

enum _GolemExpressionLimit
{
  GOLEM_EXPRESSION_LIMIT_SEMICOLON,
  GOLEM_EXPRESSION_LIMIT_PARENTHESIS,
  GOLEM_EXPRESSION_LIMIT_PARENTHESIS_COMA,
  GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET,
  GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET_COMA
};

enum _GolemOperator
{
  GOLEM_OPERATOR_EMP,
  GOLEM_OPERATOR_DIV,
  GOLEM_OPERATOR_MUL,
  GOLEM_OPERATOR_SUM,
  GOLEM_OPERATOR_SUB,
  GOLEM_OPERATOR_IS,
  GOLEM_OPERATOR_IN,
  GOLEM_OPERATOR_AND,
  GOLEM_OPERATOR_OR,
  GOLEM_OPERATOR_AND_BIT,
  GOLEM_OPERATOR_OR_BIT,
  GOLEM_OPERATOR_EQU,
  GOLEM_OPERATOR_DIF,
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

GType _golem_expression_complex_result_type(GValue * a,GValue * b)
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



gboolean
_golem_expression_complex_phase_evaluate(GolemExpressionComplexPhase * phase,GolemContext * context,GValue * result,GError ** error)
{
  GValue a = G_VALUE_INIT,
	 b = G_VALUE_INIT;
  gboolean done = TRUE;
  if(phase->operator == GOLEM_OPERATOR_EMP)
    {
      done = golem_expression_evalue(phase->a,context,result,error);
    }
  else if(phase->operator >= GOLEM_OPERATOR_DIV && phase->operator <= GOLEM_OPERATOR_DIF)
    {
      if((done = golem_expression_evalue(phase->a,context,&a,error)))
	{
	  if((done = golem_expression_evalue(phase->b,context,&b,error)))
	    {

	    }
	}
    }
  g_value_unset(&a);
  g_value_unset(&b);
  return done;
}

#endif /* GOLEMEXPRESSIONCOMPLEX_H_ */
