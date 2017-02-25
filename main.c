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
  GValue  main_argc = G_VALUE_INIT,
	  main_argv = G_VALUE_INIT,
	  const_true = G_VALUE_INIT,
	  const_false = G_VALUE_INIT;

  g_value_init(&main_argc,G_TYPE_INT);
  g_value_init(&main_argv,G_TYPE_POINTER);
  g_value_init(&const_true,G_TYPE_BOOLEAN);
  g_value_init(&const_false,G_TYPE_BOOLEAN);

  g_value_set_int(&main_argc,argc);
  g_value_set_pointer(&main_argv,argv);
  g_value_set_boolean(&const_true,TRUE);
  g_value_set_boolean(&const_false,TRUE);

  golem_context_set_auto(context,"builtin_argc",&main_argc,NULL);
  golem_context_set_auto(context,"builtin_argv",&main_argv,NULL);
  golem_context_set_auto(context,"true",&const_true,NULL);
  golem_context_set_auto(context,"false",&const_false,NULL);

  golem_context_set_function(context,"print",g_print,G_TYPE_NONE,G_TYPE_STRING,-1);

  g_file_get_contents("golem.glm",&script_file_content,NULL,NULL);
  GolemCompiled * compilation = golem_compiled_new();
  golem_compiled_add_string(compilation,script_file_content,-1,NULL);
  g_free(script_file_content);
  golem_compiled_run(compilation,context,NULL);
  g_object_unref(context);
  g_object_unref(compilation);

  return 0;
}

