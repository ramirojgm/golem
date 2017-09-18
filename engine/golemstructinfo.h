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

#ifndef GOLEMSTRUCTINFO_H_
#define GOLEMSTRUCTINFO_H_

#define GOLEM_OFFSET_WITH_PADDING(offset,size) 	((offset) + ((size) > 1 && (offset > 0) ? ((size) - ((offset) % (size))) : 0))

#define GOLEM_TYPE_STRUCT_INFO (golem_struct_info_get_type())
G_DECLARE_FINAL_TYPE(GolemStructInfo,golem_struct_info,GOLEM,STRUCT_INFO,GObject)

struct _GolemStructInfoClass
{
  GObjectClass parent_class;
};

struct _GolemStructInfo
{
  GObject parent_instance;
  GMutex mutex;
  GList * fields;
  gsize size;
};

GType			golem_struct_info_get_type(void);

GolemStructInfo *	golem_struct_info_new(void);

void			golem_struct_info_add_field(GolemStructInfo * struct_info,GType type,const gchar * name);

goffset			golem_struct_info_get_field_offset(GolemStructInfo * struct_info,const gchar * name);

gpointer		golem_struct_info_new_instance(GolemStructInfo * struct_info);

gboolean		golem_struct_info_get(GolemStructInfo * struct_info,gpointer instance,const gchar * name,GValue * dest,GError ** error);

gboolean		golem_struct_info_set(GolemStructInfo * struct_info,gpointer instance,const gchar * name,const GValue * src,GError ** error);

void			golem_struct_info_free_instance(GolemStructInfo * struct_info,gpointer instance);

#endif /* ENGINE_GOLEMSTRUCTINFO_H_ */
