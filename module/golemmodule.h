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

#ifndef GOLEM_MODULE_H_
#define GOLEM_MODULE_H_

#define GOLEM_TYPE_TYPE_MODULE	(golem_type_module_get_type())
G_DECLARE_FINAL_TYPE(GolemTypeModule,golem_type_module,GOLEM,TYPE_MODULE,GTypeModule)

typedef struct _GolemTypeModulePrivate GolemTypeModulePrivate;

typedef struct _GolemTypeInfo GolemTypeInfo;
typedef struct _GolemStructInfo GolemStructInfo;
typedef struct _GolemObjectInfo GolemObjectInfo;
typedef struct _GolemSymbolInfo GolemSymbolInfo;
typedef struct _GolemPropertyInfo GolemPropertyInfo;

struct _GolemTypeModuleClass
{
  GTypeModuleClass parent_class;
};

struct _GolemTypeModule
{
  GTypeModule parent_instance;
  /* private */
  GolemTypeModulePrivate * priv;
};

G_BEGIN_DECLS

GType		 golem_type_module_get_type(void);

GolemTypeModule *golem_type_module_new(void);


gboolean	 golem_type_module_load_from_file(GolemTypeModule * type_module,
						  const gchar * filename,
						  GError ** error);


gboolean	 golem_type_module_load_from_data(GolemTypeModule * type_module,
						  gpointer data,
						  gsize data_size,
						  GError ** error);

gboolean	 golem_type_module_load(GolemTypeModule * type_module,
					GInputStream * stream,
					GError ** error);

gboolean	 golem_type_module_parse(GolemTypeModule * type_module,
					 const gchar * name,
					 const gchar * str,
					 gsize length,
					 GError ** error);

gboolean	 golem_type_module_compile(GolemTypeModule * type_module,
					   GError ** error);

gchar **	 golem_type_module_get_type_names(GolemTypeModule * type_module,
						  gsize * length);

GolemTypeInfo**	 golem_type_module_get_types(GolemTypeModule * type_module,
						  gsize * length);

gchar **	 golem_type_module_get_symbol_names(GolemTypeModule * type_module,
						    gsize * length);

GolemSymbolInfo** golem_type_module_get_symbols(GolemTypeModule * type_module,
						gsize * length);

gboolean	 golem_type_module_get_symbol(GolemTypeModule * type_module,
					      const gchar * symbol_name,
					      gpointer * symbol,
					      GolemSymbolInfo ** symbol_info,
					      GError ** error);

gboolean	 golem_type_module_save_to_file(GolemTypeModule * type_module,
						const gchar * filename,
						GError ** error);

gboolean	 golem_type_module_save_to_buffer(GolemTypeModule * type_module,
						  gpointer * buffer,
						  gsize * length,
						  GError ** error);

GolemTypeInfo *	 golem_type_module_get_type_info(GolemTypeModule * type_module,
						 const gchar * type_name);

G_END_DECLS

#endif /* GOLEM_MODULE_H_ */
