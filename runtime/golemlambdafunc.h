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

#ifndef GOLEMLAMBDAFUNC_H_
#define GOLEMLAMBDAFUNC_H_

G_DECLARE_FINAL_TYPE(GolemLambdaFunc,golem_lambda_func,GOLEM,LAMBDA_FUNC,GObject)

typedef struct _GolemLambdaFuncPrivate	GolemLambdaFuncPrivate;

struct _GolemLambdaFuncClass
{
  GObjectClass parent_class;
};

struct _GolemLambdaFunc
{
  GObject parent_instance;

  GolemLambdaFuncPrivate * priv;
};

GType			golem_lambda_func_get_type(void) G_GNUC_CONST;

GolemLambdaFunc*	golem_lambda_func_new(GolemVMScope * scope,
					      GolemFunction * func);

#endif /* GOLEMFUNCTIONLAMBDAFUNC_H_ */
