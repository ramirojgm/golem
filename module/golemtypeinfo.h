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

#ifndef GOLEMTYPEINFO_H_
#define GOLEMTYPEINFO_H_

typedef struct _GolemTypeInfoClass GolemTypeInfoClass;
typedef struct _GolemTypeInfo GolemTypeInfo;

struct _GolemTypeInfoClass
{
  GolemTypeCode (*get_member_type_code)(GolemTypeInfo * info,
					const gchar * name);

  gboolean (*get_member)(GolemTypeInfo * info,
			 gpointer instance,
			 const gchar * name,
			 GolemVMData * dst,
			 GError ** error);

  gboolean (*set_member)(GolemTypeInfo * info,
			 gpointer instance,
  			 const gchar * name,
  			 GolemVMData * src,
  			 GError ** error);
};

struct _GolemTypeInfo
{
  const GolemTypeInfoClass * klass;
  gchar * name;
};


#endif /* GOLEMTYPEINFO_H_ */
