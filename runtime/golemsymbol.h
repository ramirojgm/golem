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
typedef struct _GolemFunction GolemFunction;

struct _GolemSymbol
{
  GType marshal_type;
  gchar * name;
  gboolean internal;
  gpointer callback;
};

struct _GolemFunction
{
  GolemSymbol symbol;

  /* arguments */
  gchar ** arguments;

  /* body */
   GolemVMScope * scope_vm;
   GolemVMBody 	* body_vm;
};



#endif /* GOLEMSYMBOL_H_ */
