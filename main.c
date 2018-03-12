/*
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
  golem_parser_parse(p,"{ int x; int x; }",-1);
  GolemStatement * block = golem_statement_parse(p,&error);
  if(block)
    {
      GolemVMData ret = {0};
      GolemScopeBuilder * scope_builder = golem_scope_builder_new();
      GolemVMBody * body = golem_vm_body_new();
      if(golem_statement_compile(block,
				  body,
				  scope_builder,
				  &error))
	{
	  golem_vm_body_run(body,NULL,&ret,&error);
	  g_print("%d",ret.int32_v);
	}
      else
	{
	  g_printerr("%s",error->message);
	  g_error_free(error);
	}
    }
  else
    {
      g_printerr("%s",error->message);
      g_error_free(error);
    }


 /* GolemVMData zero,result,inc,stop,one;
  zero.double_v = 0;
  one.int32_v = 1;
  stop.double_v = 7000000;
  inc.double_v = 0.27;
  result.double_v = 0;

  #define DATA_ZERO 0
  #define DATA_STOP 1
  #define DATA_INC 2
  #define DATA_ONE 3

  #define VAR_SUM 0, 0, sizeof(gdouble)
  #define VAR_COUNT 0, sizeof(gdouble), sizeof(gint32)

  golem_vm_body_write_data(body,&zero,0,0);
  golem_vm_body_write_data(body,&stop,0,0);
  golem_vm_body_write_data(body,&inc,0,0);
  golem_vm_body_write_data(body,&one,0,0);


  golem_vm_body_write_op32(body,GOLEM_OP_SE,sizeof(gdouble) + sizeof(gint32));//0
  golem_vm_body_write_op16(body,GOLEM_OP_DAT,DATA_ZERO); //1
  golem_vm_body_write_ops(body,GOLEM_OP_PSH,VAR_SUM); //2
  golem_vm_body_write_op16(body,GOLEM_OP_DAT,DATA_ONE); //3
  golem_vm_body_write_ops(body,GOLEM_OP_PSH,VAR_COUNT); //4

  golem_vm_body_write_ops(body,GOLEM_OP_POP,VAR_SUM); //5 BEGIN LOOP
  golem_vm_body_write_op32(body,GOLEM_OP_DAT,DATA_INC); //6
  golem_vm_body_write_opt(body,GOLEM_OP_ADD,GOLEM_TYPE_CODE_DOUBLE);//7
  golem_vm_body_write_ops(body,GOLEM_OP_PSH,VAR_SUM); //8
  golem_vm_body_write_ops(body,GOLEM_OP_POP,VAR_COUNT); // 9
  golem_vm_body_write_opt(body,GOLEM_OP_DAT,DATA_ONE); //10
  golem_vm_body_write_opt(body,GOLEM_OP_ADD,GOLEM_TYPE_CODE_INT32);//11
  golem_vm_body_write_ops(body,GOLEM_OP_PSH,VAR_COUNT); //12
  golem_vm_body_write_ops(body,GOLEM_OP_POP,VAR_SUM); //13 BEGIN LOOP
  golem_vm_body_write_op32(body,GOLEM_OP_DAT,DATA_STOP); //14
  golem_vm_body_write_opt(body,GOLEM_OP_LT,GOLEM_TYPE_CODE_DOUBLE);//15
  golem_vm_body_write_op32(body,GOLEM_OP_CND,5);//16 END LOOP
  golem_vm_body_write_ops(body,GOLEM_OP_POP,VAR_COUNT); //17
  golem_vm_body_write_op32(body,GOLEM_OP_SX,0);//18
  golem_vm_body_write_op(body,GOLEM_OP_RET);//19

  golem_vm_body_run(body,NULL,&result,NULL);
  g_print("Result: %d\n",result.int32_v);

  gdouble sum = 0;
  gint32 count;
  for(count = 1;sum < 7000000.0; count ++)
    {
      sum += 0.27;
    }
  g_print("Result: %d\n",count);*/

  return 0;
}
