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
#include <stdlib.h>

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
  GOLEM_OPERATOR_LES,
  GOLEM_OPERATOR_GRE,
  GOLEM_OPERATOR_LES_EQU,
  GOLEM_OPERATOR_GRE_EQU,
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
   else if((G_VALUE_TYPE(a) == G_TYPE_STRING)||(G_VALUE_TYPE(b) == G_TYPE_STRING))
     return G_TYPE_STRING;
   else
     return G_TYPE_POINTER;
}


#define GOLEM_ARITMETICAL(type_name,op,val_a,val_b)\
  switch(op)\
  {\
   case GOLEM_OPERATOR_ADD:\
     g_value_set_##type_name(result,g_value_get_##type_name(&val_a) + g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_SUB:\
     g_value_set_##type_name(result,g_value_get_##type_name(&val_a) - g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_DIV:\
     g_value_set_##type_name(result,g_value_get_##type_name(&val_a) / g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_MUL:\
     g_value_set_##type_name(result,g_value_get_##type_name(&val_a) * g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_LES:\
     if(!G_VALUE_HOLDS_BOOLEAN(result))\
      {\
	g_value_unset(result);\
	g_value_init(result,G_TYPE_BOOLEAN);\
      }\
     g_value_set_boolean(result,g_value_get_##type_name(&val_a) < g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_GRE:\
     if(!G_VALUE_HOLDS_BOOLEAN(result))\
      {\
  	g_value_unset(result);\
  	g_value_init(result,G_TYPE_BOOLEAN);\
      }\
     g_value_set_boolean(result,g_value_get_##type_name(&val_a) > g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_LES_EQU:\
     if(!G_VALUE_HOLDS_BOOLEAN(result))\
      {\
  	g_value_unset(result);\
  	g_value_init(result,G_TYPE_BOOLEAN);\
      }\
     g_value_set_boolean(result,g_value_get_##type_name(&val_a) <= g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_GRE_EQU:\
     if(!G_VALUE_HOLDS_BOOLEAN(result))\
      {\
  	g_value_unset(result);\
  	g_value_init(result,G_TYPE_BOOLEAN);\
      }\
     g_value_set_boolean(result,g_value_get_##type_name(&val_a) >= g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_EQU:\
     if(!G_VALUE_HOLDS_BOOLEAN(result))\
      {\
  	g_value_unset(result);\
  	g_value_init(result,G_TYPE_BOOLEAN);\
      }\
     g_value_set_boolean(result,g_value_get_##type_name(&val_a) == g_value_get_##type_name(&val_b));\
     break;\
   case GOLEM_OPERATOR_DIF:\
     if(!G_VALUE_HOLDS_BOOLEAN(result))\
      {\
  	g_value_unset(result);\
  	g_value_init(result,G_TYPE_BOOLEAN);\
      }\
     g_value_set_boolean(result,g_value_get_##type_name(&val_a) != g_value_get_##type_name(&val_b));\
     break;\
   default:\
     g_value_unset(result);\
  }

static void
_golem_expression_complex_operator_aritmetical(GValue * a,GValue * b,GValue * result,GolemOperator op)
{
  GType optimal_type = _golem_expression_complex_result_type(a,b);
  GValue optimal_a = G_VALUE_INIT,
 	 optimal_b = G_VALUE_INIT;

  g_value_init(&optimal_a,optimal_type);
  g_value_init(&optimal_b,optimal_type);
  if(!G_VALUE_HOLDS(result,optimal_type))
    {
      g_value_unset(result);
      g_value_init(result,optimal_type);
    }

  g_value_transform(a,&optimal_a);
  g_value_transform(b,&optimal_b);

  switch(optimal_type)
  {
     case G_TYPE_BOOLEAN:
       GOLEM_ARITMETICAL(boolean,op,optimal_a,optimal_b)
       break;
     case G_TYPE_CHAR:
       GOLEM_ARITMETICAL(schar,op,optimal_a,optimal_b)
       break;
     case G_TYPE_INT:
       GOLEM_ARITMETICAL(int,op,optimal_a,optimal_b)
       break;
     case G_TYPE_LONG:
       GOLEM_ARITMETICAL(long,op,optimal_a,optimal_b)
       break;
     case G_TYPE_INT64:
       GOLEM_ARITMETICAL(int64,op,optimal_a,optimal_b)
       break;
     case G_TYPE_UCHAR:
       GOLEM_ARITMETICAL(uchar,op,optimal_a,optimal_b)
       break;
     case G_TYPE_UINT:
       GOLEM_ARITMETICAL(uint,op,optimal_a,optimal_b)
       break;
     case G_TYPE_ULONG:
       GOLEM_ARITMETICAL(ulong,op,optimal_a,optimal_b)
       break;
     case G_TYPE_UINT64:
       GOLEM_ARITMETICAL(uint64,op,optimal_a,optimal_b)
       break;
     case G_TYPE_DOUBLE:
       GOLEM_ARITMETICAL(double,op,optimal_a,optimal_b)
       break;
     case G_TYPE_FLOAT:
       GOLEM_ARITMETICAL(float,op,optimal_a,optimal_b)
       break;
     case G_TYPE_STRING:
       {
       	 const gchar * str1 = g_value_get_string(&optimal_a);
       	 const gchar * str2 = g_value_get_string(&optimal_b);
       	 g_value_unset(result);
       	 g_value_init(result,G_TYPE_BOOLEAN);
       	 switch(op)
       	 {
       	   case GOLEM_OPERATOR_EQU:
       	     g_value_set_boolean(result,g_strcmp0(str1,str2) == 0);
       	     break;
       	   case GOLEM_OPERATOR_DIF:
       	     g_value_set_boolean(result,g_strcmp0(str1,str2) != 0);
       	     break;
       	   default:
       	     break;
       	 }
	}
	break;
     case G_TYPE_POINTER:
       {
	 gpointer pointer_a = g_value_get_pointer(&optimal_a);
	 gpointer pointer_b = g_value_get_pointer(&optimal_b);
	 g_value_unset(result);
	 g_value_init(result,G_TYPE_BOOLEAN);
	 switch(op)
	 {
	   case GOLEM_OPERATOR_EQU:
	     g_value_set_boolean(result,pointer_a == pointer_b);
	     break;
	   case GOLEM_OPERATOR_DIF:
	     g_value_set_boolean(result,pointer_a != pointer_b);
	     break;
	   default:
	     break;
	 }
       }
       break;
     default:
       break;
  }
  g_value_unset(&optimal_a);
  g_value_unset(&optimal_b);
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
	      if(phase->operator >= GOLEM_OPERATOR_DIV && phase->operator <= GOLEM_OPERATOR_DIF){
		  _golem_expression_complex_operator_aritmetical(&a,&b,result,phase->operator);
	      }
	    }
	}
    }
  g_value_unset(&a);
  g_value_unset(&b);
  return done;
}

gboolean
golem_expression_complex_check_continue(GolemParser * parser)
{
  if(golem_parser_is_end(parser))
    return FALSE;
  const gchar * wd = golem_parser_next_word(parser,NULL,FALSE);
  if((*wd != ';') && (*wd != ',') && (*wd != ')') && (*wd != ']') && (*wd != '}'))
    return TRUE;
  else
    return FALSE;
}

gboolean
golem_expression_complex_valid_end(GolemParser * parser,GolemExpressionLimit limit)
{
  if(golem_parser_is_end(parser))
    return FALSE;
  const gchar * wd = golem_parser_next_word(parser,NULL,FALSE);
  switch(limit)
  {
    case GOLEM_EXPRESSION_LIMIT_PARENTHESIS_COMA:
      if((*wd == ',') || (*wd == ')'))
    	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_PARENTHESIS:
      if(*wd == ')')
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET_COMA:
      if((*wd == ',') || (*wd == ']'))
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET:
      if(*wd == ']')
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_BRACKET_COMA:
      if((*wd == ',') || (*wd == '}'))
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_BRACKET:
      if(*wd == '}')
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_SEMICOLON:
      if(*wd == ';')
	return TRUE;
      break;
    case GOLEM_EXPRESSION_LIMIT_SEMICOLON_COMA:
      if((*wd == ',')||(*wd == ';'))
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
  return phase;
}

GolemExpression *
golem_expression_complex_parse_subexpression(GolemParser * parser,GolemExpression * parent,GolemExpressionLimit limit,GError ** error)
{
  GolemExpression * result = parent;
  if(golem_invoke_check(parser))
    {
      result = golem_invoke_parse(parser,parent,error);
      if(golem_expression_complex_check_continue(parser))
	{
	  result = golem_expression_complex_parse_subexpression(parser,result,limit,error);
	}
    }
  else if(golem_member_check(parser))
    {
      result = golem_member_parse(parser,parent,limit,error);
      if(golem_expression_complex_check_continue(parser))
    	{
    	  result = golem_expression_complex_parse_subexpression(parser,result,limit,error);
    	}
    }
  return result;
}

GolemExpression *
golem_expression_complex_parse(GolemParser * parser,GolemExpressionLimit limit, GError ** error)
{
  GolemExpressionComplex * expression = NULL;
  GolemOperator op = GOLEM_OPERATOR_NONE;
  gboolean have_predecessor = FALSE;
  gboolean negative = FALSE;
  GList * expression_parts = NULL;

  while(golem_expression_complex_check_continue(parser))
    {
      if(golem_parser_next_word_check(parser,"!="))
	{
	  op = GOLEM_OPERATOR_DIF;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"**"))
	{
	  op = GOLEM_OPERATOR_POW;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"*"))
	{
	  op = GOLEM_OPERATOR_MUL;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,">="))
	{
	  op = GOLEM_OPERATOR_GRE_EQU;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,">"))
	{
	  op = GOLEM_OPERATOR_GRE;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"<="))
	{
	  op = GOLEM_OPERATOR_LES_EQU;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"<"))
	{
	  op = GOLEM_OPERATOR_LES;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"=="))
	{
	  op = GOLEM_OPERATOR_EQU;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"!"))
	{
	  op = GOLEM_OPERATOR_NOT;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"/"))
	{
	  op = GOLEM_OPERATOR_DIV;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"+"))
	{
	  op = GOLEM_OPERATOR_ADD;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"-"))
	{
	  if(!have_predecessor)
	    {
	      negative = TRUE;
	    }
	  else
	    {
	      have_predecessor = FALSE;
	      op = GOLEM_OPERATOR_SUB;
	    }
	}
      else if(golem_parser_next_word_check(parser,"in"))
	{
	  op = GOLEM_OPERATOR_IN;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"is"))
	{
	  op = GOLEM_OPERATOR_IS;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"&"))
	{
	  op = GOLEM_OPERATOR_AND_BIT;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"&&"))
	{
	  op = GOLEM_OPERATOR_AND;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"||"))
	{
	  op = GOLEM_OPERATOR_OR;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"|"))
	{
	  op = GOLEM_OPERATOR_OR_BIT;
	  have_predecessor = FALSE;
	}
      else if(golem_parser_next_word_check(parser,"("))
	{
	  GolemExpression * subexp = golem_expression_complex_parse(parser,GOLEM_EXPRESSION_LIMIT_PARENTHESIS,error);
	  if(subexp)
	    {
	      GolemExpressionComplexPart * part = g_new0(GolemExpressionComplexPart,1);
	      part->expression = golem_expression_complex_parse_subexpression(parser,subexp,limit,error);
	      part->operator = op;
	      expression_parts = g_list_append(expression_parts,part);
	    }
	  golem_parser_next_word_check(parser,")");
	  have_predecessor = TRUE;
	}
      else if(golem_new_check(parser))
  	{
  	  GolemExpressionComplexPart * part = g_new0(GolemExpressionComplexPart,1);
  	  part->expression = golem_expression_complex_parse_subexpression(parser, golem_new_parse(parser,error),limit,error);
  	  part->operator = op;
  	  expression_parts = g_list_append(expression_parts,part);
  	  have_predecessor = TRUE;
  	}
      else if(golem_builder_closure_check(parser))
	{
	  GolemExpressionComplexPart * part = g_new0(GolemExpressionComplexPart,1);
	  part->expression = golem_expression_complex_parse_subexpression(parser, golem_builder_closure_parse(parser,error),limit,error);
	  part->operator = op;
	  expression_parts = g_list_append(expression_parts,part);
	  have_predecessor = TRUE;
	}
      else if(golem_constant_check(parser))
	{
	  GolemExpressionComplexPart * part = g_new0(GolemExpressionComplexPart,1);
	  part->expression = golem_expression_complex_parse_subexpression(parser, golem_constant_parse(parser,negative,error),limit,error);
	  part->operator = op;
	  negative = FALSE;
	  have_predecessor = TRUE;
	  expression_parts = g_list_append(expression_parts,part);
	}
      else if(golem_pointer_of_check(parser))
	{
	  GolemExpressionComplexPart * part = g_new0(GolemExpressionComplexPart,1);
	  part->expression = golem_expression_complex_parse_subexpression(parser, golem_pointer_of_parse(parser,error),limit,error);
	  part->operator = op;
	  expression_parts = g_list_append(expression_parts,part);
	  have_predecessor = TRUE;
	}
      else if(golem_identificator_check(parser))
	{
	  GolemExpressionComplexPart * part = g_new0(GolemExpressionComplexPart,1);
	  part->expression = golem_expression_complex_parse_subexpression(parser,golem_identificator_parse(parser,limit,error),limit,error);
	  part->operator = op;
	  expression_parts = g_list_append(expression_parts,part);
	  have_predecessor = TRUE;
	}
      else
	{
	  have_predecessor = FALSE;
	  g_print("bad %s",golem_parser_next_word(parser,NULL,FALSE));
	  abort();
	  //TODO: throw exception expected operator, constant or identificator
	}
    }

  if(golem_expression_complex_valid_end(parser,limit))
    {
      if(g_list_length(g_list_first(expression_parts)) == 1)
	{
	  expression = (GolemExpressionComplex*)((GolemExpressionComplexPart *)expression_parts->data)->expression;
	}
      else
	{
	  expression = GOLEM_EXPRESSION_COMPLEX(g_object_new(GOLEM_TYPE_EXPRESSION_COMPLEX,NULL));
	  expression->priv->phase = golem_expression_complex_phase_build(g_list_first(expression_parts),GOLEM_OPERATOR_NONE);
	}
      g_list_free(expression_parts);
    }
  else
    {
      g_print("not expected %s at %d was expected %d",golem_parser_next_word(parser,NULL,FALSE),golem_parser_get_line(parser),limit);
      abort();
    }
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
