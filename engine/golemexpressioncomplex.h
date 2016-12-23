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

typedef enum _GolemExpressionLimit GolemExpressionLimit;
typedef struct _GolemExpressionComplexPrivate GolemExpressionComplexPrivate;

#define GOLEM_TYPE_EXPRESSION_COMPLEX	(golem_expression_complex_get_type())
G_DECLARE_FINAL_TYPE(GolemExpressionComplex,golem_expression_complex,GOLEM,EXPRESSION_COMPLEX,GolemExpression)

struct _GolemExpressionComplexClass
{
  GolemExpressionClass parent_class;

};


struct _GolemExpressionComplex
{
  GolemExpressionComplex parent_instance;
  GolemExpressionComplexPrivate * priv;
};


GType			golem_expression_complex_get_type(void);

GolemExpression * 	golem_expression_complex_parse(GolemParser * parser,GolemExpressionLimit limit,GError ** error);


#endif /* GOLEMEXPRESSIONCOMPLEX_H_ */
