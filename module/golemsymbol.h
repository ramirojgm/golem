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

#ifndef GOLEMSYMBOL_H_
#define GOLEMSYMBOL_H_

typedef struct _GolemSymbol GolemSymbol;
typedef struct _GolemSymbolArgument GolemSymbolArgument;

struct _GolemSymbolArgument
{
  GType	 type;
  gchar* name;
  gpointer padding[2];
};

struct _GolemSymbol
{
  GolemTypeInfo parent;
  /* return */
  gboolean return_constant;
  GType	 return_type;

  /* name */
  gchar * name;

  /* arguments */
  guint8 n_arguments;
  GolemSymbolArgument * arguments;

  /* callback */
  gpointer callback;

  /* body */
  GolemVMScope 	* scope_vm;
  GolemVMBody 	* body_vm;
};



#endif /* GOLEMSYMBOL_H_ */