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

typedef struct _GolemFunctionSpec GolemFunctionSpec;
typedef struct _GolemPropertySpec GolemPropertySpec;
typedef struct _GolemTypeSpec GolemTypeSpec;

typedef struct _GolemTypePrivatePrivate GolemTypePrivatePrivate;

typedef enum _GolemFunctionType GolemFunctionType;


#define GOLEM_TYPE_TYPE_INFO	(golem_type_info_get_type())
G_DECLARE_FINAL_TYPE(GolemTypeInfo,golem_type_info,GOLEM,TYPE_INFO,GObject)

#define GOLEM_TYPE_TYPE_PRIVATE	(golem_type_private_get_type())
G_DECLARE_FINAL_TYPE(GolemTypePrivate,golem_type_private,GOLEM,TYPE_PRIVATE,GObject)

enum _GolemFunctionType
{
  GOLEM_FUNCTION_SYMBOLIC,
  GOLEM_FUNCTION_VIRTUAL,
  GOLEM_FUNCTION_INTERNAL,
  GOLEM_FUNCTION_CLOSURED
};


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

struct _GolemTypePrivateClass
{
	GObjectClass parent_class;
};

struct _GolemTypePrivate
{
	GObject parent_instance;
	GolemTypePrivatePrivate * priv;
};

GType 		golem_type_private_get_type(void);

GolemTypePrivate * golem_type_private_new(void);

GType 		golem_type_info_get_type(void);

GolemTypeInfo* 	golem_type_info_new(const gchar * name);

GolemTypeInfo*	golem_type_info_from_gtype(GType type);

GolemStatement *golem_type_info_get_init(GolemTypeInfo * info);

void		golem_type_info_set_init(GolemTypeInfo * info,GolemStatement * statement);

GolemStatement *golem_type_info_get_dispose(GolemTypeInfo * info);

void		golem_type_info_set_dispose(GolemTypeInfo * info,GolemStatement * statement);

GolemStatement *golem_type_info_get_constructed(GolemTypeInfo * info);

void		golem_type_info_set_constructed(GolemTypeInfo * info,GolemStatement * statement);

void		golem_type_info_set_context(GolemTypeInfo * info,GolemContext * context);

GType		golem_type_info_register(GolemTypeInfo * info,GolemContext * context,GError ** error);

gboolean	golem_type_info_get_static(GType type,const gchar * name,GValue * dest,GError ** error);

gboolean	golem_type_info_get(const GValue * instance,const gchar * name,GValue * dest,GError ** error);

gboolean	golem_type_info_set(const GValue * instance,const gchar * name,const GValue * src,GError ** error);

void		golem_type_info_add_base(GolemTypeInfo * info,GolemTypeSpec * spec);

void		golem_type_info_add_function(GolemTypeInfo * info,GolemFunctionSpec * spec);

void		golem_type_info_add_property(GolemTypeInfo * info,GolemPropertySpec * spec);


GolemTypeSpec *	golem_type_spec_new(const gchar * type_name);

GolemTypeSpec *	golem_type_spec_parse(GolemParser * parser,GError ** error);

GType		golem_type_spec_get(GolemTypeSpec * type_spec,GolemContext * context,GError ** error);

GolemFunctionSpec * golem_function_symbol_new(GolemClosureInfo * info,const gchar * symbol_name);

GolemFunctionSpec * golem_function_virtual_new(GolemClosureInfo * info,goffset offset);

GolemFunctionSpec * golem_function_internal_new(GolemClosureInfo * info,GolemStatement * body);

GolemFunctionSpec * golem_function_closured_new(const gchar * name,GolemClosureInvokeFunc func);


#endif /* GOLEMTYPEINFO_H_ */
