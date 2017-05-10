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

#ifndef GOLEMCONTEXT_H_
#define GOLEMCONTEXT_H_

#define GOLEM_TYPE_CONTEXT (golem_context_get_type())
G_DECLARE_FINAL_TYPE(GolemContext,golem_context,GOLEM,CONTEXT,GObject)

typedef struct _GolemClosure GolemClosure;

struct _GolemContextClass
{
  GObjectClass parent_class;
};

struct _GolemContext
{
  GObject parent_instace;
  GMutex mutex;
};

GolemContext *	golem_context_new(GolemContext * parent);

void		golem_context_set_parent(GolemContext * context,GolemContext * parent);

GolemContext *	golem_context_get_parent(GolemContext * context);

void		golem_context_set_instance(GolemContext * context,GObject * instance);

GObject *	golem_context_get_instance(GolemContext * context);

gboolean	golem_context_declare(GolemContext * context,const gchar * name,GType type,GError ** error);

gboolean	golem_context_set(GolemContext * context,const gchar * name,GValue * value,GError ** error);

gboolean	golem_context_set_auto(GolemContext * context,const gchar * name,GValue *  value,GError ** error);

void		golem_context_add_function(GolemContext * context,const gchar * name,GolemClosure * closure);

gboolean	golem_context_get(GolemContext * context,const gchar * name, GValue * value,GError ** error);


#endif /* GOLEMCONTEXT_H_ */
