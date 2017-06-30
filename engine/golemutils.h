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

#ifndef GOLEMUTILS_H_
#define GOLEMUTILS_H_

typedef gboolean (*GolemUsingOpenFunc)(const gchar * resource_name,gchar ** buffer,gsize * buffer_length,GError ** error);


GolemUsingOpenFunc	golem_using_get_default_open_function();

void			golem_using_set_default_open_function(GolemUsingOpenFunc func);

GType			golem_resolve_type_name(GolemContext * context,const gchar * name);

const gchar *		golem_type_get_prefix(const gchar * name);

void			g_value_free(GValue * value);

#endif /* GOLEMUTILS_H_ */
