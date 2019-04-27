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

#include "golem.h"

GType
golem_primitive_type_get_type(void)
{
  static GType primitive_type_gtype = G_TYPE_NONE;
  if (primitive_type_gtype == G_TYPE_NONE)
    {
      static GEnumValue values[] = {
	  { GOLEM_PRIMITIVE_TYPE_BOOL,"bool","bool" },
	  { GOLEM_PRIMITIVE_TYPE_CHAR,"char","uchar" },
	  { GOLEM_PRIMITIVE_TYPE_UCHAR,"uchar","uchar" },
	  { GOLEM_PRIMITIVE_TYPE_INT8,"int8","int8" },
	  { GOLEM_PRIMITIVE_TYPE_UINT8,"uint8","uint8" },
	  { GOLEM_PRIMITIVE_TYPE_INT16,"int16","int16" },
	  { GOLEM_PRIMITIVE_TYPE_UINT16,"uint16","uint16" },
	  { GOLEM_PRIMITIVE_TYPE_INT32,"int32","int32" },
	  { GOLEM_PRIMITIVE_TYPE_UINT32,"uint32","uint32" },
	  { GOLEM_PRIMITIVE_TYPE_INT64,"int64","int64" },
	  { GOLEM_PRIMITIVE_TYPE_UINT64,"uint64","uint64" },
	  { GOLEM_PRIMITIVE_TYPE_INT128,"int128","int128" },
	  { GOLEM_PRIMITIVE_TYPE_UINT128,"uint128","uint128" },
	  { GOLEM_PRIMITIVE_TYPE_FLOAT32,"float32","float32" },
	  { GOLEM_PRIMITIVE_TYPE_FLOAT64,"float64","float64" },
	  { GOLEM_PRIMITIVE_TYPE_FLOAT128,"float128","float128" },
	  { GOLEM_PRIMITIVE_TYPE_STRING,"string","string" },
	  { GOLEM_PRIMITIVE_TYPE_POINTER,"pointer","pointer" },
	  { 0 ,NULL,NULL }
      };
      primitive_type_gtype = g_enum_register_static("GolemPrimitiveType",
						    values);
    }
  return primitive_type_gtype;
}
