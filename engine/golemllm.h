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

#ifndef GOLEMLLM_H_
#define GOLEMLLM_H_

typedef struct _GolemStructBuilder GolemStructBuilder;

struct _GolemStructBuilder
{
  guint8 * mem;
  guint8 offset;
  guint8 size;
};

GolemStructBuilder * golem_struct_builder_new(void);

void		golem_struct_builder_append(GolemStructBuilder * struct_builder,const GValue * value);
void		golem_struct_builder_append_string(GolemStructBuilder * struct_builder,const gchar * str1);
void		golem_struct_builder_append_type(GolemStructBuilder * struct_builder,GType type);
void		golem_struct_builder_append_pointer(GolemStructBuilder * struct_builder,gpointer pointer);
void		golem_struct_builder_free(GolemStructBuilder * struct_builder);

void		golem_invoke(gpointer address,GolemStructBuilder * args);
guint8		golem_invoke_guint8(gpointer address,GolemStructBuilder * args);
guint		golem_invoke_guint(gpointer address,GolemStructBuilder * args);
guint64		golem_invoke_guint64(gpointer address,GolemStructBuilder * args);
gulong		golem_invoke_gulong(gpointer address,GolemStructBuilder * args);
gint8		golem_invoke_gint8(gpointer address,GolemStructBuilder * args);
gint		golem_invoke_gint(gpointer address,GolemStructBuilder * args);
gint64		golem_invoke_gint64(gpointer address,GolemStructBuilder * args);
glong		golem_invoke_glong(gpointer address,GolemStructBuilder * args);
gfloat		golem_invoke_gfloat(gpointer address,GolemStructBuilder * args);
gdouble		golem_invoke_gdouble(gpointer address,GolemStructBuilder * args);
gpointer	golem_invoke_gpointer(gpointer address,GolemStructBuilder * args);

#endif /* GOLEMLLM_H_ */
