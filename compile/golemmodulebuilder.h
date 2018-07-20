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

#ifndef GOLEMMODULEBUILDER_H_
#define GOLEMMODULEBUILDER_H_

#define GOLEM_TYPE_MODULE_BUILDER	(golem_module_builder_get_type())
G_DECLARE_FINAL_TYPE(GolemModuleBuilder,golem_module_builder,GOLEM,MODULE_BUILDER,GObject)

typedef struct _GolemModuleBuilderPrivate GolemModuleBuilderPrivate;

struct _GolemModuleBuilderClass
{
  GObjectClass parent_class;
};

struct _GolemModuleBuilder
{
  GObject parent_instance;

};

GType		golem_module_builder_get_type(void);

void		golem_module_builder_new(void);

gboolean	golem_module_builder_parse(GolemModuleBuilder * builder,
					   const gchar * code,
					   gssize length,
					   GError ** error);


GolemModule*	golem_module_builder_compile(GolemModuleBuilder * builder,
					     GolemModuleManager * module_manager,
					     GError ** error);

#endif /* GOLEMMODULEBUILDER_H_ */
