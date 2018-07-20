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


#include "../golem.h"

G_DEFINE_INTERFACE(GolemModuleManager,golem_module_manager,G_TYPE_OBJECT)

static void
golem_module_manager_default_init(GolemModuleManagerInterface * mm)
{
  mm->lookup = NULL;
}

gpointer
golem_module_manager_lookup(GolemModuleManager * mm,
			    const gchar * name,
			    GError ** error)
{
  GolemModuleManagerInterface *iface;

  g_return_val_if_fail (GOLEM_IS_MODULE_MANAGER(mm),NULL);
  g_return_val_if_fail (error == NULL || *error == NULL,NULL);

  iface = GOLEM_MODULE_MANAGER_GET_IFACE (mm);
  g_return_val_if_fail (iface->lookup != NULL,NULL);
  return iface->lookup (mm,name, error);
}
