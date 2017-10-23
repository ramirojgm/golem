/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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

#define GOLEM_TYPE_TYPE_INFO (golem_type_info_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemTypeInfo,golem_type_info,GOLEM,TYPE_INFO,GObject)

struct _GolemTypeInfoClass
{
  GObjectClass parent_class;

  const gchar * (*get_name)(GolemTypeInfo * type_info);

  GType (*register_type)(GolemTypeInfo * type_info,
			 GolemModule * module,
			 GError ** error);

  gboolean (*get_static)(GolemTypeInfo * type_info,
			 const gchar * name,
			 GValue * dest,
			 GError ** error);

  gboolean (*get_member)(GolemTypeInfo * type_info,
			 GValue * instance,
			 const gchar * name,
			 GValue * dest
			 ,GError ** error);

  gboolean (*set_member)(GolemTypeInfo * type_info,
			 GValue * instance,
			 const gchar * name,
			 const GValue * src,
			 GError ** error);
};

GType		golem_type_info_get_type(void);


const gchar *	golem_type_info_get_name(GolemTypeInfo * type_info);

GType		golem_type_info_register_type(GolemTypeInfo * type_info,
					      GolemModule * module,
					      GError ** error);

gboolean 	golem_type_info_get_static(GolemTypeInfo * type_info,
					   const gchar * name,
					   GValue * dest,
					   GError ** error);


gboolean 	golem_type_info_get_member(GolemTypeInfo * type_info,
					   GValue * instance,
					   const gchar * name,
					   GValue * dest,
					   GError ** error);

gboolean 	golem_type_info_set_member(GolemTypeInfo * type_info,
					   GValue * instance,
					   const gchar * name,
					   const GValue * src,
					   GError ** error);


GolemTypeInfo * golem_type_info_from_gtype(GType type);

GType		golem_type_from_name(const gchar * type_name);

const gchar *	golem_type_get_name(GType type);

#endif /* ENGINE_GOLEMTYPEINFO_H_ */
