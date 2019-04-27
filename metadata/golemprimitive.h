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

#define GOLEM_TYPE_PRIMITIVE    (golem_primitive_get_type())

G_DECLARE_FINAL_TYPE(GolemPrimitive,golem_primitive,GOLEM,PRIMITIVE,GolemMetadata)

#define GOLEM_TYPE_BOOL		(golem_primitive_type_bool())
#define GOLEM_TYPE_CHAR  	(golem_primitive_type_char())
#define GOLEM_TYPE_UCHAR  	(golem_primitive_type_uchar())
#define GOLEM_TYPE_SBYTE   	(golem_primitive_type_int8())
#define GOLEM_TYPE_BYTE  	(golem_primitive_type_uint8())
#define GOLEM_TYPE_SHORT   	(golem_primitive_type_int16())
#define GOLEM_TYPE_USHORT  	(golem_primitive_type_uint16())
#define GOLEM_TYPE_INT   	(golem_primitive_type_int32())
#define GOLEM_TYPE_UINT  	(golem_primitive_type_uint32())
#define GOLEM_TYPE_LONG   	(golem_primitive_type_int64())
#define GOLEM_TYPE_ULONG  	(golem_primitive_type_uint64())
#define GOLEM_TYPE_INT128   	(golem_primitive_type_int128())
#define GOLEM_TYPE_UINT128  	(golem_primitive_type_uint128())
#define GOLEM_TYPE_FLOAT   	(golem_primitive_type_float32())
#define GOLEM_TYPE_DOUBLE  	(golem_primitive_type_float64())
#define GOLEM_TYPE_QUAD  	(golem_primitive_type_float128())
#define GOLEM_TYPE_STRING  	(golem_primitive_type_string())
#define GOLEM_TYPE_POINTER  	(golem_primitive_type_pointer())


typedef struct _GolemPrimitivePrivate GolemPrimitivePrivate;

struct _GolemPrimitive
{
  GolemMetadata parent;
  GolemPrimitivePrivate * priv;
};

struct _GolemPrimitiveClass
{
  GolemMetadataClass parent_class;
};

GType              golem_primitive_get_type(void);

GType              golem_primitive_get_gtype(GolemPrimitive * primitive);

GolemPrimitiveType golem_primitive_get_primitive_type(GolemPrimitive * primitive);

GolemMetadata *    golem_primitive_type_bool(void);
GolemMetadata *    golem_primitive_type_char(void);
GolemMetadata *    golem_primitive_type_uchar(void);
GolemMetadata *    golem_primitive_type_int8(void);
GolemMetadata *    golem_primitive_type_uint8(void);
GolemMetadata *    golem_primitive_type_int16(void);
GolemMetadata *    golem_primitive_type_uint16(void);
GolemMetadata *    golem_primitive_type_int32(void);
GolemMetadata *    golem_primitive_type_uint32(void);
GolemMetadata *    golem_primitive_type_int64(void);
GolemMetadata *    golem_primitive_type_uint64(void);
GolemMetadata *    golem_primitive_type_int128(void);
GolemMetadata *    golem_primitive_type_uint128(void);
GolemMetadata *    golem_primitive_type_float32(void);
GolemMetadata *    golem_primitive_type_float64(void);
GolemMetadata *    golem_primitive_type_float128(void);
GolemMetadata *    golem_primitive_type_string(void);
GolemMetadata *    golem_primitive_type_pointer(void);

  
