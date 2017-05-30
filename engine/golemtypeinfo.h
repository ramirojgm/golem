/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
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

typedef struct _GolemTypeInfoPrivate GolemTypeInfoPrivate;
typedef struct _GolemMethod GolemMethod;
typedef struct _GolemProperty GolemProperty;
typedef enum _GolemMethodType GolemMethodType;

#define GOLEM_TYPE_TYPE_INFO	(golem_type_info_get_type())
G_DECLARE_FINAL_TYPE(GolemTypeInfo,golem_type_info,GOLEM,TYPE_INFO,GObject)


struct _GolemTypeInfoClass
{
  GObjectClass	parent_class;

};

struct _GolemTypeInfo
{
  GObject parent_instance;
  GMutex mutex;
  GolemTypeInfoPrivate * priv;
};

enum _GolemMethodType
{
  GOLEM_METHOD_STATIC,
  GOLEM_METHOD_INSTANCED,
  GOLEM_METHOD_VIRTUAL,
  GOLEM_METHOD_MODIFICATOR
};

static

GType 		golem_type_info_get_type(void);

GolemTypeInfo* 	golem_type_info_new();

GolemTypeInfo*	golem_type_info_from_gtype(GType type);

gboolean	golem_type_info_register(GolemTypeInfo * type_info,GolemContext * context,GError ** error);

const gchar *	golem_type_info_get_name(GolemTypeInfo * type_info);

void		golem_type_info_set_name(GolemTypeInfo * type_info,const gchar * name);

void		golem_type_info_set_init(GolemTypeInfo * type_info,GolemStatement * statement);

GolemStatement* golem_type_info_get_init(GolemTypeInfo * type_info);

void		golem_type_info_set_complete(GolemTypeInfo * type_info,GolemStatement * statement);

GolemStatement* golem_type_info_get_init(GolemTypeInfo * type_info);

void		golem_type_info_set_constructed(GolemTypeInfo * type_info,GolemStatement * statement);

GolemStatement* golem_type_info_get_constructed(GolemTypeInfo * type_info);

void		golem_type_info_set_dispose(GolemTypeInfo * type_info,GolemStatement * statement);

GolemStatement* golem_type_info_get_dispose(GolemTypeInfo * type_info);

void		golem_type_info_add_method(GolemTypeInfo * type_info,GolemMethod * method);

void		golem_type_info_add_property(GolemTypeInfo * type_info,GolemProperty * property);

gboolean	golem_type_info_get_static(GType type,const gchar * name,GValue * dest,GError ** error);

gboolean	golem_type_info_get(gpointer instance,const gchar * name,GValue * dest,GError ** error);

gboolean	golem_type_info_set(gpointer instance,const gchar * name,const GValue * src,GError ** error);

GolemProperty *	golem_property_new(GParamSpec * property,GolemStatement *  get,GolemStatement * set);

void		golem_property_free(GolemProperty *  property);

GolemMethod *	golem_method_new(GolemMethodType type,GolemClosureInfo * info,GCallback callback,goffset offset);

void		golem_method_free(GolemMethod * method);

#endif /* GOLEMTYPEINFO_H_ */
