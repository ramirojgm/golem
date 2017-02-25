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

#ifndef GOLEMJIT_H_
#define GOLEMJIT_H_

typedef struct _GolemArgs GolemArgs;

struct _GolemArgs
{
  guint8 * mem;
  guint16 offset;
};

GolemArgs * 	golem_args_new();

void		golem_args_append(GolemArgs * args,const GValue * value);
void		golem_args_append_string(GolemArgs * args,const gchar * str1);
void		golem_args_append_type(GolemArgs * args,GType type);
void		golem_args_append_pointer(GolemArgs * args,gpointer pointer);
void		golem_args_free(GolemArgs * args);

void		golem_invoke(gpointer address,GolemArgs * args);
guint8		golem_invoke_guint8(gpointer address,GolemArgs * args);
guint		golem_invoke_guint(gpointer address,GolemArgs * args);
guint64		golem_invoke_guint64(gpointer address,GolemArgs * args);
gulong		golem_invoke_gulong(gpointer address,GolemArgs * args);
gint8		golem_invoke_gint8(gpointer address,GolemArgs * args);
gint		golem_invoke_gint(gpointer address,GolemArgs * args);
gint64		golem_invoke_gint64(gpointer address,GolemArgs * args);
glong		golem_invoke_glong(gpointer address,GolemArgs * args);
gpointer	golem_invoke_gpointer(gpointer address,GolemArgs * args);
gfloat		golem_invoke_gfloat(gpointer address,GolemArgs * args);
gdouble		golem_invoke_gdouble(gpointer address,GolemArgs * args);
gpointer	golem_invoke_boxed(gpointer address,GolemArgs * args);
GObject *	golem_invoke_gobject(gpointer address,GolemArgs * args);
gchar *		golem_invoke_string(gpointer address,GolemArgs * args);

#endif /* GOLEMJIT_H_ */
