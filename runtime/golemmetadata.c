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

typedef struct _GolemMetadataPrivate	GolemMetadataPrivate;

struct _GolemMetadataPrivate
{
  gchar * name;
};

G_DEFINE_ABSTRACT_TYPE(GolemMetadata,golem_metadata,G_TYPE_OBJECT)

enum _GolemMetadataProps
{
  GOLEM_METADATA_PROP_0,
  GOLEM_METADATA_PROP_NAME,
  GOLEM_METADATA_N_PROP
};

static GParamSpec * _golem_metadata_properties[GOLEM_METADATA_N_PROP] = {NULL,};

static void
golem_metadata_set_property(GObject * obj,
			    guint property_id,
			    const GValue * value,
			    GParamSpec * pspec)
{
  GolemMetadataPrivate * priv =
      golem_metadata_get_instance_private(GOLEM_METADATA(obj));

  switch(property_id)
  {
    case GOLEM_METADATA_PROP_NAME:
      g_clear_pointer(&priv->name,g_free);
      priv->name = g_value_dup_string(value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, property_id, pspec);
      break;
  }
}

static void
golem_metadata_get_property(GObject * obj,
			    guint property_id,
			    GValue * value,
			    GParamSpec * pspec)
{
  GolemMetadataPrivate * priv =
      golem_metadata_get_instance_private(GOLEM_METADATA(obj));

  switch(property_id)
  {
    case GOLEM_METADATA_PROP_NAME:
      g_value_set_string(value,priv->name);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, property_id, pspec);
      break;
  }
}

static void
golem_metadata_finalize(GObject * obj)
{
  GolemMetadataPrivate * priv =
          golem_metadata_get_instance_private(GOLEM_METADATA(obj));
  g_clear_pointer(&priv->name,g_free);
}

static void
golem_metadata_init(GolemMetadata * self)
{
  GolemMetadataPrivate * priv = golem_metadata_get_instance_private(self);
  priv->name = NULL;
}

static void
golem_metadata_class_init(GolemMetadataClass * klass)
{
  G_OBJECT_CLASS(klass)->set_property = golem_metadata_set_property;
  G_OBJECT_CLASS(klass)->get_property = golem_metadata_get_property;
  G_OBJECT_CLASS(klass)->finalize = golem_metadata_finalize;

  _golem_metadata_properties[GOLEM_METADATA_PROP_NAME] =
      g_param_spec_string("name",
			  "name",
			  "Name of metadata",
			  "",
			  G_PARAM_CONSTRUCT|G_PARAM_CONSTRUCT_ONLY);

  g_object_class_install_properties(
      G_OBJECT_CLASS(klass),
      GOLEM_METADATA_N_PROP,
      _golem_metadata_properties);
}

const gchar *
golem_metadata_get_name(GolemMetadata * metadata)
{
  GolemMetadataPrivate * priv =
            golem_metadata_get_instance_private(metadata);
  return priv->name;
}
