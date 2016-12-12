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
#include <errno.h>
#include <memory.h>


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


  v_func = mmap( NULL,v_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE,0,0);
  memcpy(v_func,v_template,v_size);
  memcpy(v_func + 0xC,&metadata,sizeof(gpointer));
  return v_func;
}

