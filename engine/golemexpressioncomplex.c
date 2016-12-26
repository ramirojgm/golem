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

struct _GolemExpressionComplexPrivate
{
  GolemExpressionComplexPhase * phase;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemExpressionComplex,golem_expression_complex,GOLEM_TYPE_EXPRESSION)

enum _GolemOperator
{
  GOLEM_OPERATOR_POW,
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
  GolemExpressionComplexPhase * a, *b;
  GolemExpression * value;
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
  if(phase->value)
    {
      done = golem_expression_evaluate(phase->value,context,result,error);
    }
  else if(phase->operator >= GOLEM_OPERATOR_DIV && phase->operator <= GOLEM_OPERATOR_OR)
    {
      if((done = _golem_expression_complex_phase_evaluate(phase->a,context,&a,error)))
	{
	  if((done = _golem_expression_complex_phase_evaluate(phase->b,context,&b,error)))
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

gboolean
golem_expression_complex_check_continue(GolemParser * parser,GolemExpressionLimit limit)
{
  const gchar * wd = golem_parser_next_word(parser,NULL,FALSE);
  switch(limit)
  {
    case GOLEM_EXPRESSION_LIMIT_PARENTHESIS_COMA:
      if((*wd != ',') || (*wd != ')'))
    	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_PARENTHESIS:
      if(*wd != ')')
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET_COMA:
      if((*wd != ',') || (*wd != ']'))
	    return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET:
      if(*wd != ']')
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_SEMICOLON:
      if(*wd != ';')
	return TRUE;
      break;
  }
  return FALSE;
}

GList *
g_list_slice(GList * start,gboolean reverse)
{
  GList * new_list = NULL;
  if(reverse)
    {
      for(GList * iter = start;iter;iter = iter->prev)
	new_list = g_list_append(new_list,iter->data);
      new_list = g_list_reverse(new_list);
    }
  else
    {
      for(GList * iter = start;iter;iter = iter->next)
      	new_list = g_list_append(new_list,iter->data);
    }
  return new_list;
}

GolemExpressionComplexPhase *
golem_expression_complex_phase_build(GList * parts,GolemOperator level)
{
  GolemExpressionComplexPhase * phase = g_new0(GolemExpressionComplexPhase,1);
  if(g_list_length(parts) == 1)
    {
      phase->operator = GOLEM_OPERATOR_NONE;
      phase->value = ((GolemExpressionComplexPart*)parts->data)->expression;
      phase->a = NULL;
      phase->b = NULL;
    }
  else if(g_list_length(parts) >= 2)
    {
      GList * min_op = NULL;
      for(GList * iter = parts;iter;iter = iter->next)
        {
	  GolemExpressionComplexPart* part = ((GolemExpressionComplexPart*) iter->data);
	  if(!min_op)
	    {
	      min_op = iter;
	    }
	  else
	    {
	      if((((GolemExpressionComplexPart*)min_op->data)->operator < part->operator)||(((GolemExpressionComplexPart*)min_op->data)->operator == GOLEM_OPERATOR_NONE))
		min_op = iter;
	    }
        }
      if(min_op)
	{
	  GolemExpressionComplexPart* part = ((GolemExpressionComplexPart*) min_op->data);
	  phase->operator = part->operator;
	  part->operator = GOLEM_OPERATOR_NONE;
	  GList * left,*right;
	  left = g_list_slice(min_op->prev,TRUE);
	  right = g_list_slice(min_op,FALSE);
	  phase->a = golem_expression_complex_phase_build(left,phase->operator);
	  phase->b = golem_expression_complex_phase_build(right,phase->operator);
	  phase->value = NULL;
	  g_list_free(left);
	  g_list_free(right);
	}
    }
  else
    {
      g_print("<0");
      abort();
    }
  return phase;
}

GolemExpression *
golem_expression_complex_parse(GolemParser * parser,GolemExpressionLimit limit, GError ** error)
{
  GolemExpressionComplex * expression = NULL;
  GolemOperator op = GOLEM_OPERATOR_NONE;
  GList * expression_parts = NULL;
  while(golem_expression_complex_check_continue(parser,limit))
    {
      if(golem_parser_next_word_check(parser,"!"))
	op = GOLEM_OPERATOR_NOT;
      else if(golem_parser_next_word_check(parser,"*"))
	{
	  if(golem_parser_next_word_check(parser,"*"))
	    op = GOLEM_OPERATOR_POW;
	  else
	    op = GOLEM_OPERATOR_MUL;
	}
      else if(golem_parser_next_word_check(parser,"/"))
      	op = GOLEM_OPERATOR_DIV;
      else if(golem_parser_next_word_check(parser,"+"))
      	op = GOLEM_OPERATOR_ADD;
      else if(golem_parser_next_word_check(parser,"-"))
      	op = GOLEM_OPERATOR_SUB;
      else if(golem_parser_next_word_check(parser,"in"))
      	op = GOLEM_OPERATOR_IN;
      else if(golem_parser_next_word_check(parser,"is"))
      	op = GOLEM_OPERATOR_IS;
      else if(golem_parser_next_word_check(parser,"&"))
	{
	  if(golem_parser_next_word_check(parser,"&"))
	    op = GOLEM_OPERATOR_AND;
	  else
	    op = GOLEM_OPERATOR_AND_BIT;
	}
      else if(golem_parser_next_word_check(parser,"|"))
      	{
      	  if(golem_parser_next_word_check(parser,"|"))
      	    op = GOLEM_OPERATOR_OR;
      	  else
      	    op = GOLEM_OPERATOR_OR_BIT;
      	}
      else if(golem_constant_check(parser))
	{
	  GolemExpressionComplexPart * part = g_new0(GolemExpressionComplexPart,1);
	  part->expression = golem_constant_parse(parser,error);
	  part->operator = op;
	  expression_parts = g_list_append(expression_parts,part);
	}
      else
	{
	  //TODO: throw exception expected operator, constant or identificator
	}
    }
  expression = GOLEM_EXPRESSION_COMPLEX(g_object_new(GOLEM_TYPE_EXPRESSION_COMPLEX,NULL));
  expression->priv->phase = golem_expression_complex_phase_build(g_list_first(expression_parts),GOLEM_OPERATOR_NONE);
  g_list_free(expression_parts);
  return GOLEM_EXPRESSION(expression);
}

static gboolean
golem_expression_complex_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemExpressionComplex * self = GOLEM_EXPRESSION_COMPLEX(expression);
  return _golem_expression_complex_phase_evaluate(self->priv->phase,context,result,error);
}

static void
golem_expression_complex_init(GolemExpressionComplex * self)
{
  self->priv = golem_expression_complex_get_instance_private(self);
}

static void
golem_expression_complex_class_init(GolemExpressionComplexClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = golem_expression_complex_evaluate;
}
