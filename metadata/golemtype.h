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

#ifndef GOLEMTYPE_H_
#define GOLEMTYPE_H_

#define GOLEM_TYPE_TYPE		(golem_type_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemType,golem_type,GOLEM,TYPE,GObject)

typedef guint32 GolemTypeReference;
typedef guint8  GolemTypeModule;
typedef guint32 GolemTypeName;

#define GOLEM_TYPE_REFERENCE(module,name)	(((guint32)module) << 24 | ((guint32)name))
#define GOLEM_TYPE_GET_MODULE(type_reference)	(type_reference >> 24)
#define GOLEM_TYPE_GET_NAME(type_reference)	((type_reference << 8) >> 8)

#define GOLEM_TYPE_NONE		(0)
#define GOLEM_TYPE_CHAR		GOLEM_TYPE_REFERENCE(0,1)
#define GOLEM_TYPE_UCHAR	GOLEM_TYPE_REFERENCE(0,2)
#define GOLEM_TYPE_INT16	GOLEM_TYPE_REFERENCE(0,3)
#define GOLEM_TYPE_UINT16	GOLEM_TYPE_REFERENCE(0,4)
#define GOLEM_TYPE_INT32	GOLEM_TYPE_REFERENCE(0,5)
#define GOLEM_TYPE_UINT32	GOLEM_TYPE_REFERENCE(0,6)
#define GOLEM_TYPE_INT64	GOLEM_TYPE_REFERENCE(0,7)
#define GOLEM_TYPE_UINT64	GOLEM_TYPE_REFERENCE(0,8)
#define GOLEM_TYPE_FLOAT	GOLEM_TYPE_REFERENCE(0,9)
#define GOLEM_TYPE_DOUBLE	GOLEM_TYPE_REFERENCE(0,10)
#define GOLEM_TYPE_STRING	GOLEM_TYPE_REFERENCE(0,11)
#define GOLEM_TYPE_OBJECT	GOLEM_TYPE_REFERENCE(0,12)
#define GOLEM_TYPE_POINTER	GOLEM_TYPE_REFERENCE(0,13)
#define GOLEM_TYPE_BOOL		GOLEM_TYPE_REFERENCE(0,14)


struct _GolemTypeClass
{
  GObjectClass	parent_class;

  gboolean	(*is_derived)(GolemType * type, GolemType * other_type);
};


const gchar * 	golem_type_get_name(GolemType * type);

GType		golem_type_get_gtype(GolemType * type);

GolemTypeName	golem_type_get_type_name(GolemType * type);

gboolean	golem_type_is_derived(GolemType * type, GolemType * other_type);


#endif /* GOLEMTYPE_H_ */
