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


gdouble
test_function(gdouble a, gdouble b,GError ** error)
{
  GolemValue ret;
  GolemValue arguments[2];
  static GolemVMBody * body = NULL;

  if(!body)
    {
      GolemParser * p = golem_parser_new("main.glm");
      golem_parser_parse(p,"{ return (10.0 * 10.0)/2.25; }",-1);
      GolemStatement * block = golem_statement_parse(p,error);
      if(block)
	{
	  GolemScopeBuilder * scope_builder = golem_scope_builder_new();
	  body = golem_vm_body_new();
	  golem_scope_builder_enter(scope_builder,body,error);
	/*  golem_scope_builder_argument(scope_builder,GOLEM_TYPE_DOUBLE,"a",error);
	  golem_scope_builder_argument(scope_builder,GOLEM_TYPE_DOUBLE,"b",error);
*/
	  golem_statement_compile(block,
				body,
				scope_builder,
				error);

	  golem_scope_builder_exit(scope_builder,error);

	  g_object_unref(scope_builder);
	  golem_statement_free(block);
	}
      g_object_unref(p);
    }

  GOLEM_FLOAT64(&arguments[0]) = a;
  GOLEM_FLOAT64(&arguments[1]) = b;
  golem_vm_body_run(body,NULL,2,arguments,&ret,NULL);
  return GOLEM_FLOAT64(&ret);
}

gint
main(gint argc,gchar ** argv)
{

  g_print("%g",test_function(10,6,NULL));
  return 0;
}
