/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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

#ifndef GOLEM_BUILDER_STRUCT_H_
#define GOLEM_BUILDER_STRUCT_H_

#define GOLEM_TYPE_BUILDER_STRUCT	(golem_builder_struct_get_type())
G_DECLARE_FINAL_TYPE(GolemBuilderStruct,golem_builder_struct,GOLEM,BUILDER_STRUCT,GolemRegister)

struct _GolemBuilderStructClass
{
  GolemRegisterClass parent_class;
};

GType			golem_builder_struct_get_type(void);

gboolean 		golem_builder_struct_check(GolemParser * parser);

GolemBuilderStruct * 	golem_builder_struct_parse(GolemParser * parser,GError ** error);

#endif /* GOLEM_BUILDER_STRUCT_H_ */
