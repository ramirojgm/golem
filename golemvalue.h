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

#ifndef GOLEMVALUE_H_
#define GOLEMVALUE_H_

union _GolemValueCast {
  gboolean bool_v;
  gint8 int8_v;
  gint16 int16_v;
  gint32 int32_v;
  gint64 int64_v;
  guint8 uint8_v;
  guint16 uint16_v;
  guint32 uint32_v;
  guint64 uint64_v;
  gfloat float_v;
  gdouble double_v;
  gpointer pointer_v;
  gchar * string_v;
};

typedef gint64	GolemValue;

#define GOLEM_BOOL(v)	((union _GolemValueCast*)(v))->bool_v
#define GOLEM_INT8(v)	((union _GolemValueCast*)(v))->int8_v
#define GOLEM_UINT8(v)	((union _GolemValueCast*)(v))->uint8_v
#define GOLEM_INT16(v)	((union _GolemValueCast*)(v))->int16_v
#define GOLEM_UINT16(v)	((union _GolemValueCast*)(v))->uint16_v
#define GOLEM_INT32(v)	((union _GolemValueCast*)(v))->int32_v
#define GOLEM_UINT32(v)	((union _GolemValueCast*)(v))->uint32_v
#define GOLEM_INT64(v)	((union _GolemValueCast*)(v))->int64_v
#define GOLEM_UINT64(v)	((union _GolemValueCast*)(v))->uint64_v
#define GOLEM_FLOAT(v)	((union _GolemValueCast*)(v))->float_v
#define GOLEM_DOUBLE(v)	((union _GolemValueCast*)(v))->double_v
#define GOLEM_PTR(v)	((union _GolemValueCast*)(v))->pointer_v
#define GOLEM_STRING(v)	((union _GolemValueCast*)(v))->string_v

#endif /* GOLEMVALUE_H_ */
