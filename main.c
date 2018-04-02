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


gint
main(gint argc,gchar ** argv)
{
  GolemParser * p = golem_parser_new("main.glm");
  GError * error = NULL;
  golem_parser_parse(p,"{ double age = 20.0 + 0.20; age = age +(a * b);  return b; }",-1);
  GolemStatement * block = golem_statement_parse(p,&error);
  if(block)
    {
      GolemVMData ret = {0};

      GolemScopeBuilder * scope_builder = golem_scope_builder_new();
      GolemVMBody * body = golem_vm_body_new();
      golem_scope_builder_enter(scope_builder,body,&error);
      golem_scope_builder_argument(scope_builder,GOLEM_TYPE_CODE_DOUBLE,"a",&error);
      golem_scope_builder_argument(scope_builder,GOLEM_TYPE_CODE_DOUBLE,"b",&error);


      if(golem_statement_compile(block,
				  body,
				  scope_builder,
				  &error))
	{
	  GolemVMData arguments[2];
	  arguments[0].double_v = 2;
	  arguments[1].double_v = 5;
	  GolemVMInvoke * invoke = golem_vm_invoke_new(2,arguments,NULL);
	  golem_vm_body_run(body,NULL,invoke,&ret,&error);
	  golem_vm_invoke_free(invoke);
	  g_print("%g",ret.double_v);
	}
      else
	{
	  g_printerr("%s",error->message);
	  g_error_free(error);
	}

      golem_scope_builder_exit(scope_builder,&error);
    }
  else
    {
      g_printerr("%s",error->message);
      g_error_free(error);
    }

  return 0;
}
