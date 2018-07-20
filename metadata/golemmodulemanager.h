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

#ifndef GOLEMMODULEMANAGER_H_
#define GOLEMMODULEMANAGER_H_

#define GOLEM_TYPE_MODULE_MANAGER	(golem_module_manager_get_type())
G_DECLARE_INTERFACE(GolemModuleManager,golem_module_manager,GOLEM,MODULE_MANAGER,GObject)

struct _GolemModuleManagerInterface
{
  gpointer (*lookup)(GolemModuleManager * module_manager,
		      const gchar * name,
		      GError ** error);
};

GType		golem_module_manager_get_type(void);

gpointer	golem_module_manager_lookup(GolemModuleManager * mm,
					    const gchar * name,
					    GError ** error);

#endif /* GOLEMMODULEMANAGER_H_ */
