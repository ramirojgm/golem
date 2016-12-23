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

#ifndef GOLEMEXPRESSION_H_
#define GOLEMEXPRESSION_H_

typedef enum _GolemExpressionLimit GolemExpressionLimit;

#define GOLEM_TYPE_EXPRESSION	(golem_expression_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemExpression,golem_expression,GOLEM,EXPRESSION,GolemSentence)


enum _GolemExpressionLimit
{
  GOLEM_EXPRESSION_LIMIT_SEMICOLON,
  GOLEM_EXPRESSION_LIMIT_PARENTHESIS,
  GOLEM_EXPRESSION_LIMIT_PARENTHESIS_COMA,
  GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET,
  GOLEM_EXPRESSION_LIMIT_SQUARE_BRACKET_COMA
};


struct _GolemExpressionClass
{
  GolemSentenceClass parent_class;
  gboolean (*evaluate)(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error);

};

GType			golem_expression_get_type(void);

gboolean		golem_expression_check(GolemParser * parser);

GolemExpression * 	golem_expression_parse(GolemParser * parser,GError ** error);

gboolean	 	golem_expression_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error);

#endif /* GOLEMEXPRESSION_H_ */
