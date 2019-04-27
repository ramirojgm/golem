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

#ifndef GOLEMVAR_H_
#define GOLEMVAR_H_

#define GOLEM_VAR_CLASS	(golem_var_get_class())
#define GOLEM_VAR(p)	((GolemVar*)p)

typedef struct _GolemVar	GolemVar;
typedef struct _GolemVarInfo	GolemVarInfo;

struct _GolemVarInfo
{
  gchar * name;
  GolemStatement * value;
};

struct _GolemVar {
  GolemStatement parent;
  gchar * type_name;
  GList * vars;
};

GolemStatementClass * golem_var_get_class(void);

#endif /* GOLEMVAR_H_ */
