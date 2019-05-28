/*
*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "golem.h"
#include "stdio.h"
#include "math.h"

GolemMetadata *
golem_type_int_to_string();

gboolean ld_function(gpointer data,
		     const gchar * link_name,
		     gpointer * symbol,
		     GError ** error)
{
  if (g_strcmp0(link_name,"golem_type_int_to_string") == 0)
    {
      *symbol = golem_type_int_to_string();
      g_print("Linked");
      return TRUE;
    }
  return FALSE;
}

GolemValue
test_exp(const gchar * test,gdouble pi,GError ** error)
{
  GolemValue arguments[1] = {};
  GolemValue ret;

  GolemVMBody * body = NULL;
  GolemParser * p = golem_parser_new("test");
  gchar * test_script = g_strdup_printf("{ return %s; }",test);
  golem_parser_parse(p,test_script,-1);
  GolemStatement * block = golem_statement_parse(p,error);
  if(block)
    {
      GolemScopeBuilder * scope_builder = golem_scope_builder_new();

      body = golem_vm_body_new();
      golem_scope_builder_enter(scope_builder,body,error);

      golem_scope_builder_argument(scope_builder,
				   GOLEM_TYPE_DOUBLE,
				   "pi",
				   error);
      golem_statement_compile(block,
			    body,
			    scope_builder,
			    error);

      golem_scope_builder_exit(scope_builder,error);

      g_object_unref(scope_builder);
      golem_statement_free(block);
    }
  g_object_unref(p);
  g_free(test_script);

  GOLEM_FLOAT64(&arguments[0]) = pi;
  golem_vm_body_link_dynamic(body,ld_function,NULL,NULL);
  golem_vm_body_run(body,NULL,1,arguments,&ret,NULL);
  return ret;
}

gint
main(gint argc,gchar ** argv)
{
  gchar buff[128] = {0,};
  GError * error = NULL;
  GolemValue ret = 0;

  g_print("Write 'quit' to finish\n");

  for(;;)
    {
      g_print(">");
      scanf("%[^\n]",buff);
      getchar();
      fflush(stdin);
      if (g_strcmp0(buff,"quit") == 0)
	break;
      ret = test_exp(buff,M_PI, &error);
      if (error)
	{
	  g_print("Error: %s\n",error->message);
	  g_clear_error(&error);
	}
      else
	{
	  g_print("I32: %d\nF64: %g\n",
		  GOLEM_INT32(&ret),
		  GOLEM_FLOAT64(&ret));
	}
    }
  return 0;
}
