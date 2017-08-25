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

#ifndef GOLEMCOMPILED_H_
#define GOLEMCOMPILED_H_

#define GOLEM_TYPE_COMPILED (golem_compiled_get_type())
G_DECLARE_FINAL_TYPE(GolemCompiled,golem_compiled,GOLEM,COMPILED,GObject)

typedef struct _GolemCompiledPrivate GolemCompiledPrivate;

struct _GolemCompiledClass
{
  GObjectClass parent_class;

};

struct _GolemCompiled
{
  GObject parent_instance;
  GolemCompiledPrivate * priv;
};

GType 		golem_compiled_get_type();

GolemCompiled * golem_compiled_new();

gchar **	golem_compiled_get_references(GolemCompiled * compiled,gsize * length);

gboolean	golem_compiled_add_string(GolemCompiled * compiled,const gchar * source_name,const gchar * str,gssize length,GError ** error);

gboolean	golem_compiled_add_data(GolemCompiled * compiled,const guint8 * data,gsize length,GError ** error);

gboolean	golem_compiled_run(GolemCompiled * compiled,GolemContext * context,GError ** error);

gboolean	golem_compiled_save_to_buffer(GolemCompiled * compiled,guint8 ** buffer,gsize * buff_length);

#endif /* GOLEMCOMPILED_H_ */
