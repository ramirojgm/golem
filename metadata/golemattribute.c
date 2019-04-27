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

#include <golem.h>

struct _GolemAttributePrivate
{
  GolemMetadata * defined_type;
  glength16_t offset;
  glength8_t length;
};

enum GolemAttributeProperties
{
  GOLEM_ATTRIBUTE_DEFINED_TYPE = 1,
  GOLEM_ATTRIBUTE_OFFSET,
  GOLEM_ATTRIBUTE_LENGTH,
  GOLEM_ATTRIBUTE_N
};

G_DEFINE_TYPE_WITH_PRIVATE (GolemAttribute, golem_attribute, GOLEM_TYPE_METADATA)

static void
golem_attribute_init(GolemAttribute * self)
{
  self->priv = golem_attribute_get_instance_private (self);
  self->priv->defined_type = NULL;
  glength_set(self->priv->offset,0);
  glength_set(self->priv->length,0);
}

static void
golem_attribute_dispose(GObject * obj)
{
  GolemAttributePrivate *
  priv = GOLEM_ATTRIBUTE(obj)->priv;
  g_object_unref (priv->defined_type);
}


static void
golem_attribute_get_property(GObject * obj,
                             guint property_id,
                             GValue * dest,
                             GParamSpec * spec)
{
  GolemAttributePrivate *
  priv = golem_attribute_get_instance_private (GOLEM_ATTRIBUTE(obj));

  switch(property_id)
    {
    case GOLEM_ATTRIBUTE_DEFINED_TYPE:
      g_value_set_object (dest,priv->defined_type);
      break;
    case GOLEM_ATTRIBUTE_OFFSET:
      g_value_set_uint (dest, *((guint*)&(priv->offset)));
      break;
    case GOLEM_ATTRIBUTE_LENGTH:
      g_value_set_uint (dest, *((guint*)&(priv->length)));
      break;
    }

}

static void
golem_attribute_set_property(GObject * obj,
                             guint property_id,
                             const GValue * src,
                             GParamSpec * spec)
{

  GolemAttributePrivate *
  priv = golem_attribute_get_instance_private (GOLEM_ATTRIBUTE(obj));

  guint uint_v;

  switch(property_id)
    {
    case GOLEM_ATTRIBUTE_DEFINED_TYPE:
      g_clear_object (&priv->defined_type);
      priv->defined_type = g_value_get_object (src);
      break;
    case GOLEM_ATTRIBUTE_OFFSET:
      uint_v = g_value_get_uint(src);
      priv->offset = *((glength16_t*)(&uint_v));
      break;
    case GOLEM_ATTRIBUTE_LENGTH:
      uint_v = g_value_get_uint(src);
      priv->length = *((glength8_t*)(&uint_v));
      break;
    }
}


static void
golem_attribute_class_init(GolemAttributeClass * klass)
{
  static GParamSpec * properties[GOLEM_ATTRIBUTE_N] = {0,};

  properties [GOLEM_ATTRIBUTE_DEFINED_TYPE] =
  g_param_spec_object ("defined-type",
                       "Defined type",
                       "Defined type of the attribute",
                       GOLEM_TYPE_METADATA,
                     G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  properties [GOLEM_ATTRIBUTE_OFFSET] =
  g_param_spec_uint ("offset",
                    "Offset",
                    "Offset in bytes",
                    0,
                    G_MAXUINT32,
                    0,
                    G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  properties [GOLEM_ATTRIBUTE_LENGTH] =
  g_param_spec_uint ("length",
                    "Length",
                    "Length in bytes",
                    0,
                    G_MAXUINT32,
                    0,
                    G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  G_OBJECT_CLASS(klass)->get_property = golem_attribute_get_property;
  G_OBJECT_CLASS(klass)->set_property = golem_attribute_set_property;
  G_OBJECT_CLASS(klass)->dispose = golem_attribute_dispose;

  g_object_class_install_properties(G_OBJECT_CLASS(klass),
                                    GOLEM_ATTRIBUTE_N,
                                    properties);
}

glength16_t
golem_attribute_get_offset(GolemAttribute * attr)
{
  return attr->priv->offset;
}

glength8_t
golem_attribute_get_length(GolemAttribute * attr)
{
  return attr->priv->length;
}

void
golem_attribute_get (GolemAttribute * attr,
                     gpointer instance,
                     GolemValue * dest)
{}

void
golem_attribute_set (GolemAttribute * attr,
                     gpointer instance,
                     GolemValue * src)
{


}
