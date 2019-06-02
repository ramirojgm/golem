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
golem_type_int_func();

gboolean ld_function(gpointer data,
		     const gchar * link_name,
		     gpointer * symbol,
		     GError ** error)
{
  if (g_strcmp0(link_name,"golem_int_func") == 0)
    {
      *symbol = golem_type_int_func();
      return TRUE;
    }
  return FALSE;
}

G_BEGIN_DECLS

G_MODULE_EXPORT gint
golem_int_func(gint value)
{
  return value * 100;
}


G_END_DECLS

void
test_exp(const gchar * test,gdouble pi,GError ** error)
{
  GolemValue arguments[2] = {};
  GolemValue ret;

  GolemVMBody * body = NULL;
  GolemParser * p = golem_parser_new("test");
  gchar * test_script = g_strdup_printf("return %s;",test);
  golem_parser_parse(p,test_script,-1);
  GolemStatement * block = golem_statement_parse(p,error);

  GolemMetadata * metadata = NULL;

  if(block)
    {
      GolemScopeBuilder * scope_builder = golem_scope_builder_new();

      body = golem_vm_body_new();
      golem_scope_builder_enter(scope_builder,body,error);

      golem_scope_builder_argument(scope_builder,
				   GOLEM_TYPE_DOUBLE,
				   "pi",
				   error);

      golem_scope_builder_argument(scope_builder,
      				   GOLEM_TYPE_INT,
      				   "a",
      				   error);

      metadata = golem_statement_value_type(((GolemReturn*)block)->m_expression,
      				 scope_builder,
      				 NULL);

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

  if(body)
    {
      GOLEM_FLOAT64(&arguments[0]) = pi;
      GOLEM_INT32(&arguments[1]) = 42;

      golem_vm_body_link_dynamic(body,ld_function,NULL,NULL);
      golem_vm_body_run(body,NULL,2,arguments,&ret,NULL);

      if (GOLEM_IS_PRIMITIVE(metadata))
	{
	  GolemPrimitiveType type =
	      golem_primitive_get_primitive_type(GOLEM_PRIMITIVE(metadata));
	  switch(type)
	  {
	    case GOLEM_PRIMITIVE_TYPE_BOOL:
	      g_print("< %s\n",GOLEM_INT32(&ret) ? "true": "false" );
	      break;
	    case GOLEM_PRIMITIVE_TYPE_CHAR:
	    case GOLEM_PRIMITIVE_TYPE_UCHAR:
	      g_print("< '%c'\n",GOLEM_CHAR(&ret));
	      break;
	    case GOLEM_PRIMITIVE_TYPE_FLOAT32:
	      g_print("< %gf\n",GOLEM_FLOAT32(&ret));
	      break;
	    case GOLEM_PRIMITIVE_TYPE_FLOAT64:
	      g_print("< %g\n",GOLEM_FLOAT64(&ret));
	      break;
	    case GOLEM_PRIMITIVE_TYPE_POINTER:
	      g_print("< %p\n",GOLEM_POINTER(&ret));
	      break;
	    case GOLEM_PRIMITIVE_TYPE_STRING:
	      g_print("< \"%s\"\n",GOLEM_STRING(&ret));
	      break;
	    default:
	      g_print("< %d\n",GOLEM_INT32(&ret));
	   }
	}
    }
}

gint
main(gint argc,gchar ** argv)
{
  gchar buff[128] = {0,};
  GError * error = NULL;

  g_print("Write 'quit' to finish\n");

  for(;;)
    {
      g_print(">");
      scanf("%[^\n]",buff);
      getchar();
      fflush(stdin);
      if (g_strcmp0(buff,"quit") == 0)
	break;
      test_exp(buff,M_PI, &error);
      if (error)
	{
	  g_print("Error: %s\n",error->message);
	  g_clear_error(&error);
	}
    }
  return 0;
}
