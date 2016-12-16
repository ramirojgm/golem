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

#ifndef GOLEMFUNC_H_
#define GOLEMFUNC_H_

#define GOLEM_TYPE_FUNC 	(golem_func_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemFunc,golem_func,GOLEM,FUNC,GObject)

typedef struct _GolemFuncMetaData GolemFuncMetaData;
typedef struct _GolemFuncParam GolemFuncParam;
typedef struct _GolemArgs GolemArgs;

/*struct _GolemArgs{
  guint8 padding[16];
};*/


struct _GolemFuncClass{
  GObjectClass parent_class;

  gboolean (*invoke)(GolemFunc * func,GValue ** args,GValue * result,GError ** error);

  gpointer (*get_address)(GolemFunc * func);
};

struct _GolemFuncParam
{
  gchar * name;
  GType   type;
  const gchar * type_name;
  gboolean is_reference: 1;
  gboolean is_array : 1;
  gboolean catch_exception: 1;
};

struct _GolemFuncMetaData
{
  gboolean is_resolved: 1;
  gchar * name;
  const gchar * return_type_name;
  GType return_type;
  GList * params;

};

GType	golem_func_get_type(void);

GolemFunc * golem_func_new(GolemFuncMetaData * meta_data,gpointer address);

gboolean golem_func_invoke(GolemFunc * func,GValue ** args,GValue * result,GError ** error);

gpointer golem_func_get_address(GolemFunc * func);

GolemFuncMetaData *	golem_func_meta_data_new();

GolemFuncMetaData *	golem_func_meta_data_parse(GolemParser * parser,GError ** error);

void			golem_func_meta_data_set_return_type(GolemFuncMetaData * meta_data,GType return_type);

GType			golem_func_meta_data_get_return_type(GolemFuncMetaData * meta_data);

void			golem_func_meta_data_set_name(GolemFuncMetaData * meta_data,const gchar * name);

const gchar *		golem_func_meta_data_get_name(GolemFuncMetaData * meta_data);

void			golem_func_meta_data_add_param(GolemFuncMetaData * meta_data,const gchar * name,GType type,gboolean is_reference,gboolean is_array);

void			golem_func_meta_data_catch_exception(GolemFuncMetaData * meta_data);

gboolean		golem_func_meta_data_resolve(GolemFuncMetaData * meta_data,GError ** error);

#endif /* GOLEMFUNC_H_ */
