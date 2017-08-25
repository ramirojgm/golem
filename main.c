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
#include <stdlib.h>
#include <string.h>

#include "engine/golem.h"

GList * _resolved_references = NULL;

typedef struct
{
  gchar * name;
  GolemCompiled * compiled;
}GolemReference;


gboolean
golem_reference_run(GolemContext * context,GError ** error)
{
  gboolean done = TRUE;
  for(GList * iter = g_list_first(_resolved_references);iter;iter = g_list_next(iter))
    {
      GolemReference * reference = (GolemReference*) iter->data;
      GolemContext * reference_context = golem_context_new(context);
      done = golem_compiled_run(reference->compiled,reference_context,error);
      g_object_unref(reference_context);
      if(!done)
	break;
    }
  return done;
}

gboolean
golem_reference_check(const gchar * name)
{
  for(GList * iter = g_list_first(_resolved_references);iter;iter = g_list_next(iter))
    {
      GolemReference * reference = (GolemReference*) iter->data;
      if(g_strcmp0(reference->name,name) == 0)
	return TRUE;
    }
  return FALSE;
}

void
golem_reference_add(const gchar * reference,GolemCompiled * compiled)
{
  GolemReference * resolved = g_new0(GolemReference,1);
  resolved->name = g_strdup(reference);
  resolved->compiled = GOLEM_COMPILED(g_object_ref(compiled));
  _resolved_references = g_list_prepend(_resolved_references,resolved);
}

gboolean
golem_reference_resolve(GolemCompiled * compiled,GError ** error)
{
  gsize reference_count = 0;
  gchar ** reference_names = golem_compiled_get_references(compiled,&reference_count);
  gboolean done = TRUE;
  for(gint index = 0;index < reference_count;index ++)
    {
      const gchar * reference_name = reference_names[index];
      if(!golem_reference_check(reference_name))
	{
	  gchar * reference_path = g_strconcat(reference_name,".glm",NULL);
	  for(gchar * ref_index = reference_path;*ref_index;ref_index ++)
	    {
	      if(*ref_index == '.' && !g_str_has_prefix(ref_index,".glm"))
		*ref_index = G_DIR_SEPARATOR;
	    }
	  if(g_file_test(reference_path,G_FILE_TEST_IS_REGULAR))
	    {
	      gchar * script = NULL;
	      if((done = g_file_get_contents(reference_path,&script,NULL,error)))
		{
		  GolemCompiled * compiled = golem_compiled_new();
		  if((done = golem_compiled_add_string(compiled,reference_path,script,-1,error)))
		    {
		      golem_reference_add(reference_name,compiled);
		      done = golem_reference_resolve(compiled,error);
		    }
		  g_object_unref(compiled);
		  g_free(script);
		}
	    }
	  else
	    {
	      if(error)
		  *error = g_error_new(GOLEM_ERROR,GOLEM_NOT_EXISTS_ERROR,"not found '%s'",reference_path);
	      done = FALSE;
	    }
	  g_free(reference_path);
	}

      if(!done)
	break;
    }
  g_strfreev(reference_names);
  return done;
}


static gboolean
golem_print_func(GolemClosure * self,GolemClosureInvoke * invoke,gpointer data)
{
  GValue value = G_VALUE_INIT;
  while(golem_closure_invoke_next(invoke,&value))
    {
      GValue string_value = G_VALUE_INIT;
      g_value_init(&string_value,G_TYPE_STRING);
      if(g_value_transform(&value,&string_value))
	{
	  g_print("%s",g_value_get_string(&string_value));
	}
      else if(G_VALUE_HOLDS_GTYPE(&value))
	{
	  g_print("<type: %s>",g_type_name(g_value_get_gtype(&value)));
	}
      else if(G_VALUE_HOLDS_OBJECT(&value) || G_VALUE_HOLDS_BOXED(&value))
	{
	  gpointer instance = g_value_get_object(&value);
	  g_print("<%s: %p>",G_VALUE_TYPE_NAME(&value),instance);
	}
      else if(G_VALUE_HOLDS_POINTER(&value))
	{
	  gpointer pointer = g_value_get_pointer(&value);
	  g_print("%p",pointer);
	}
      g_value_unset(&string_value);
      g_value_unset(&value);
    }
  return TRUE;
}



gint
main(gint argc,gchar ** argv)
{
  if(argc <= 1)
    {
      g_error("no input file");
      return 0;
    }

  GolemContext * context = golem_context_new(NULL);
  gchar * script_file_content = NULL;
  GValue  main_func = G_VALUE_INIT;

  GolemClosure * print_closure = golem_closure_new(golem_print_func,NULL,NULL);

  golem_context_add_function(context,"print",print_closure);

  g_closure_unref(G_CLOSURE(print_closure));

  GError * compile_error = NULL;

  g_file_get_contents(argv[1],&script_file_content,NULL,NULL);
  GolemCompiled * compilation = golem_compiled_new();
  golem_compiled_add_string(compilation,argv[1],script_file_content,-1,&compile_error);
  g_free(script_file_content);
  if(golem_reference_resolve(compilation,&compile_error))
    {
      if(golem_reference_run(context,NULL))
	{
	  golem_compiled_run(compilation,context,NULL);

	  if(golem_context_get(context,"main",&main_func,NULL))
	    {
	      GArray * array = g_array_sized_new(TRUE,TRUE,sizeof(gchar*),TRUE);
	      for(gint iarg = 1;iarg < argc;iarg ++)
		{
		  g_array_append_val(array,argv[iarg]);
		}

	      GValue main_argc = G_VALUE_INIT,
		     main_argv = G_VALUE_INIT;

	      g_value_init(&main_argc,G_TYPE_INT);
	      g_value_init(&main_argv,G_TYPE_ARRAY);

	      g_value_set_int(&main_argc,argc-1);
	      g_value_set_boxed(&main_argv,array);

	      GolemClosureInvoke * invoke = golem_closure_invoke_new();
	      golem_closure_invoke_push(invoke,&main_argc);
	      golem_closure_invoke_push(invoke,&main_argv);
	      golem_closure_invoke(GOLEM_CLOSURE(g_value_get_boxed(&main_func)), invoke);
	      g_value_unset(&main_argc);
	      g_value_unset(&main_argv);
	      g_array_free(array,TRUE);

	      golem_closure_invoke_free(invoke);
	    }
	}
    }
  else
    {
      if(compile_error)
	{
	  g_error("%s",compile_error->message);
	  g_error_free(compile_error);
	}
    }
  g_object_unref(context);
  g_object_unref(compilation);

  return 0;
}

