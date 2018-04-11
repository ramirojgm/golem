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

#include "../golem.h"

struct _GolemTypeModulePrivate
{
  GList * symbols;
  GList * type_objects;
  GList * type_struct;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemTypeModule,golem_type_module,G_TYPE_TYPE_MODULE)

typedef struct _GolemTypeInfoClass GolemTypeInfoClass;
typedef struct _GolemSymbolArgumentInfo GolemSymbolArgumentInfo;

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

struct _GolemStructInfo
{
  GolemTypeInfo parent;
};

struct _GolemObjectInfo
{
  GolemTypeInfo parent;
  GType	gtype;
  guint32 n_properties;
  GolemPropertyInfo ** properties;
  guint32 n_symbols;
  GolemSymbolInfo ** symbols;
};

struct _GolemSymbolArgumentInfo
{
  gchar * 	name;
  gchar * 	type_name;
  GolemTypeCode type_code;
};

struct _GolemSymbolInfo
{
  /* data */
  gboolean is_external;
  gboolean is_static;
  gchar * name;
  /* return */
  GolemTypeCode return_type_code;
  gboolean return_constant;
  gchar * return_type_name;
  /* arguments */
  guint32 n_arguments;
  GolemSymbolArgumentInfo ** arguments;
  /* function */
  gpointer callable_func;
  gpointer symbol_func;
};

struct _GolemFunctionInfo
{
  GolemSymbolInfo parent;
  GolemStatement * stmt_body;
  GolemVMBody * body;
};

struct _GolemPropertyInfo
{
  GParamSpec * spec;
  GolemVMBody * get_body;
  GolemVMBody * set_body;
};




GolemTypeModule *
golem_type_module_new(void)
{
  return GOLEM_TYPE_MODULE(g_object_new(GOLEM_TYPE_TYPE_MODULE,NULL));
}


gboolean
golem_type_module_load_from_file(GolemTypeModule * type_module,
				 const gchar * filename,
				 GError ** error)
{

}


gboolean
golem_type_module_load_from_data(GolemTypeModule * type_module,
				  gpointer data,
				  gsize data_size,
				  GError ** error)
{

}

gboolean
golem_type_module_load(GolemTypeModule * type_module,
			GInputStream * stream,
			GError ** error)
{

}

gboolean
golem_type_module_parse(GolemTypeModule * type_module,
			 const gchar * name,
			 const gchar * str,
			 gsize length,
			 GError ** error)
{


}

gboolean
golem_type_module_compile(GolemTypeModule * type_module,
			   GError ** error)
{

}

gchar **
golem_type_module_get_type_names(GolemTypeModule * type_module,
				  gsize * length)
{

}

gchar **
golem_type_module_get_symbol_names(GolemTypeModule * type_module,
				    gsize * length)
{

}

gboolean
golem_type_module_get_symbol(GolemTypeModule * type_module,
			      const gchar * symbol_name,
			      gpointer * symbol,
			      GolemSymbolInfo ** symbol_info,
			      GError ** error)
{

}

gboolean
golem_type_module_save_to_file(GolemTypeModule * type_module,
				const gchar * filename,
				GError ** error)
{

}

gboolean
golem_type_module_save_to_buffer(GolemTypeModule * type_module,
				  gpointer * buffer,
				  gsize * length,
				  GError ** error)
{

}

gboolean
golem_type_module_save(GolemTypeModule * type_module,
		       GOutputStream * stream,
		       GError ** error)
{

}

static void
golem_type_module_init(GolemTypeModule * self)
{
  self->priv = golem_type_module_get_instance_private(self);
}

static void
golem_type_module_class_init(GolemTypeModuleClass * klass)
{

}
