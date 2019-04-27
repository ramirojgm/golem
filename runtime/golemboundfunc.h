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

#ifndef GOLEMBOUNDFUNC_H_
#define GOLEMBOUNDFUNC_H_

#define GOLEM_TYPE_BOUND_FUNC	(golem_bound_func_get_type())
G_DECLARE_FINAL_TYPE(GolemBoundFunc,golem_bound_func,GOLEM,BOUND_FUNC,GObject)

typedef struct _GolemBoundFuncPrivate	GolemBoundFuncPrivate;

struct _GolemBoundFuncClass
{
  GObjectClass parent_class;
};

struct _GolemBoundFunc
{
  GObject parent_instance;

  GolemBoundFuncPrivate * priv;
};

GType			golem_bound_func_get_type(void);

GolemBoundFunc *	golem_bound_func_new(GolemFunction * func,
					     gpointer inst);

#endif /* GOLEMBOUNDFUNCTION_H_ */
