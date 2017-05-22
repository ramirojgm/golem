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

GType
golem_resolve_type_name(GolemContext * context,const gchar * name)
{
  if(g_strcmp0(name,"void") == 0)
    return G_TYPE_NONE;
  else if(g_strcmp0(name,"var") == 0)
    return G_TYPE_VALUE;
  else if(g_strcmp0(name,"bool") == 0)
      return G_TYPE_BOOLEAN;
  else if(g_strcmp0(name,"string") == 0)
    return G_TYPE_STRING;
  else if(g_strcmp0(name,"byte") == 0 || g_strcmp0(name,"char") == 0)
    return G_TYPE_CHAR;
  else if(g_strcmp0(name,"int") == 0)
    return G_TYPE_INT;
  else if(g_strcmp0(name,"long") == 0)
    return G_TYPE_LONG;
  else if(g_strcmp0(name,"ubyte") == 0 || g_strcmp0(name,"uchar") == 0)
      return G_TYPE_UCHAR;
  else if(g_strcmp0(name,"uint") == 0)
    return G_TYPE_UINT;
  else if(g_strcmp0(name,"ulong") == 0)
    return G_TYPE_ULONG;
  else if(g_strcmp0(name,"pointer") == 0)
    return G_TYPE_POINTER;
  else if(g_strcmp0(name,"float") == 0)
      return G_TYPE_FLOAT;
  else if(g_strcmp0(name,"double") == 0)
      return G_TYPE_DOUBLE;
  else if(g_strcmp0(name,"function") == 0)
      return GOLEM_TYPE_CLOSURE;
  else if(g_strcmp0(name,"object") == 0)
      return G_TYPE_OBJECT;
  else if(g_strcmp0(name,"debug_object") == 0)
      return GOLEM_TYPE_DEBUG_OBJECT;
  else
    {
#ifdef GOLEM_TYPE_IMPORT
      GType type = g_type_from_name(name);
      static gchar type_named[256] = {0,};
      memset(type_named,0,256);
      if(type == 0)
	{
	  GModule * module = g_module_open(NULL,0);
	  guint type_named_index = 0;
	  for(const gchar * iter = name;*iter;iter ++)
	    {
	      if(isupper(*iter) && (iter != name))
		{
		  type_named[type_named_index] = '_';
		  type_named_index++;

		}
	      type_named[type_named_index] = tolower(*iter);
	      type_named_index++;
	    }
	  strcat(type_named,"_get_type");
	  GType (*get_type)() = 0;
	  g_module_symbol(module,type_named,(gpointer*)&get_type);
	  if(get_type)
	    type = get_type();
	  else
	    type = 0;
	  g_module_close(module);
	}
      return type;
#else
      GType type = 0;
      GValue type_value = G_VALUE_INIT;
      GError * error = NULL;
      if(golem_context_get(context,name,&type_value,&error))
	{
	  if(G_VALUE_TYPE(&type_value) == G_TYPE_GTYPE)
	    type = g_value_get_gtype(&type_value);
	}
      g_value_unset(&type_value);
      if(error)
	g_error_free(error);
      return type;
#endif
    }
}

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

gboolean
golem_member_get(GValue * value,const gchar * member_name,GValue * dest,GError ** error)
{
  gboolean done = FALSE;
  GType value_type = G_VALUE_TYPE(value);
  if(g_type_is_a(value_type,G_TYPE_OBJECT))
    {
      GObject * self = g_value_get_object(value);
      GObjectClass * klass = G_OBJECT_CLASS(g_type_class_ref(value_type));
      GParamSpec * property = g_object_class_find_property(klass,member_name);

      //TODO:MISING CLASS FUNCTION SEARCH
      if(g_strcmp0(member_name,"on") == 0)
	{
	  done = TRUE;
	  GolemClosure * closure = golem_closure_new(golem_gobject_signal_on,g_object_unref,g_object_ref(self));
	  g_value_init(dest,GOLEM_TYPE_CLOSURE);
	  g_value_set_boxed(dest,closure);
	}
      else if(property)
	{

	  done = TRUE;
	  g_value_init(dest,property->value_type);
	  g_object_get_property(self,property->name,dest);
	}
      else
	{
	  GValue * data_value = (GValue*)(g_object_get_data(self,member_name));
	  if(data_value)
	    {
	      done = TRUE;
	      g_value_init(dest,G_VALUE_TYPE(data_value));
	      g_value_copy(data_value,dest);
	    }
	  else
	    {
	      //TODO: throw error
	      g_print("NOT FOUND %s\n",member_name);
	    }
	}
      g_type_class_unref(klass);
    }
  else if(value_type == G_TYPE_GTYPE)
    {
      if(g_strcmp0(member_name,"name") == 0)
	{

	}
      else
	{
	  //TODO: throw error

	}
    }
  else
    {
      //TODO: throw error

    }
  return done;
}

gboolean
golem_member_set(GValue * value,const gchar * item,GValue * src,GError ** error)
{

}

void
g_value_free(GValue * value)
{
  g_value_unset(value);
  g_free(value);
}
