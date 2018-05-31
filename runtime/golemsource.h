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

#ifndef GOLEMAPPLICATIONCONTEXT_H_
#define GOLEMAPPLICATIONCONTEXT_H_

#define GOLEM_TYPE_APPLICATION_CONTEXT (golem_application_context_get_type())
G_DECLARE_INTERFACE (GolemApplicationContext, golem_application_context, GOLEM, APPLICATION_CONTEXT, GObject)

struct _GolemApplicationContextInterface
{
  GTypeInterface parent_iface;

  gboolean (*register_object)(const gchar * type_name);

  gboolean (*register_struct)(const gchar * type_name);

  gboolean (*register_marshal)(const gchar * type_name);


};


#endif /* GOLEMAPPLICATIONCONTEXT_H_ */
