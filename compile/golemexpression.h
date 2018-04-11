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

#ifndef GOLEMEXPRESSION_H_
#define GOLEMEXPRESSION_H_

typedef struct 	_GolemExpression GolemExpression;
typedef struct  _GolemExpressionOperation GolemExpressionOperation;
typedef struct 	_GolemExtendExpression GolemExtendExpression;

#define GOLEM_EXPRESSION_CLASS	(golem_expression_get_class())
#define GOLEM_EXPRESSION(p)	((GolemExpression*)p)

enum _GolemExpressionLimit {
  GOLEM_EXPRESSION_LIMIT_SEMICOLON,
  GOLEM_EXPRESSION_LIMIT_SEMICOLON_COMA,
  GOLEM_EXPRESSION_LIMIT_PARENTHESIS,
  GOLEM_EXPRESSION_LIMIT_PARENTHESIS_COMA,
  GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET,
  GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET_COMA,
  GOLEM_EXPRESSION_LIMIT_BRACKET,
  GOLEM_EXPRESSION_LIMIT_BRACKET_COMA
};

typedef enum
{
  GOLEM_OPERATOR_NON,
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
  GOLEM_OPERATOR_LESI,
  GOLEM_OPERATOR_GREI,
  GOLEM_OPERATOR_LAND,
  GOLEM_OPERATOR_LOR,
  GOLEM_OPERATOR_BAND,
  GOLEM_OPERATOR_BOR,
} GolemOperator;

struct _GolemExpressionOperation
{
  GolemOperator operator;
  GolemExpressionOperation * exp1;
  GolemExpressionOperation * exp2;
  GolemStatement * value;
};


struct _GolemExpression
{
  GolemStatement parent;
  GolemExpressionOperation * op;
};

struct _GolemExtendExpression
{
  GolemStatement parent;
  GolemStatement * base;
};

GolemStatementClass * golem_expression_get_class(void);

GolemStatement * golem_expression_parse_new(GolemParser * parser,
					GolemExpressionLimit limit,
					GError ** error);

GolemStatement * golem_simple_expression_parse(GolemParser * parser,
					       GolemExpressionLimit limit,
					       GError ** error);

#endif /* GOLEMEXPRESSION_H_ */
