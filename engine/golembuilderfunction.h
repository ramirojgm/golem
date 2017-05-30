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

#ifndef GOLEMBUILDERFUNC_H_
#define GOLEMBUILDERFUNC_H_

#define GOLEM_TYPE_BUILDER_FUNCTION	(golem_builder_function_get_type())
G_DECLARE_FINAL_TYPE(GolemBuilderFunction,golem_builder_function,GOLEM,BUILDER_FUNCTION,GolemStatement)

typedef struct _GolemBuilderFunctionPrivate GolemBuilderFunctionPrivate;

struct _GolemBuilderFunctionClass
{
  GolemStatementClass parent_class;

};

struct _GolemBuilderFunction
{
  GolemStatement parent_instance;
  GolemBuilderFunctionPrivate * priv;
};

GType			golem_builder_function_get_type(void);

gboolean		golem_builder_function_check(GolemParser * parser);

GolemBuilderFunction * 	golem_builder_function_parse(GolemParser * parser,GError ** error);

#endif /* GOLEMBUILDERFUNC_H_ */
