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

static gboolean
golem_convert_func(GolemClosure * self,GolemClosureInvoke * invoke,gpointer data)
{
  gboolean done = FALSE;
  if(golem_closure_invoke_get_length(invoke) == 2)
    {
      GValue src = G_VALUE_INIT;
      GValue dest = G_VALUE_INIT;
      GValue gtype = G_VALUE_INIT;

      golem_closure_invoke_next(invoke,&gtype);
      golem_closure_invoke_next(invoke,&src);
      if(G_VALUE_HOLDS_GTYPE(&gtype))
	{
	  GType gtype_dest = g_value_get_gtype(&gtype);
	  if(g_value_type_transformable(src.g_type,gtype_dest))
	    {
	      done = TRUE;
	      g_value_init(&dest,gtype_dest);
	      g_value_transform(&src,&dest);
	      golem_closure_invoke_set_result(invoke,&dest);
	    }
	  else
	    {

	      //TODO: can't transform this to it
	    }
	}
      else
	{
	  //TODO: No holds type
	}
      g_value_unset(&src);
      g_value_unset(&dest);
      g_value_unset(&gtype);
    }
  else
    {
      //TODO: expected 2 params
    }
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

static gboolean
golem_input_func(GolemClosure * self,GolemClosureInvoke * invoke,gpointer data)
{
  GValue type_value = G_VALUE_INIT;
  GValue result_value = G_VALUE_INIT;
  GType type = G_TYPE_STRING;

  if(golem_closure_invoke_next(invoke,&type_value))
    {
      if(G_VALUE_HOLDS_INT(&type_value))
	type = G_TYPE_INT;
      else if(G_VALUE_HOLDS_DOUBLE(&type_value))
	type = G_TYPE_DOUBLE;
      else if(G_VALUE_HOLDS_FLOAT(&type_value))
      	type = G_TYPE_FLOAT;
      g_value_unset(&type_value);
    }
  gchar input[1024];
  fgets(input,1024,stdin);
  g_value_init(&result_value,type);
  switch(type)
  {
    case G_TYPE_STRING:
      g_value_set_string(&result_value,input);
      break;
    case G_TYPE_INT:
      g_value_set_int(&result_value,atoi(input));
      break;
    case G_TYPE_FLOAT:
      g_value_set_float(&result_value,atof(input));
      break;
    case G_TYPE_DOUBLE:
      g_value_set_double(&result_value,atof(input));
      break;
  }
  golem_closure_invoke_set_result(invoke,&result_value);
  g_value_unset(&result_value);
  return TRUE;
}

gint
main(gint argc,gchar ** argv)
{
  GolemContext * context = golem_context_new(NULL);
  gchar * script_file_content = NULL;
  GValue  main_func = G_VALUE_INIT;

  GolemClosure * print_closure = golem_closure_new(golem_print_func,NULL,NULL);
  GolemClosure * input_closure = golem_closure_new(golem_input_func,NULL,NULL);
  GolemClosure * convert_closure = golem_closure_new(golem_convert_func,NULL,NULL);

  golem_context_add_function(context,"print",print_closure);
  golem_context_add_function(context,"input",input_closure);
  golem_context_add_function(context,"convert",convert_closure);

  g_closure_unref(G_CLOSURE(print_closure));
  g_closure_unref(G_CLOSURE(input_closure));
  g_closure_unref(G_CLOSURE(convert_closure));

  g_file_get_contents("golem.glm",&script_file_content,NULL,NULL);
  GolemCompiled * compilation = golem_compiled_new();
  golem_compiled_add_string(compilation,"golem.glm",script_file_content,-1,NULL);
  g_free(script_file_content);
  golem_compiled_run(compilation,context,NULL);

  if(golem_context_get(context,"main",&main_func,NULL))
    {
      GValue main_argc = G_VALUE_INIT,
	     main_argv = G_VALUE_INIT;

      g_value_init(&main_argc,G_TYPE_INT);
      g_value_init(&main_argv,G_TYPE_POINTER);

      g_value_set_int(&main_argc,argc);
      g_value_set_pointer(&main_argv,argv);

      GolemClosureInvoke * invoke = golem_closure_invoke_new();
      golem_closure_invoke_push(invoke,&main_argc);
      golem_closure_invoke_push(invoke,&main_argv);
      golem_closure_invoke(GOLEM_CLOSURE(g_value_get_boxed(&main_func)), invoke);
      g_value_unset(&main_argc);
      g_value_unset(&main_argv);
      golem_closure_invoke_free(invoke);
    }
  g_object_unref(context);
  g_object_unref(compilation);

  return 0;
}

