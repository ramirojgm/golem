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

#include "golem.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <memory.h>

/*void _golem_struct_builder_expand(GolemStructBuilder * struct_builder,gsize size)
{

  if((struct_builder->allowed - struct_builder->size) < size)
    {
      struct_builder->offset = struct_builder->allowed;
      struct_builder->size = struct_builder->allowed + size;
      struct_builder->allowed += (size * 2);
      struct_builder->mem = g_realloc(struct_builder->mem,struct_builder->allowed);
      memset(struct_builder->mem,0,struct_builder->allowed - struct_builder->offset);
    }
  else
    {
      struct_builder->offset = struct_builder->size;
      struct_builder->size += size;
    }

  //g_print("{ mem: %p, offset: %d, size: %d,allowed: %d, new_size: %d }\n",struct_builder->mem,struct_builder->offset,struct_builder->size,struct_builder->allowed,size);
}*/

volatile gsize 		_golem_invoke_vfunc_size = 0;
volatile goffset 	_golem_invoke_vfunc_vfunc_offset = 0;
volatile goffset 	_golem_invoke_vfunc_vdata_offset = 0;
volatile gint		_golem_invoke_vfunc_vfd = 0;

gint64
_golem_invoke_vfunc_template(gpointer instance,...)
{
  gint64 vfunc_address = 0x00FF00FF00000000;
  gint64 vdata_address = 0xFF00FF0000000000;
  //virtual function
  GolemLLMVFunc vfunc;
  gpointer	vdata;
  struct _GolemLLMInvoke invoke;
  memcpy(&vfunc,&vfunc_address,sizeof(gpointer));
  memcpy(&vdata,&vdata_address,sizeof(gpointer));
  va_list ap;
  va_start(ap,instance);
  invoke.va_args = &ap;
  vfunc(instance,&invoke,vdata);
  va_end(ap);
  return invoke.result.int_64;
}

static void
__attribute__((constructor)) _golem_invoke_vfunc_init()
{
  gpointer vtemplate = _golem_invoke_vfunc_template;
  gsize vfunc_size = 0;
  guint64 vfunc_data = GUINT64_TO_LE(0x00FF00FF00000000);
  guint64 vdata_data = GUINT64_TO_LE(0xFF00FF0000000000);
  while(TRUE)
    {
      if(*((guint8*)(vtemplate + vfunc_size)) == 0xC3)
	{
	  _golem_invoke_vfunc_size = vfunc_size + 1;
	  break;
	}
      else if(*((guint64*)(vtemplate + vfunc_size)) == vfunc_data)
	{
	  _golem_invoke_vfunc_vfunc_offset = vfunc_size;
	  vfunc_size += 7;
	}
      else if(*((guint64*)(vtemplate + vfunc_size)) == vdata_data)
	{
	  _golem_invoke_vfunc_vdata_offset = vfunc_size;
	  vfunc_size += 7;
	}
      vfunc_size += 1;
    }
  _golem_invoke_vfunc_vfd = open(GOLEM_VFUNC_TEMPLATE,O_RDWR);
}

gpointer
golem_llm_new_vfunction(GolemLLMVFunc func,gpointer data)
{
  gpointer v_template = _golem_invoke_vfunc_template;
  gpointer vfunc = mmap(NULL,_golem_invoke_vfunc_size,PROT_WRITE|PROT_READ|PROT_EXEC,MAP_PRIVATE, _golem_invoke_vfunc_vfd, 0);
  guint64 vfunc_data = (guint64)func;
  guint64 vdata_data = (guint64)data;
  memcpy(vfunc,v_template,_golem_invoke_vfunc_size);
  memcpy(vfunc + _golem_invoke_vfunc_vfunc_offset,&vfunc_data ,sizeof(guint64));
  memcpy(vfunc + _golem_invoke_vfunc_vdata_offset,&vdata_data ,sizeof(guint64));
  return vfunc;
}

void
golem_llm_dispose_vfunction(gpointer vfunc)
{
  munmap(vfunc,_golem_invoke_vfunc_size);
}

void
golem_llm_invoke_rewind(GolemLLMInvoke * invoke)
{}

guint8
golem_llm_invoke_get_guint8(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),int);
}

guint
golem_llm_invoke_get_guint(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),guint);
}

guint64
golem_llm_invoke_get_guint64(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),guint64);
}

gulong
golem_llm_invoke_get_gulong(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),gulong);
}

gint8
golem_llm_invoke_get_gint8(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),int);
}

gint
golem_llm_invoke_get_gint(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),gint);
}

gint64		golem_llm_invoke_get_gint64(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),gint64);
}

glong		golem_llm_invoke_get_glong(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),glong);
}

gfloat		golem_llm_invoke_get_gfloat(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),gdouble);
}
gdouble		golem_llm_invoke_get_gdouble(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),gdouble);
}

gpointer	golem_llm_invoke_get_gpointer(GolemLLMInvoke * invoke)
{
	return va_arg(*(invoke->va_args),gpointer);
}

const va_list *
golem_llm_invoke_get_va_list(GolemLLMInvoke * invoke)
{
	return invoke->va_args;
}

void
golem_llm_invoke_set_result(GolemLLMInvoke * invoke,gresult * result)
{
	invoke->result.int_64 = result->int_64;
}

