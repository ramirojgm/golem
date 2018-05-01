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

#ifndef GOLEMSYMBOLINFO_H_
#define GOLEMSYMBOLINFO_H_

typedef struct _GolemSymbolInfo GolemSymbolInfo;
typedef struct _GolemSymbolArgumentInfo GolemSymbolArgumentInfo;

struct _GolemSymbolArgumentInfo
{
  gchar* name;
  GType	 type;
};

struct _GolemSymbolInfo
{
  GolemTypeInfo parent;
  gboolean return_constant;
  GType	 return_type;
  gchar * name;
  guint8 n_arguments;
  GolemSymbolArgumentInfo * arguments;
  gpointer callback;
};

GLIB_AVAILABLE_IN_ALL
GType		golem_symbol_get_return_type(GolemSymbolInfo * symbol_info);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_symbol_return_constant(GolemSymbolInfo * symbol_info);

GLIB_AVAILABLE_IN_ALL
const gchar *	golem_symbol_get_name(GolemSymbolInfo * symbol_info);

GLIB_AVAILABLE_IN_ALL
const GolemSymbolArgumentInfo *
		golem_symbol_get_arguments(GolemSymbolInfo * symbol_info);

GLIB_AVAILABLE_IN_ALL
guint8		golem_symbol_get_arguments_count(GolemSymbolInfo * symbol_info);

GLIB_AVAILABLE_IN_ALL
gpointer	golem_symbol_get_callback(GolemSymbolInfo * symbol_info);

#endif /* GOLEMSYMBOLINFO_H_ */
