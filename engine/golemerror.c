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
