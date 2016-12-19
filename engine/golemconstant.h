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

#ifndef GOLEMCONSTANT_H_
#define GOLEMCONSTANT_H_

#define GOLEM_TYPE_CONSTANT	(golem_constant_get_type())

typedef struct _GolemConstantPrivate GolemConstantPrivate;

G_DECLARE_FINAL_TYPE(GolemConstant,golem_constant,GOLEM,CONSTANT,GolemExpression)

struct _GolemConstantClass
{
  GolemExpressionClass parent_class;
};

struct _GolemConstant
{
  GolemExpression parent_instance;
  GolemConstantPrivate * priv;
};

GType			golem_constant_get_type(void);

gboolean		golem_constant_check(GolemParser * parser);

GolemExpression * 	golem_constant_parse(GolemParser * parser,GError ** error);


#endif /* GOLEMCONSTANT_H_ */
