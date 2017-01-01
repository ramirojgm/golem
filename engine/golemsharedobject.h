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

#ifndef GOLEMSHAREDOBJECT_H_
#define GOLEMSHAREDOBJECT_H_

typedef struct _GolemSharedObjectPrivate GolemSharedObjectPrivate;

#define GOLEM_TYPE_SHARED_OBJECT (golem_shared_object_get_type())

G_DECLARE_FINAL_TYPE(GolemSharedObject,golem_shared_object,GOLEM,SHARED_OBJECT,GolemSentence)

struct _GolemSharedObjectClass
{
  GolemSentenceClass parent_class;
};

struct _GolemSharedObject
{
  GolemSentence	     parent_instance;
  GolemSharedObjectPrivate * priv;
};

GType		golem_shared_object_get_type(void);

gboolean	golem_shared_object_check(GolemParser * parser);

GolemSentence *	golem_shared_object_parse(GolemParser * parser,GError ** error);

gpointer	golem_shared_object_get_symbol(const gchar * name);

#endif /* GOLEMSHAREDOBJECT_H_ */
