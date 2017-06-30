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

#ifndef ENGINE_GOLEMSTRUCTINFO_H_
#define ENGINE_GOLEMSTRUCTINFO_H_

typedef struct _GolemStructInfoPrivate GolemStructInfoPrivate;
G_DECLARE_FINAL_TYPE(GolemStructInfo,golem_struct_info,GOLEM,STRUCT_INFO,GObject)

struct _GolemStructInfoClass
{
  GObjectClass parent_class;
};

struct _GolemStructInfo
{
  GObjectClass parent_instance;
  GolemStructInfoPrivate * priv;
};

GType 		 golem_struct_info_get_type(void);

GolemStructInfo* golem_struct_info_new(void);

gboolean	 golem_struct_info_resolve(GolemStructInfo * info,GolemContext * context);

GolemStructInfo* golem_struct_info_parse(GolemParser * parse,GError ** error);

gsize		 golem_struct_info_get_size(GolemStructInfo * struct_info);

void		 golem_struct_info_append_attibute(GolemStructInfo * struct_info,GType type,const gchar * name);

gboolean	 golem_struct_info_set(GolemStructInfo * struct_info,gpointer struct_instance,const gchar * name,const GValue * src,GError * error);

gboolean	 golem_struct_info_get(GolemStructInfo * struct_info,gpointer struct_instance,const gchar * name,GValue * dest,GError * error);

void		 golem_struct_info_free(GolemStructInfo * struct_info,gpointer struct_instance);

#endif /* ENGINE_GOLEMSTRUCTINFO_H_ */
