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

#ifndef GOLEMBUILDERCLOSURE_H_
#define GOLEMBUILDERCLOSURE_H_

typedef struct _GolemBuilderClosurePrivate GolemBuilderClosurePrivate;

#define GOLEM_TYPE_BUILDER_CLOSURE (golem_builder_closure_get_type())
G_DECLARE_FINAL_TYPE(GolemBuilderClosure,golem_builder_closure,GOLEM,BUILDER_CLOSURE,GolemExpression)

struct _GolemBuilderClosureClass
{
  GolemExpressionClass parent_class;
};


struct _GolemBuilderClosure
{
  GolemExpression parent_instance;
  GolemBuilderClosurePrivate * priv;
};

GType 			golem_builder_closure_get_type(void);

gboolean 		golem_builder_closure_check(GolemParser * parser);

GolemExpression * 	golem_builder_closure_parse(GolemParser * parser,GError ** error);

#endif /* GOLEMBUILDERCLOSURE_H_ */
