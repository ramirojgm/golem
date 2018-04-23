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

#ifndef GOLEMCALL_H_
#define GOLEMCALL_H_

#define GOLEM_CALL_CLASS	(golem_call_get_class())
#define GOLEM_CALL(p)		((GolemCall*)p)

typedef struct _GolemCall	GolemCall;

struct _GolemCall {
  GolemStatementExt parent;
  GList * arguments;
};

GolemStatementClass * golem_call_get_class(void);

#endif /* GOLEMCALL_H_ */
