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

typedef struct _GolemMemberPrivate GolemMemberPrivate;

struct _GolemMemberPrivate
{
  gchar * name;
  GolemModule * module;
  GolemTypeReference value_type;
};

enum _GolemMemberProps
{
  GOLEM_MEMBER_PROP_NAME = 1,
  GOLEM_MEMBER_PROP_MODULE,
  GOLEM_MEMBER_PROP_VALUE_TYPE,
  GOLEM_MEMBER_PROP_N
};

static GParamSpec * golem_member_properties[GOLEM_MEMBER_PROP_N] = {0,};

G_DEFINE_TYPE_WITH_PRIVATE(GolemMember,golem_member,G_TYPE_OBJECT)

static void
golem_member_init(GolemMember * self)
{
  GolemMemberPrivate * priv = golem_member_get_instance_private(self);
  priv->module = NULL;
  priv->name = NULL;
  priv->value_type = GOLEM_TYPE_NONE;
}

static void
golem_member_set_property(GObject * object,
			  guint prop_id,
			  const GValue * src,
			  GParamSpec * spec)
{

}

static void
golem_member_get_property(GObject * object,
			  guint prop_id,
			  GValue * dest,
			  GParamSpec * spec)
{

}

static void
golem_member_dispose(GObject * obj)
{
  GolemMemberPrivate * priv =
      golem_member_get_instance_private(GOLEM_MEMBER(obj));

  g_clear_pointer(&(priv->name),g_free);

  G_OBJECT_CLASS(golem_member_parent_class)->dispose(obj);
}

static void
golem_member_class_init(GolemMemberClass * klass)
{

  G_OBJECT_CLASS(klass)->get_property = golem_member_get_property;
  G_OBJECT_CLASS(klass)->set_property = golem_member_set_property;
  G_OBJECT_CLASS(klass)->dispose = golem_member_dispose;

  golem_member_properties[GOLEM_MEMBER_PROP_NAME] = g_param_spec_string(
      "name",
      "Name",
      "Name",
      "",
      G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  golem_member_properties[GOLEM_MEMBER_PROP_MODULE] = g_param_spec_object(
        "module",
        "Module",
        "Source module",
        G_TYPE_OBJECT, //TODO: change to GOLEM_TYPE_MODULE
        G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  golem_member_properties[GOLEM_MEMBER_PROP_VALUE_TYPE] = g_param_spec_int(
        "value-type",
        "Value type",
        "Value type",
        G_MININT32,
	G_MAXINT32,
	GOLEM_TYPE_NONE,
        G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  g_object_class_install_properties(G_OBJECT_CLASS(klass),
				    GOLEM_MEMBER_PROP_N,
				    golem_member_properties);

}

const gchar *
golem_member_get_name(GolemMember * member)
{
  GolemMemberPrivate * priv = golem_member_get_instance_private(member);
  return priv->name;
}

GolemModule *
golem_member_get_module(GolemMember * member)
{
  GolemMemberPrivate * priv = golem_member_get_instance_private(member);
  return priv->module;
}

GolemTypeReference
golem_member_get_value_type(GolemMember * member)
{
  GolemMemberPrivate * priv = golem_member_get_instance_private(member);
  return priv->value_type;
}

gboolean
golem_member_get_value(GolemMember * member,
		       gpointer instance,
		       gpointer dest,
		       GError ** error)
{
  g_return_val_if_fail(member != NULL,FALSE);
  g_return_val_if_fail(GOLEM_IS_MEMBER(member),FALSE);
  GolemMemberClass * klass = GOLEM_MEMBER_GET_CLASS(member);
  g_return_val_if_fail(klass->get_value!=NULL,FALSE);

  return klass->get_value(member,instance,dest,error);
}

gboolean
golem_member_set_value(GolemMember * member,
		       gpointer instance,
		       gconstpointer src,
		       GError ** error)
{
  g_return_val_if_fail(member != NULL,FALSE);
  g_return_val_if_fail(GOLEM_IS_MEMBER(member),FALSE);
  GolemMemberClass * klass = GOLEM_MEMBER_GET_CLASS(member);
  g_return_val_if_fail(klass->set_value!=NULL,FALSE);
  return klass->set_value(member,instance,src,error);
}

