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

#ifndef GOLEMCLASS_H_
#define GOLEMCLASS_H_

#define GOLEM_TYPE_CLASS	(golem_class_get_type())
G_DECLARE_FINAL_TYPE(GolemClass,golem_class,GOLEM,CLASS,GObject)


typedef struct _GolemClassIter 			GolemClassIter;

struct _GolemClassIter
{
  GType	   type;
  gboolean (*iter_first)(gpointer instance,gpointer * iter_dest);
  gboolean (*iter_next)(gpointer instance,gpointer iter);
  gboolean (*iter_fetch)(gpointer instance,GValue * dest);
  void 	   (*iter_free)(gpointer instance,gpointer iter);
};

struct _GolemClassClass
{
  GObjectClass	parent_class;

};

struct _GolemClass
{
  GObject parent_instance;


};


GType 		golem_class_get_type(void);

GolemClass * 	golem_class_new();

GolemClass *	golem_class_from_type(GType type);

GType		golem_class_register(GolemClass * klass,GError ** error);

void		golem_class_implement(GolemClass * klass,const gchar * interface_name);

void		golem_class_add_private(GolemClass * klass,const gchar * name,GType type);

void		golem_class_add_property(GolemClass * klass,const gchar * name,GType type,GValue * default_value);

void		golem_class_add_func(GolemClass * klass,const gchar * name,GolemFuncMetaData * meta_data);

void		golem_class_add_set_func_body(GolemClass * klass,const gchar * name,GolemFuncMetaData * meta_data,GolemBlock * block);

#endif /* GOLEMCLASS_H_ */
