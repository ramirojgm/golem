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

#ifndef GOLEMMODULE_H_
#define GOLEMMODULE_H_

typedef struct _GolemModulePrivate GolemModulePrivate;

#define GOLEM_TYPE_MODULE (golem_module_get_type())
G_DECLARE_FINAL_TYPE(GolemModule,golem_module,GOLEM,MODULE,GObject)

typedef struct _GolemTypeInfo GolemTypeInfo;

struct _GolemModuleClass
{
  GObjectClass parent_class;
};

struct _GolemModule
{
  GObject parent_instance;
  GMutex module_mutex;
  GolemModulePrivate * priv;
};

GType		golem_module_get_type();

GolemModule *	golem_module_new();

GolemContext *	golem_module_get_context(GolemModule * module);

gboolean	golem_module_use(GolemModule * module,GError ** error);

void		golem_module_unuse(GolemModule * module);

GType		golem_module_register_type(GolemModule *module,
					   GolemTypeInfo * info,
					   GType parent_type,
					   const gchar *type_name,
					   const GTypeInfo *type_info,
					   GTypeFlags flags);

GType *		golem_module_get_types(GolemModule * module,gsize * n_types);

gchar **	golem_module_get_references(GolemModule * module,gsize * n_references);

GolemTypeInfo *	golem_module_get_type_info(GolemModule * module,GType type);

gboolean	golem_module_compile(GolemModule * module,const gchar * source_name,const gchar * code,gssize code_length,GError ** error);


#endif /* GOLEMMODULE_H_ */
