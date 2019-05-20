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

#ifndef GOLEMENUMS_H_
#define GOLEMENUMS_H_

#define GOLEM_TYPE_PRIMITIVE_TYPE    (golem_primitive_type_get_type())
#define GOLEM_TYPE_TRANSFER_MODE    (golem_transfer_mode_get_type())

typedef enum _GolemPrimitiveType GolemPrimitiveType;
typedef enum _GolemTransferMode GolemTransferMode;

enum _GolemPrimitiveType
{
  GOLEM_PRIMITIVE_TYPE_BOOL,
  GOLEM_PRIMITIVE_TYPE_CHAR,
  GOLEM_PRIMITIVE_TYPE_UCHAR,
  GOLEM_PRIMITIVE_TYPE_INT8,
  GOLEM_PRIMITIVE_TYPE_UINT8,
  GOLEM_PRIMITIVE_TYPE_INT16,
  GOLEM_PRIMITIVE_TYPE_UINT16,
  GOLEM_PRIMITIVE_TYPE_INT32,
  GOLEM_PRIMITIVE_TYPE_UINT32,
  GOLEM_PRIMITIVE_TYPE_INT64,
  GOLEM_PRIMITIVE_TYPE_UINT64,
  GOLEM_PRIMITIVE_TYPE_INT128,
  GOLEM_PRIMITIVE_TYPE_UINT128,
  GOLEM_PRIMITIVE_TYPE_FLOAT32,
  GOLEM_PRIMITIVE_TYPE_FLOAT64,
  GOLEM_PRIMITIVE_TYPE_FLOAT128,
  GOLEM_PRIMITIVE_TYPE_STRING,
  GOLEM_PRIMITIVE_TYPE_POINTER
};


enum _GolemTransferMode
{
  GOLEM_TRANSFER_NONE,
  GOLEM_TRANSFER_WRAP,
  GOLEM_TRANSFER_FULL
};

GType	golem_primitive_type_get_type(void);

GType	golem_transfer_mode_get_type(void);

#endif /* GOLEMENUMS_H_ */
