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

#ifndef GOLEMSYMBOLENTRY_H_
#define GOLEMSYMBOLENTRY_H_

typedef struct _GolemSymbolEntryArgument GolemSymbolEntryArgument;

#define GOLEM_SYMBOL_ENTRY_CLASS	(golem_symbol_entry_get_class())
#define GOLEM_SYMBOL_ENTRY(p)		((GolemSymbolEntry*)p)

typedef struct _GolemSymbolEntry	GolemSymbolEntry;

struct _GolemSymbolEntry {
  GolemStatement parent;
  gboolean external;
  gboolean ret_const;
  gchar *  ret_type;
  gchar * name;
  GList * arguments;
  GolemStatement * body;
};

struct _GolemSymbolEntryArgument {
  gchar * type;
  gchar * name;
};

GolemStatementClass * golem_symbol_entry_get_class(void);


#endif /* GOLEMSYMBOLENTRY_H_ */
