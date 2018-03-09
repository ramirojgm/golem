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

#ifndef GOLEMSCOPEBUILDER_H_
#define GOLEMSCOPEBUILDER_H_

typedef struct _GolemScopeBuilderPrivate GolemScopeBuilderPrivate;

#define GOLEM_TYPE_SCOPE_BUILDER	(golem_scope_builder_get_type())
G_DECLARE_FINAL_TYPE(GolemScopeBuilder,golem_scope_builder,GOLEM,SCOPE_BUILDER,GObject)

struct _GolemScopeBuilderClass
{
  GObjectClass parent_class;
};

struct _GolemScopeBuilder
{
  GObject parent_instance;

  GolemScopeBuilderPrivate * priv;
};

G_BEGIN_DECLS

GLIB_AVAILABLE_IN_ALL
GType			golem_scope_builder_get_type(void);

GLIB_AVAILABLE_IN_ALL
GolemScopeBuilder * 	golem_scope_builder_new();

GLIB_AVAILABLE_IN_ALL
gboolean		golem_scope_builder_define(GolemScopeBuilder * scope,
						   GolemTypeCode type,
						   const gchar * name,
						   GError ** error);

GLIB_AVAILABLE_IN_ALL
GolemTypeCode		golem_scope_builder_type(GolemScopeBuilder * scope,
						 const gchar * name);

GLIB_AVAILABLE_IN_ALL
gboolean		golem_scope_builder_enter(GolemScopeBuilder * scope,
						  GolemVMBody * body,
						  GError ** error);

GLIB_AVAILABLE_IN_ALL
gboolean		golem_scope_builder_get(GolemScopeBuilder * scope,
						GolemVMBody * body,
						const gchar * name,
						GError ** error);

GLIB_AVAILABLE_IN_ALL
gboolean		golem_scope_builder_set(GolemScopeBuilder * scope,
						GolemVMBody * body,
						const gchar * name,
						GError ** error);

GLIB_AVAILABLE_IN_ALL
gboolean		golem_scope_builder_exit(GolemScopeBuilder * scope,
						 GolemVMBody * body,
						 GError ** error);

G_END_DECLS

#endif /* GOLEMCONTEXTBUILDER_H_ */
