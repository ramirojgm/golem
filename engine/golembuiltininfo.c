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

struct _GolemBuiltinInfoPrivate
{
  GType   builtin_type;
  GList * func_spec;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuiltinInfo,golem_builtin_info,GOLEM_TYPE_TYPE_INFO)


static void
golem_builtin_info_init(GolemBuiltinInfo * self)
{
  self->priv = golem_builtin_info_get_instance_private(self);
}

static void
golem_builtin_info_class_init(GolemBuiltinInfoClass * klass)
{
  /*GOLEM_TYPE_INFO_CLASS(klass)->get_name = _golem_type_info_get_name;
  GOLEM_TYPE_INFO_CLASS(klass)->register_type = _golem_type_info_register_type;
  GOLEM_TYPE_INFO_CLASS(klass)->get_member = _golem_type_info_get_member;
  GOLEM_TYPE_INFO_CLASS(klass)->set_member = _golem_type_info_set_member;*/
}

