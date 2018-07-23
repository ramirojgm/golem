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
G_DECLARE_FINAL_TYPE(GolemFunction,golem_function,GOLEM,FUNCTION,GolemMember)

typedef struct _GolemFunctionPrivate GolemFunctionPrivate;

struct _GolemFunctionClass
{
  GolemMemberClass parent_class;
};

struct _GolemFunction
{
  GolemMember parent_instance;

  GolemFunctionPrivate * priv;
};

GType			golem_function_get_type(void);

gpointer		golem_function_get_symbol(GolemFunction * function);

GolemTypeReference	golem_function_get_marshal(GolemFunction * function);

gboolean		golem_function_call(GolemFunction * function,
					    gpointer instance,
					    guint8 argc,
					    GValue * argv,
					    GError ** error);

#endif /* GOLEMFUNCTION_H_ */
