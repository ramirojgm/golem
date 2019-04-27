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

G_DEFINE_INTERFACE (GolemCallable, golem_callable,G_TYPE_OBJECT)

static void
golem_callable_default_init (GolemCallableInterface *iface)
{
  /* pass */
}


gboolean
golem_callable_call(GolemCallable * callable,
		    GolemValue * result,
		    guint8 argc,
		    GolemValue * argv,
		    GError ** error)
{
   GolemCallableInterface *iface;
   g_return_val_if_fail (GOLEM_IS_CALLABLE(callable),FALSE);
   iface = GOLEM_CALLABLE_GET_IFACE (callable);
   g_return_val_if_fail (iface->call != NULL,FALSE);

   return iface->call(callable,result,argc,argv,error);
}

