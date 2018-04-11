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

#ifndef GOLEMCONDITIONAL_H_
#define GOLEMCONDITIONAL_H_

#define GOLEM_CONDITIONAL_CLASS	(golem_conditional_get_class())
#define GOLEM_CONDITIONAL(p)	((GolemConditional*)p)

typedef struct _GolemConditional	GolemConditional;

struct _GolemConditional {
  GolemStatement parent;
  GolemStatement * true_part;
  GolemStatement * false_part;
};

GolemStatementClass * golem_conditional_get_class(void);


#endif /* GOLEMCONDITIONAL_H_ */
