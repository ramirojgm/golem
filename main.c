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
  GolemVMData ret;
  GolemVMData arguments[2];
  static GolemVMBody * body = NULL;

  if(!body)
    {
      GolemParser * p = golem_parser_new("main.glm");
      golem_parser_parse(p,"{ return a + a * b; }",-1);
      GolemStatement * block = golem_statement_parse(p,error);
      if(block)
	{
	  GolemScopeBuilder * scope_builder = golem_scope_builder_new();
	  body = golem_vm_body_new();
	  golem_scope_builder_enter(scope_builder,body,error);
	  golem_scope_builder_argument(scope_builder,GOLEM_TYPE_CODE_DOUBLE,"a",error);
	  golem_scope_builder_argument(scope_builder,GOLEM_TYPE_CODE_DOUBLE,"b",error);

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

  arguments[0].data->double_v = a;
  arguments[1].data->double_v = b;
  golem_vm_body_run(body,NULL,2,arguments,&ret,NULL);
  return ret.data->double_v;
}

/* using gir.gtk;
 *
 * module Default
 * {
 * class MyWindow: GtkApplicationWindow
 * {
 * 	init {}
 * }
 *
 * void	main(int argc,pointer argv)
 * {
 * 	struct iter;
 * 	iter = GtkTreeIter.new();
 *
 * 	iter.free();
 *
 * 	object application = new GtkApplication
 * 	{
 * 		"application-id": "org.gnome.desktop.golemtestapp"
 * 	};
 *
 * 	application.on("activate",void:() {
 * 		object window = new GtkApplicationWindow {
 * 			"title": "MyWindow",
 * 			"children": new @GtkBox {
 *
 * 			}
 * 		};
 * 		application.add_window(window);
 * 		window.show();
 * 	});
 *
 * 	application.run(argc,argv);
 * }
 *
 *}
 */

gint
main(gint argc,gchar ** argv)
{
 /* void (*main_func)(int argc,char ** argv);

  GolemTypeModule * main_module = golem_type_module_new();
  golem_type_module_load_from_file(main_module,"main.glb",NULL);

  golem_type_module_get_symbol(main_module,"main",&main_func,NULL,NULL);
  golem_type_module_get_symbol(main_module,"MyWindow::init",&main_func,NULL,NULL);
  main_func(argc,argv);*/

  GError * error = NULL;
  gdouble ret = test_function(10,25,&error);
  g_print("%g",ret);
  return 0;
}
