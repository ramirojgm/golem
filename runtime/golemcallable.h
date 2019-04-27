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

#ifndef GOLEMCALLABLE_H_
#define GOLEMCALLABLE_H_

#define GOLEM_TYPE_CALLABLE (golem_callable_get_type())
G_DECLARE_INTERFACE(GolemCallable,golem_callable,GOLEM,CALLABLE,GObject)

struct _GolemCallableInterface
{
  GTypeInterface parent_iface;

  gboolean (*call)(GolemCallable * callable,
  		             guint8 argc,
  		             GolemValue * argv,
   		   GolemValue * result,
  		   GError ** error);
};


GType		golem_callable_get_type(void) G_GNUC_CONST;

gboolean 	golem_callable_call(GolemCallable * callable,
				    GolemValue * result,
				    guint8 argc,
				    GolemValue * argv,
				    GError ** error);


#endif /* GOLEMCALLABLE_H_ */
