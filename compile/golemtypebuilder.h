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

#ifndef GOLEMTYPEBUILDER_H_
#define GOLEMTYPEBUILDER_H_

#define GOLEM_TYPE_TYPE_BUILDER	(golem_type_builder_get_type())
G_DECLARE_FINAL_TYPE(GolemTypeBuilder,golem_type_builder,GOLEM,TYPE_BUILDER,GObject)

typedef struct _GolemTypeBuilderPrivate GolemTypeBuilderPrivate;

struct _GolemTypeBuilderClass
{
  GObjectClass parent_class;
};


GolemTypeBuilder*	golem_type_builder_new(void);

GolemType *		golem_type_builder_compile(GolemTypeBuilder * builder,
						   GolemModuleBuilder * module);

void			golem_type_builder_add_base(GolemTypeBuilder * builder,
						    const gchar * type_name);


#endif /* GOLEMTYPEBUILDER_H_ */
