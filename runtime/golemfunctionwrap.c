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

#include "../golem.h"

struct _GolemFunctionWrapPrivate
{
  gpointer padding[5];
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemFunctionWrap,golem_function_wrap,GOLEM_TYPE_FUNCTION)

static void
golem_function_wrap_init(GolemFunctionWrap * self)
{

}

static gboolean
golem_function_wrap_invoke_real(GolemFunction * func,
				guint16 argc,
				GolemVMData * argv,
				GolemVMData * ret,
				GError ** error)
{

  return TRUE;
}

static void
golem_function_wrap_class_init(GolemFunctionWrapClass * klass)
{
  GOLEM_FUNCTION_CLASS(klass)->invoke = golem_function_wrap_invoke_real;
}


GolemFunction *
golem_function_wrap_new(GolemFunctionInfo * info,
			gpointer instance,
			gpointer native)
{
  return GOLEM_FUNCTION(
      g_object_new(GOLEM_TYPE_FUNCTION_WRAP,
		   "function-info",info,
		   "instance",info,
		   "native",native));
}
