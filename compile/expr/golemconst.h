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

#ifndef GOLEMCONSTANT_H_
#define GOLEMCONSTANT_H_

#define GOLEM_CONST_CLASS (golem_const_get_class())
#define GOLEM_CONST(p)	  ((GolemConst*)p)

typedef struct _GolemConst	GolemConst;

struct _GolemConst {
  GolemStatement parent;
  GolemPrimitive * primitive;
  GolemValue 	 data;
  guint16_t 	 size;
};

GolemStatementClass * golem_const_get_class(void);

#endif /* GOLEMCONSTANT_H_ */
