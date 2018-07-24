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

#ifndef GOLEMFUNCTIONLAMBDA_H_
#define GOLEMFUNCTIONLAMBDA_H_

typedef struct _GolemFunctionLambdaPrivate	GolemFunctionLambdaPrivate;

struct _GolemFunctionLambdaClass
{
  GObjectClass parent_class;
};

struct _GolemFunctionLambda
{
  GObject parent_instance;

  GolemFunctionLambdaPrivate * priv;
};



#endif /* GOLEMFUNCTIONLAMBDA_H_ */
