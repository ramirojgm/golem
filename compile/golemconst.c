/*
	Copyright (C) 2018 Ramiro Jose Garcia Moraga

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


#include "../golem.h"
#include <ctype.h>

GOLEM_DEFINE_STATEMENT(GolemConst,golem_const)

static void
golem_const_init(GolemConst * cnst)
{
  cnst->type = GOLEM_TYPE_CODE_UNDEFINED;
  cnst->data.int64_v = 0;
}

static GolemTypeCode
golem_const_value_type(GolemConst * cnst,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
  return cnst->type;
}


static gboolean
golem_const_compile(GolemConst * cnst,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = TRUE;
  guint32 data_index = golem_vm_body_write_data(body,
					  &(cnst->data),
					  cnst->type,
					  cnst->size);
  golem_vm_body_write_op32(body,GOLEM_OP_DAT,data_index);
  return done;
}

static gboolean
golem_const_parse(GolemConst * cnst,
		GolemParser * parser,
		GolemExpressionLimit limit,
		GError ** error)
{
  gboolean done = TRUE;
  const gchar * const_str = golem_parser_next_word(parser,TRUE);
  if(g_str_has_prefix(const_str,"\"") && g_str_has_suffix(const_str,"\""))
    {
      gchar * uncompressed = g_strndup(const_str + 1,g_utf8_strlen(const_str,G_MAXUINT16) - 2);
      cnst->data.pointer_v = g_strcompress(uncompressed);
      cnst->size = g_utf8_strlen((gchar*)cnst->data.pointer_v,G_MAXUINT16);
      cnst->size = GOLEM_TYPE_CODE_STRING;
      g_free(uncompressed);
    }
  else if(g_str_has_prefix(const_str,"'") && g_str_has_suffix(const_str,"'"))
    {
      gchar * uncompressed = g_strndup(const_str + 1,g_utf8_strlen(const_str,6) - 2);
      gchar * compressed = g_strcompress(uncompressed);
      cnst->data.int8_v = compressed[0];
      cnst->size = sizeof(gint8);
      cnst->size = GOLEM_TYPE_CODE_INT8;
      g_free(compressed);
      g_free(uncompressed);
    }
  else
    {
      gdouble value = g_strtod(const_str,NULL);
      cnst->data.double_v = value;
      cnst->size = sizeof(gdouble);
      cnst->type = GOLEM_TYPE_CODE_DOUBLE;
      done = TRUE;
    }
  return done;
}

static void
golem_const_dispose(GolemConst * cnst)
{
  if(cnst->type == GOLEM_TYPE_CODE_STRING)
    g_free(cnst->data.pointer_v);
}

static gboolean
golem_const_check(GolemParser * parser)
{
  return golem_parser_check_is_const(parser);
}
