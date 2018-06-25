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

#ifndef GOLEMFUNCTION_H_
#define GOLEMFUNCTION_H_

#define GOLEM_TYPE_FUNCTION	(golem_function_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemFunction,golem_function,GOLEM,FUNCTION,GObject)

struct _GolemFunctionClass
{
  GObjectClass parent_class;

  gboolean (*invoke)(GolemFunction * func,
		     guint16 argc,
		     GolemVMData * argv,
		     GolemVMData * ret,
		     GError ** error);
};

gpointer		golem_function_get_instance(GolemFunction * func);

gpointer		golem_function_get_symbol(GolemFunction * func);

GolemFunctionType* 	golem_function_get_function_type(GolemFunction * func);

gboolean		golem_function_invoke(GolemFunction * func,
				      guint16 argc,
				      GolemVMData * argv,
				      GolemVMData * ret,
				      GError ** error);



#endif /* GOLEMFUNCTION_H_ */
