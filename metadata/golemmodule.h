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

#ifndef GOLEMMODULE_H_
#define GOLEMMODULE_H_

#define GOLEM_TYPE_MODULE	(golem_module_get_type())
G_DECLARE_FINAL_TYPE(GolemModule,golem_module,GOLEM,MODULE,GObject)

typedef guint32	GolemSymbolName;
typedef struct _GolemModulePrivate GolemModulePrivate;

struct _GolemModuleClass
{
  GObjectClass parent_class;
};

struct _GolemModule
{
  GObject parent_instance;

  GolemModulePrivate * priv;
};

GType		golem_module_get_type(void);

GolemModule * 	golem_module_load_from_stream(GolemModuleManager * mm,
					      GInputStream * stream,
					      GError ** error);

gboolean	golem_module_save_to_stream(GolemModule * module,
					    GOutputStream * stream,
					    GError ** error);

gchar **	golem_module_get_packages(GolemModule * module,
					  gsize * length);

GolemModule **	golem_module_get_references(GolemModule * module,
					    gsize * length);

GolemType **	golem_module_get_types(GolemModule * module,
				       gssize * length);

GolemType *	golem_module_resolve_type(GolemModule * module,
					  GolemTypeReference reference);

gpointer	golem_module_get_symbol(GolemModule * module,
					const gchar * name,
					GError ** error);

gpointer	golem_module_get_symbol_by_name(GolemModule * module,
						GolemSymbolName name,
						GError ** error);

#endif /* GOLEMMODULE_H_ */
