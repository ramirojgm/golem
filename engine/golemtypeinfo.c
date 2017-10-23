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

G_DEFINE_ABSTRACT_TYPE(GolemTypeInfo,golem_type_info,G_TYPE_OBJECT)

static void
golem_type_info_init(GolemTypeInfo * self)
{
  golem_type_info_get_instance_private(self);
}

static void
golem_type_info_class_init(GolemTypeInfoClass * klass)
{
  klass->get_name = NULL;
  klass->register_type = NULL;
  klass->get_member = NULL;
  klass->set_member = NULL;
}


const gchar *
golem_type_info_get_name(GolemTypeInfo * type_info)
{
  GolemTypeInfoClass * klass = GOLEM_TYPE_INFO_GET_CLASS(type_info);
  g_return_val_if_fail(klass->get_name != NULL,NULL);
  return klass->get_name(type_info);
}

GType
golem_type_info_register_type(GolemTypeInfo * type_info,GolemModule * module,GError ** error)
{
  GolemTypeInfoClass * klass = GOLEM_TYPE_INFO_GET_CLASS(type_info);
  g_return_val_if_fail(klass->register_type != NULL,0);
  return klass->register_type(type_info,module,error);
}

gboolean
golem_type_info_get_static(GolemTypeInfo * type_info,const gchar * name,GValue * dest,GError ** error)
{
  GolemTypeInfoClass * klass = GOLEM_TYPE_INFO_GET_CLASS(type_info);
  g_return_val_if_fail(klass->get_static != NULL,FALSE);
  return klass->get_static(type_info,name,dest,error);
}


gboolean
golem_type_info_get_member(GolemTypeInfo * type_info,GValue * instance,const gchar * name,GValue * dest,GError ** error)
{
  GolemTypeInfoClass * klass = GOLEM_TYPE_INFO_GET_CLASS(type_info);
  g_return_val_if_fail(klass->get_member != NULL,FALSE);
  return klass->get_member(type_info,instance,name,dest,error);
}

gboolean
golem_type_info_set_member(GolemTypeInfo * type_info,GValue * instance,const gchar * name,const GValue * src,GError ** error)
{
  GolemTypeInfoClass * klass = GOLEM_TYPE_INFO_GET_CLASS(type_info);
  g_return_val_if_fail(klass->set_member != NULL,FALSE);
  return klass->set_member(type_info,instance,name,src,error);
}
