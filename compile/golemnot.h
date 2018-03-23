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

#ifndef GOLEMNOT_H_
#define GOLEMNOT_H_

#define GOLEM_NOT_CLASS	(golem_not_get_class())
#define GOLEM_NOT(p)	((GolemNot*)p)

typedef struct _GolemNot	GolemNot;

struct _GolemNot {
  GolemStatement parent;
  GolemStatement * value;
};

GolemStatementClass * golem_not_get_class(void);

#endif /* GOLEMNOT_H_ */
