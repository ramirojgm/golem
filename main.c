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
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>


#include "engine/golem.h"


gint
main(gint argc,gchar * argv[])
{
  GolemContext * context = golem_context_new(NULL);
  gchar * script_file_content = NULL;

  GError * parser_error = NULL;

  g_file_get_contents("golem.glm",&script_file_content,NULL,NULL);
  GolemCompiled * compilation = golem_compiled_new();
  golem_compiled_add_string(compilation,script_file_content,-1,NULL);
  g_free(script_file_content);

  golem_compiled_run(compilation,context,NULL);
  GValue func_value = G_VALUE_INIT;
  GValue var = G_VALUE_INIT;
  golem_context_get(context,"string_value",&var,NULL);

  GValue result = G_VALUE_INIT;
  GValue ** args = g_new0(GValue*,3);
  args[0] = g_new0(GValue,1);
  args[1] = &var;
  g_value_init(args[0],G_TYPE_STRING);
  //g_value_init(args[1],G_TYPE_STRING);
  g_value_set_string(args[0],"hello world (%s)\n");

  golem_context_get(context,"g_print",&func_value,NULL);
  golem_func_invoke(GOLEM_FUNC(g_value_get_object(&func_value)),args,&result,NULL);
  g_object_unref(context);
  g_object_unref(compilation);
  return 0;
}

