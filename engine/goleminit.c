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
#include "gmodule.h"
#include <ctype.h>
#include <string.h>


const gchar *
golem_type_get_prefix(const gchar * name)
{
  static gchar prefix[256] = {0,};
  guint offset = 0;
  for(const gchar * iter = name;*iter;iter++)
    {
      if((isupper(*iter)) && (offset != 0))
	{
	  prefix[offset] = '_';
	  offset++;
	}
      prefix[offset] = tolower(*iter);
      offset ++;
    }
  prefix[offset] = 0;
  return prefix;
}

static gboolean
golem_gobject_ref(GolemClosure * closure,
			GolemClosureInvoke * invoke,
			gpointer data)
{
  GValue return_value = G_VALUE_INIT;
  g_value_init(&return_value,G_TYPE_FROM_INSTANCE(data));
  g_value_set_object(&return_value,g_object_ref(data));
  golem_closure_invoke_set_result(invoke,&return_value);
  return TRUE;
}

static gboolean
golem_gobject_unref(GolemClosure * closure,
			GolemClosureInvoke * invoke,
			gpointer data)
{
  GValue return_value = G_VALUE_INIT;
  g_value_init(&return_value,G_TYPE_FROM_INSTANCE(data));
  if(G_OBJECT(data)->ref_count > 1)
    g_value_set_object(&return_value,g_object_ref(data));
  else
    g_value_set_object(&return_value,NULL);
  g_object_unref(data);
  golem_closure_invoke_set_result(invoke,&return_value);
  return TRUE;
}

static gboolean
golem_gobject_signal_on(GolemClosure * closure,
			GolemClosureInvoke * invoke,
			gpointer data)
{
  GValue return_value = G_VALUE_INIT;
  g_value_init(&return_value,G_TYPE_UINT64);
  g_value_set_uint64(&return_value,0);

  if(golem_closure_invoke_get_length(invoke) == 2)
    {
      const gchar * details = golem_closure_invoke_get_string(invoke,0);
      GClosure * closure = G_CLOSURE(golem_closure_invoke_get_boxed(invoke,1));
      guint64 signal_handler =  g_signal_connect_closure(
	      data,
	      details,
	      closure,
	      FALSE);

      g_value_set_uint64(&return_value,signal_handler);
    }
  golem_closure_invoke_set_result(invoke,&return_value);
  return TRUE;
}

static void
_g_value_pointer_to_object(const GValue * src_value,GValue * dest_value)
{
  g_value_set_object(dest_value,g_value_get_pointer(src_value));
}

static void
_g_value_object_to_pointer(const GValue * src_value,GValue * dest_value)
{
  g_value_set_pointer(dest_value,g_value_get_object(src_value));
}



void
__attribute__((constructor)) _golem_object_type_init() 
{
  //convert
  g_value_register_transform_func(G_TYPE_POINTER,G_TYPE_OBJECT,_g_value_pointer_to_object);
  g_value_register_transform_func(G_TYPE_OBJECT,G_TYPE_POINTER,_g_value_object_to_pointer);

  //object
  GolemTypeInfo * type_info = golem_type_info_from_gtype(G_TYPE_OBJECT);
  golem_type_info_add_function(type_info,golem_function_closured_new("on",golem_gobject_signal_on));
  golem_type_info_add_function(type_info,golem_function_closured_new("ref",golem_gobject_ref));
  golem_type_info_add_function(type_info,golem_function_closured_new("unref",golem_gobject_unref));

}


void
g_value_free(GValue * value)
{
  g_value_unset(value);
  g_free(value);
}
