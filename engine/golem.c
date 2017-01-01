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
#include <ctype.h>

GQuark
golem_error_quark(void)
{
  return g_quark_from_static_string("golem-error-quark");
}

void
golem_throw(GError ** error,enum GolemError code,const gchar * format,...)
{
  va_list va;
  va_start(va,format);
  GError * err = g_error_new_valist(GOLEM_ERROR,code,format,va);
  va_end(va);
  golem_throw_error(error,err);
}

void
golem_throw_error(GError ** error,GError * err)
{
  if(error)
    {
      *error = err;
    }
  else
    {
      g_printerr("%s **: %s\n",g_quark_to_string(err->domain), err->message);
      g_error_free(err);
      raise(SIGTRAP);
    }
}

GType
golem_resolve_type_name(const gchar * name)
{
  if(g_strcmp0(name,"void") == 0)
    return G_TYPE_NONE;
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
  else if(g_strcmp0(name,"func") == 0)
      return GOLEM_TYPE_FUNC;
  else if(g_strcmp0(name,"object") == 0)
      return G_TYPE_OBJECT;
  else
      return g_type_from_name(name);
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
