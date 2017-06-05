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
#include <stdlib.h>
#include <stdio.h>

GQuark
golem_error_quark(void)
{
  return g_quark_from_static_string("golem-error-quark");
}

void
golem_error_default_handle(GError * error)
{
  if(error)
    {
      g_printerr("%s **: %s\n",g_quark_to_string(error->domain), error->message);
      g_error_free(error);
      raise(SIGTRAP);
    }
}

void
golem_parser_error(GError ** error,GolemParser * parser,const gchar * format,...)
{
  va_list va;
  va_start(va,format);
  gchar * message = g_strdup_vprintf(format,va);
  va_end(va);
  GError * err = g_error_new(GOLEM_ERROR,GOLEM_SYNTAXIS_ERROR,"%s (%d): %s",golem_parser_get_source_name(parser),golem_parser_get_line(parser),message);
  g_free(message);
  golem_propage_error(error,err);
}

void
golem_runtime_error(GError ** error,enum GolemError code,const gchar * format,...)
{
  va_list va;
  va_start(va,format);
  GError * err = g_error_new_valist(GOLEM_ERROR,code,format,va);
  va_end(va);
  golem_propage_error(error,err);
}

void
golem_propage_error(GError ** error,GError * new_error)
{
  if(error)
      *error = new_error;
  else
    golem_error_default_handle(new_error);
}
