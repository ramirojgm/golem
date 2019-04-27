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

#ifndef GOLEMGSVAR_H_
#define GOLEMGSVAR_H_

#define GOLEM_GSVAR_CLASS	(golem_gsvar_get_class())
#define GOLEM_GSVAR(p)		((GolemGSVar*)p)

typedef struct _GolemGSVar	GolemGSVar;

struct _GolemGSVar {
  GolemStatement parent;
  gchar * variable_name;
  GolemStatement * value;
};

GolemStatementClass * golem_gsvar_get_class(void);

#endif /* GOLEMGSVAR_H_ */
