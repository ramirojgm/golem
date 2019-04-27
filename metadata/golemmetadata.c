/*
	Copyright (C) 2019 Ramiro Jose Garcia Moraga

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

typedef struct _GolemMetadataPrivate GolemMetadataPrivate;

struct _GolemMetadataPrivate {
  gchar * name;
  gpointer padding[12];
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemMetadata,golem_metadata,G_TYPE_OBJECT)

enum GolemMetadataProperties
{
  GOLEM_METADATA_PROP_NAME = 1,
  GOLEM_METADATA_N_PROP
};

const gchar *
golem_metadata_get_name (GolemMetadata * metadata)
{
  g_assert_nonnull (metadata);
  g_assert (GOLEM_IS_METADATA(metadata));
  GolemMetadataPrivate *
  priv = golem_metadata_get_instance_private(metadata);
  return priv->name;
}

static GolemMetadata *
_golem_metadata_get_attribute_real (GolemMetadata * metadata,
                                    const gchar * attr_name)
{
  return NULL;
}


static void
golem_metadata_init(GolemMetadata * self)
{
  GolemMetadataPrivate *
  priv = golem_metadata_get_instance_private(self);
  priv->name = NULL;
}

static void
golem_metadata_set_property(GObject * obj,
			    guint property_id,
			    const GValue * src,
			    GParamSpec * spec)
{
  GolemMetadataPrivate *
  priv = golem_metadata_get_instance_private(GOLEM_METADATA(obj));

  switch (property_id)
    {
      case GOLEM_METADATA_PROP_NAME:
	g_clear_pointer(&priv->name,g_free);
	priv->name = g_value_dup_string(src);
	break;
      default:
	G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,spec);
	break;
    }
}

static void
golem_metadata_get_property(GObject * obj,
			    guint property_id,
			    GValue * dest,
			    GParamSpec * spec)
{
  GolemMetadataPrivate *
  priv = golem_metadata_get_instance_private(GOLEM_METADATA(obj));

  switch (property_id)
    {
      case GOLEM_METADATA_PROP_NAME:
        g_value_set_string(dest,priv->name);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,spec);
        break;
    }
}

static void
golem_metadata_finalize(GObject * obj)
{
  GolemMetadataPrivate *
  priv = golem_metadata_get_instance_private(GOLEM_METADATA(obj));
  g_free(priv->name);
}

static void
golem_metadata_class_init(GolemMetadataClass * klass)
{
  static GParamSpec * properties[GOLEM_METADATA_N_PROP] = {0,};
  properties [GOLEM_METADATA_PROP_NAME] =
      g_param_spec_string("name",
			  "Name",
			  "Name of the metadata",
			  "",
			  G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  G_OBJECT_CLASS(klass)->set_property = golem_metadata_set_property;
  G_OBJECT_CLASS(klass)->get_property = golem_metadata_get_property;
  G_OBJECT_CLASS(klass)->finalize = golem_metadata_finalize;

  klass->get_attribute = _golem_metadata_get_attribute_real;

  g_object_class_install_properties(
      G_OBJECT_CLASS(klass),
      GOLEM_METADATA_N_PROP,
      properties);
}

GolemMetadata *
golem_metadata_get_attribute (GolemMetadata * metadata,
                              const gchar * attr_name)
{
  g_assert_nonnull (metadata);
  g_assert (GOLEM_IS_METADATA(metadata));
  GolemMetadataClass * klass = GOLEM_METADATA_GET_CLASS(metadata);
  g_assert_nonnull (klass->get_attribute);
  return klass->get_attribute(metadata,attr_name);
}

glength8_t
golem_metadata_get_sizeof (GolemMetadata * metadata)
{
  g_assert_nonnull (metadata);
  g_assert (GOLEM_IS_METADATA(metadata));
  GolemMetadataClass * klass = GOLEM_METADATA_GET_CLASS(metadata);
  g_assert_nonnull (klass->get_sizeof);
  return klass->get_sizeof(metadata);
}
