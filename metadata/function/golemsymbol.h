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

#ifndef GOLEM_SYMBOL_H_
#define GOLEM_SYMBOL_H_

#define GOLEM_TYPE_SYMBOL	(golem_symbol_get_type())
G_DECLARE_FINAL_TYPE(GolemSymbol,golem_symbol,GOLEM,SYMBOL,GolemFunction)

typedef struct _GolemSymbolPrivate GolemSymbolPrivate;

struct _GolemSymbol
{
  GolemFunction parent;

  GolemSymbolPrivate * priv;
};

struct _GolemSymbolClass
{
  GolemFunctionClass parent_class;
};

G_BEGIN_DECLS

GType			golem_symbol_get_type(void);

GolemMetadata * 	golem_symbol_new(GolemMetadata * self,
					 const gchar * name,
					 GolemMetadata * return_type,
					 GolemTransferMode transfer_mode,
					 const gchar * symbol_name,
					 const GolemParamSpec ** args);

G_END_DECLS


#endif /* GOLEM_SYMBOL_H_ */
