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

#ifndef GOLEMCLASSINFO_H_
#define GOLEMCLASSINFO_H_

typedef struct _GolemClassInfoPrivate GolemClassInfoPrivate;

typedef struct _GolemFunctionSpec GolemFunctionSpec;

typedef struct _GolemPropertySpec GolemPropertySpec;

typedef struct _GolemIterator GolemIterator;

#define GOLEM_TYPE_CLASS_INFO	(golem_class_info_get_type())
G_DECLARE_FINAL_TYPE(GolemClassInfo,golem_class_info,GOLEM,CLASS_INFO,GolemTypeInfo)


struct _GolemClassInfoClass
{
  GolemTypeInfoClass parent_class;

};

struct _GolemClassInfo
{
  GolemTypeInfo	parent_instance;
  GMutex mutex;
  GolemClassInfoPrivate * priv;
};


GType 		golem_class_info_get_type(void);

GolemClassInfo*	golem_class_info_new(const gchar * name);

void		golem_class_info_set_parent(GolemClassInfo * info,const gchar * parent_name);

void		golem_class_info_add_function(GolemClassInfo * info,GolemFunctionSpec * spec);

void		golem_class_info_add_property(GolemClassInfo * info,GolemPropertySpec * spec);

GolemStatement*	golem_class_info_get_init(GolemClassInfo * info);

void		golem_class_info_set_init(GolemClassInfo * info,GolemStatement * statement);

GolemStatement*	golem_class_info_get_dispose(GolemClassInfo * info);

void		golem_class_info_set_dispose(GolemClassInfo * info,GolemStatement * statement);

GolemStatement*	golem_class_info_get_constructed(GolemClassInfo * info);

void		golem_class_info_set_constructed(GolemClassInfo * info,GolemStatement * statement);


GolemFunctionSpec * golem_function_spec_new(GolemClosureInfo * info,GolemStatement * body);

GolemFunctionSpec * golem_function_spec_new_static(GolemClosureInfo * info,GolemStatement * body);

GolemPropertySpec * golem_property_spec_new(const gchar * type_name,const gchar * property_name,GolemStatement * get,GolemStatement * set);


#endif /* GOLEMCLASSINFO_H_ */
