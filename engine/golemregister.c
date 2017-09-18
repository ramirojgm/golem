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

#include "golem.h"

G_DEFINE_ABSTRACT_TYPE(GolemRegister,golem_register,G_TYPE_OBJECT)

static gboolean
_golem_register_register_type_real(GolemRegister * self,GolemModule * module,GError ** error)
{
  golem_runtime_error(error,
      GOLEM_NOT_IMPLEMENTED_ERROR,
      "not implement"
  );
  return FALSE;
}

static void
golem_register_init(GolemRegister * self)
{
  golem_register_get_instance_private(self);
}

static void
golem_register_class_init(GolemRegisterClass * klass)
{
  klass->register_type = _golem_register_register_type_real;
}


gboolean
golem_register_register_type(GolemRegister * self,GolemModule * module,GError ** error)
{
  GolemRegisterClass * klass = GOLEM_REGISTER_GET_CLASS(self);
  return klass->register_type(self,module,error);
}
