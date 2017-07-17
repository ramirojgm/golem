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

gint64
_golem_invoke_vfunc_template(gpointer instance,...)
{
  gint64 vfunc_address = 0x00FF00FF00000000;
  gint64 vdata_address = 0xFF00FF0000000000;
  //virtual function
  GolemLLMVFunc vfunc;
  gpointer	vdata;

  memcpy(&vfunc,&vfunc_address,sizeof(gpointer));
  memcpy(&vdata,&vdata_address,sizeof(gpointer));
  va_list ap;
  va_start(ap,instance);
  struct _GolemLLMInvoke invoke;
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
	  _golem_invoke_vfunc_size = vfunc_size + 10;
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
}

gpointer
golem_llm_new_vfunction(GolemLLMVFunc func,gpointer data)
{
  gpointer v_template = _golem_invoke_vfunc_template;
  gpointer vfunc = mmap(NULL,_golem_invoke_vfunc_size,PROT_WRITE|PROT_READ|PROT_EXEC,MAP_PRIVATE, 0, 0);
  guint64 vfunc_data = (guint64)func;
  guint64 vdata_data = (guint64)data;
  memset(vfunc,0xC3,_golem_invoke_vfunc_size-10);
  /*memcpy(vfunc,v_template,_golem_invoke_vfunc_size-10);
  memcpy(vfunc + _golem_invoke_vfunc_vfunc_offset,&vfunc_data ,sizeof(guint64));
  memcpy(vfunc + _golem_invoke_vfunc_vdata_offset,&vdata_data ,sizeof(guint64));*/
  return vfunc;
}

void
golem_llm_dispose_vfunction(gpointer vfunc)
{

}

/*
gsize _golem_vm_template_sizeof(gpointer func){
  gsize result = 0;
  for(guint8 * bytes = (guint8*)func;*bytes != 0xC3;bytes++)
    result ++;
  return result + 1;
}

guint8 _golem_guint8_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint8 _golem_guint8_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint8 _golem_guint8_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

guint16 _golem_guint16_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint16 _golem_guint16_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint16 _golem_guint16_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

guint32 _golem_guint32_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint32 _golem_guint32_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint32 _golem_guint32_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

guint64 _golem_guint64_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint64 _golem_guint64_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint64 _golem_guint64_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint8 _golem_gint8_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint8 _golem_gint8_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint8 _golem_gint8_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint16 _golem_gint16_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint16 _golem_gint16_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint16 _golem_gint16_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint32 _golem_gint32_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint32 _golem_gint32_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint32 _golem_gint32_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint64 _golem_gint64_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint64 _golem_gint64_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint64 _golem_gint64_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gfloat _golem_gfloat_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gfloat _golem_gfloat_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gfloat _golem_gfloat_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gdouble _golem_gdouble_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gdouble _golem_gdouble_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gdouble _golem_gdouble_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gpointer _golem_gpointer_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gpointer _golem_gpointer_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gpointer _golem_gpointer_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gpointer _golem_guint8_pointer = _golem_guint8_invoke;
gpointer _golem_guint16_pointer = _golem_guint16_invoke;
gpointer _golem_guint32_pointer = _golem_guint16_invoke;

guint8 _golem_guint8_template(GolemArgs args)
{
  gpointer metadata = NULL;
  guint8(*internal)(gpointer,GolemArgs) = _golem_guint8_pointer;
  return internal(metadata,args);
}

guint16 _golem_guint16_template(GolemArgs args)
{
  gpointer metadata = NULL;
  guint16(*internal)(gpointer,GolemArgs) = _golem_guint16_pointer;
  return internal(metadata,args);
}

guint32 _golem_guint32_template(GolemArgs args)
{
  gpointer metadata = NULL;
  guint32(*internal)(gpointer,GolemArgs) = _golem_guint32_pointer;
  return internal(metadata,args);
}

gpointer golem_v_func(GType return_type,gpointer metadata)
{
  gpointer v_template;
  gsize v_size;

  guint8 * v_func = NULL;
  switch(return_type)
  {
    case G_TYPE_CHAR:
      v_template = _golem_guint8_template;
      v_size = _golem_vm_template_sizeof(_golem_guint8_template);
    break;
    case G_TYPE_INT:
      v_template = _golem_guint32_template;
      v_size = _golem_vm_template_sizeof(_golem_guint32_template);
    break;
    default:
      v_func = NULL;
  }

#ifndef __WIN32__
  v_func = mmap( NULL,v_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE,0,0);
  memcpy(v_func,v_template,v_size);
  memcpy(v_func + 0xC,&metadata,sizeof(gpointer));
  return v_func;
#else
  v_func = VirtualAlloc();
#endif
}

*/
