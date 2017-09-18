/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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

#ifndef GOLEM_REGISTER_H_
#define GOLEM_REGISTER_H_

#define GOLEM_TYPE_REGISTER (golem_register_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemRegister,golem_register,GOLEM,REGISTER,GObject)

struct _GolemRegisterClass
{
  GObjectClass parent_class;
  gboolean (*register_type)(GolemRegister *,GolemModule *,GError ** );
};

GType		golem_register_get_type(void);

gboolean 	golem_register_register_type(GolemRegister * reg,GolemModule * module,GError **  error);

#endif /* GOLEM_REGISTER_H_ */
