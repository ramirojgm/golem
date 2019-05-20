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

#include "../golem.h"

struct _GolemPrimitivePrivate
{
  GType              gtype;
  GolemPrimitiveType primitive_type;
};

enum GolemPrimitiveProperties
{
  GOLEM_PRIMITIVE_PROP_GTYPE = 1,
  GOLEM_PRIMITIVE_PROP_PRIMITIVE_TYPE,
  GOLEM_PRIMITIVE_N_PROP
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemPrimitive,golem_primitive,GOLEM_TYPE_METADATA)


GolemPrimitiveType
golem_primitive_get_primitive_type(GolemPrimitive * primitive)
{
  g_assert(GOLEM_IS_PRIMITIVE(primitive));
  return primitive->priv->primitive_type;
}

glength8_t
golem_primitive_get_sizeof(GolemMetadata * metadata)
{
  GolemPrimitivePrivate *
  priv = GOLEM_PRIMITIVE(metadata)->priv;
  const glength8_t glength_ptr = {4,8};

  glength8_t size = {0,0};
  switch(priv->primitive_type)
  {
    case GOLEM_PRIMITIVE_TYPE_BOOL:
      glength_set(size,sizeof(gbool_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_CHAR:
    case GOLEM_PRIMITIVE_TYPE_UCHAR:
      glength_set(size,sizeof(gchar_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_INT8:
    case GOLEM_PRIMITIVE_TYPE_UINT8:
      glength_set(size,sizeof(gint8_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_INT16:
    case GOLEM_PRIMITIVE_TYPE_UINT16:
      glength_set(size,sizeof(gint16_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_INT32:
    case GOLEM_PRIMITIVE_TYPE_UINT32:
      glength_set(size,sizeof(gint32_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_INT64:
    case GOLEM_PRIMITIVE_TYPE_UINT64:
      glength_set(size,sizeof(gint64_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_INT128:
    case GOLEM_PRIMITIVE_TYPE_UINT128:
      glength_set(size,sizeof(gint128_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_FLOAT32:
      glength_set(size,sizeof(gfloat32_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_FLOAT64:
      glength_set(size,sizeof(gfloat64_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_FLOAT128:
      glength_set(size,sizeof(gfloat128_t));
      break;
    case GOLEM_PRIMITIVE_TYPE_STRING:
    case GOLEM_PRIMITIVE_TYPE_POINTER:
      glength_add(size,glength_ptr);
      break;
  }
  return size;
}

static void
golem_primitive_init(GolemPrimitive * self)
{
  self->priv = golem_primitive_get_instance_private(self);
}

static void
golem_primitive_set_property(GObject * obj,
			     guint property_id,
			     const GValue * src,
			     GParamSpec * pspec)
{
  GolemPrimitivePrivate *
  priv = GOLEM_PRIMITIVE(obj)->priv;

  switch(property_id)
  {
    case GOLEM_PRIMITIVE_PROP_GTYPE:
      priv->gtype = g_value_get_gtype(src);
      break;
    case GOLEM_PRIMITIVE_PROP_PRIMITIVE_TYPE:
      priv->primitive_type = g_value_get_enum(src);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,pspec);
  }
}

static void
golem_primitive_get_property(GObject * obj,
			     guint property_id,
			     GValue * dest,
			     GParamSpec * pspec)
{
  GolemPrimitivePrivate *
  priv = GOLEM_PRIMITIVE(obj)->priv;

  switch(property_id)
    {
      case GOLEM_PRIMITIVE_PROP_GTYPE:
	g_value_set_gtype(dest,priv->gtype);
	break;
      case GOLEM_PRIMITIVE_PROP_PRIMITIVE_TYPE:
	g_value_set_enum(dest,priv->primitive_type);
	break;
      default:
	G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,pspec);
    }
}

static GolemMetadata *
golem_primitive_get_attribute(GolemMetadata * metadata,
			      const gchar * attr_name)
{
  g_print("Attribute:%s\n",attr_name);
  return NULL;
}

static void
golem_primitive_class_init(GolemPrimitiveClass * klass)
{
  static GParamSpec * properties[GOLEM_PRIMITIVE_N_PROP] = {0,};

  properties [GOLEM_PRIMITIVE_PROP_GTYPE] =
      g_param_spec_gtype("gtype",
			 "GType",
			 "Equivalent GType",
			 G_TYPE_NONE,
			 G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  properties [GOLEM_PRIMITIVE_PROP_PRIMITIVE_TYPE] =
        g_param_spec_enum("primitive-type",
  			 "Primitive Type",
  			 "Unique code for primitive",
  			 GOLEM_TYPE_PRIMITIVE_TYPE,
			 GOLEM_PRIMITIVE_TYPE_INT32,
  			 G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  G_OBJECT_CLASS(klass)->set_property = golem_primitive_set_property;
  G_OBJECT_CLASS(klass)->get_property = golem_primitive_get_property;

  GOLEM_METADATA_CLASS(klass)->get_sizeof = golem_primitive_get_sizeof;
  GOLEM_METADATA_CLASS(klass)->get_attribute = golem_primitive_get_attribute;

  g_object_class_install_properties(G_OBJECT_CLASS(klass),
				    GOLEM_PRIMITIVE_N_PROP,
				    properties);
}

GolemMetadata *
golem_primitive_type_bool(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","bool",
		   "gtype",G_TYPE_BOOLEAN,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_BOOL,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_char(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","char",
		   "gtype",G_TYPE_CHAR,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_CHAR,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_uchar(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","uchar",
		   "gtype",G_TYPE_UCHAR,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_UCHAR,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_int8(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","sbyte",
		   "gtype",G_TYPE_INT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_INT8,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_uint8(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","byte",
		   "gtype",G_TYPE_UINT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_UINT8,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_int16(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","short",
		   "gtype",G_TYPE_INT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_INT16,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_uint16(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","ushort",
		   "gtype",G_TYPE_UINT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_UINT16,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_int32(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","int",
		   "gtype",G_TYPE_INT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_INT32,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_uint32(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","uint",
		   "gtype",G_TYPE_UINT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_UINT32,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_int64(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","long",
		   "gtype",G_TYPE_INT64,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_INT64,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_uint64(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","ulong",
		   "gtype",G_TYPE_UINT64,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_UINT64,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_int128(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","int128",
		   "gtype",G_TYPE_INT64,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_INT128,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_uint128(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","uint128",
		   "gtype",G_TYPE_UINT64,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_UINT128,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_float32(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","float",
		   "gtype",G_TYPE_FLOAT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_FLOAT32,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_float64(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","double",
		   "gtype",G_TYPE_DOUBLE,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_FLOAT64,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_float128(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","quad",
		   "gtype",G_TYPE_FLOAT,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_FLOAT128,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_string(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","string",
		   "gtype",G_TYPE_STRING,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_STRING,
		   NULL));
    }
  return prim;
}

GolemMetadata *
golem_primitive_type_pointer(void)
{
  static
  GolemMetadata * prim = NULL;
  if (!prim)
    {
      prim = GOLEM_METADATA(
	  g_object_new(GOLEM_TYPE_PRIMITIVE,
		   "name","pointer",
		   "gtype",G_TYPE_POINTER,
		   "primitive-type",GOLEM_PRIMITIVE_TYPE_POINTER,
		   NULL));
    }
  return prim;
}

