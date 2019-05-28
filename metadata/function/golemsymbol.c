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


#include <golem.h>

struct _GolemSymbolPrivate
{
  gboolean n_static;
  gpointer m_symbol;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemSymbol,golem_symbol,GOLEM_TYPE_FUNCTION)

GolemMetadata *
golem_symbol_new(GolemMetadata * self,
		 const gchar * name,
		 GolemMetadata * return_type,
		 GolemTransferMode transfer_mode,
		 const gchar * symbol_name,
		 const GolemParamSpec ** args)
{


  return GOLEM_METADATA(
      g_object_new(GOLEM_TYPE_SYMBOL,
		   "name",name,
		   "return-type",return_type,
		   "transfer-mode",transfer_mode,
		   "link-name",symbol_name,
		   "args",args,
		   //"static",is_static,
		   NULL));
}


static void
golem_symbol_init(GolemSymbol * self)
{}

static void
golem_symbol_class_init(GolemSymbolClass * klass)
{}

