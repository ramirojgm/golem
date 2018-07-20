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

typedef struct
{
  gchar * name;
  GolemTypeName type_name;
  GType	gtype;

} GolemTypePrivate;

G_DEFINE_ABSTRACT_TYPE(GolemType,golem_type,G_TYPE_OBJECT)

enum _GolemTypeProperties
{
  GOLEM_TYPE_PROP_0 = 0,
  GOLEM_TYPE_PROP_NAME,
  GOLEM_TYPE_PROP_TYPE_NAME,
  GOLEM_TYPE_PROP_GTYPE,
  GOLEM_TYPE_PROP_N
};

static GParamSpec * _golem_type_properties[GOLEM_TYPE_PROP_N] = {0,};

static void
golem_type_init(GolemType * self)
{
  GolemTypePrivate * priv = golem_type_get_instance_private(self);
  priv->gtype = G_TYPE_NONE;
  priv->name = NULL;
  priv->type_name = GOLEM_TYPE_NONE;
}

static void
_golem_type_set_property(GObject * object,
			 guint property_id,
			 const GValue * value,
			 GParamSpec * pspec)
{

}

static void
_golem_type_get_property(GObject * object,
			 guint property_id,
			 GValue * value,
			 GParamSpec * pspec)
{

}


static void
golem_type_class_init(GolemTypeClass * klass)
{
  G_OBJECT_CLASS(klass)->get_property = _golem_type_get_property;
  G_OBJECT_CLASS(klass)->set_property = _golem_type_set_property;

  _golem_type_properties[GOLEM_TYPE_PROP_NAME] =
      g_param_spec_string("name",
			  "Name",
			  "Descriptive name of type",
			  "",
			  G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  _golem_type_properties[GOLEM_TYPE_PROP_TYPE_NAME] =
        g_param_spec_int("type-name",
  			 "Type name",
  			 "Numeric name of type",
			  G_MININT16,
			  G_MAXUINT16,
  			  0,
  			  G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  _golem_type_properties[GOLEM_TYPE_PROP_GTYPE] =
        g_param_spec_gtype("gtype",
			   "GType",
			   "GType",
			   G_TYPE_NONE,
			   G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  g_object_class_install_properties(
      G_OBJECT_CLASS(klass),
      GOLEM_TYPE_PROP_N,
      _golem_type_properties);
}
