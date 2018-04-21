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
#include <stdio.h>
#include <math.h>

GOLEM_DEFINE_STATEMENT(GolemConst,golem_const)

static void
golem_const_init(GolemConst * cnst)
{
  cnst->type = GOLEM_TYPE_CODE_UNDEFINED;
  cnst->data.data->int64_v = 0;
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
  golem_vm_body_write_op32(body,GOLEM_OP_DT,data_index);
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
  guint64 uint64 = 0;

  if(g_str_has_prefix(const_str,"\"") && g_str_has_suffix(const_str,"\""))
    {
      gchar * uncompressed = g_strndup(const_str + 1,g_utf8_strlen(const_str,G_MAXUINT16) - 2);
      cnst->data.data->pointer_v = g_strcompress(uncompressed);
      cnst->size = g_utf8_strlen((gchar*)cnst->data.data->pointer_v,G_MAXUINT16);
      cnst->size = GOLEM_TYPE_CODE_POINTER;
      g_free(uncompressed);
    }
  else if(g_str_has_prefix(const_str,"'") && g_str_has_suffix(const_str,"'"))
    {
      gchar * uncompressed = g_strndup(const_str + 1,g_utf8_strlen(const_str,6) - 2);
      gchar * compressed = g_strcompress(uncompressed);
      cnst->data.data->int8_v = compressed[0];
      cnst->size = sizeof(gint8);
      cnst->size = GOLEM_TYPE_CODE_INT8;
      g_free(compressed);
      g_free(uncompressed);
    }
  else if(g_str_has_prefix(const_str,"0x"))
    {
      sscanf(const_str,"%lx",&uint64);
      if(uint64 <= G_MAXINT8)
	{
	  cnst->data.data->int8_v = uint64;
	  cnst->type = GOLEM_TYPE_CODE_INT8;
	  cnst->size = sizeof(gint8);
	}
      else if(uint64 <= G_MAXUINT8)
	{
	  cnst->data.data->uint8_v = uint64;
	  cnst->type = GOLEM_TYPE_CODE_UINT8;
	  cnst->size = sizeof(guint8);
	}
      else if(uint64 <= G_MAXINT16)
	{
	  cnst->data.data->int16_v = uint64;
	  cnst->type = GOLEM_TYPE_CODE_INT16;
	  cnst->size = sizeof(gint16);
	}
      else if(uint64 <= G_MAXUINT16)
      	{
      	  cnst->data.data->uint16_v = uint64;
      	  cnst->type = GOLEM_TYPE_CODE_UINT16;
      	  cnst->size = sizeof(guint16);
      	}
      else if(uint64 <= G_MAXINT32)
	{
	  cnst->data.data->int32_v = uint64;
	  cnst->type = GOLEM_TYPE_CODE_INT32;
	  cnst->size = sizeof(gint32);
	}
      else if(uint64 <= G_MAXUINT32)
	{
	  cnst->data.data->uint32_v = uint64;
	  cnst->type = GOLEM_TYPE_CODE_UINT32;
	  cnst->size = sizeof(guint32);
	}
      else if(uint64 <= G_MAXINT64)
	{
	  cnst->data.data->int64_v = uint64;
	  cnst->type = GOLEM_TYPE_CODE_INT32;
	  cnst->size = sizeof(gint64);
	}
      else if(uint64 <= G_MAXUINT64)
	{
	  cnst->data.data->uint64_v = uint64;
	  cnst->type = GOLEM_TYPE_CODE_UINT64;
	  cnst->size = sizeof(guint64);
	}
    }
  else
    {
      sscanf(const_str,"%lu",&uint64);
      if(golem_parser_check(parser,"."))
	{
	  const gchar * decimal_str = golem_parser_next_word(parser,TRUE);
	  guint64 decimals = 0;
	  sscanf(decimal_str,"%lu",&decimals);
	  gdouble double_value = decimals ? uint64 +  (decimals / pow(10.0,(int) log10(decimals) + 1)): uint64;
	  if(g_str_has_suffix(decimal_str,"f"))
	    {
	      cnst->data.data->float_v = double_value;
	      cnst->type = GOLEM_TYPE_CODE_FLOAT;
	      cnst->size = sizeof(gfloat);
	    }
	  else
	    {
	      cnst->data.data->double_v = double_value;
	      cnst->type = GOLEM_TYPE_CODE_DOUBLE;
	      cnst->size = sizeof(gdouble);
	    }
	}
      else
	{
	  if(g_str_has_suffix(const_str,"l"))
	    {
	      cnst->data.data->int64_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_INT64;
	      cnst->size = sizeof(gint64);
	    }
	  else if(uint64 <= G_MAXINT8)
	    {
	      cnst->data.data->int8_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_INT8;
	      cnst->size = sizeof(gint8);
	    }
	   else if(uint64 <= G_MAXUINT8)
	    {
	      cnst->data.data->uint8_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_UINT8;
	      cnst->size = sizeof(guint8);
	    }
	   else if(uint64 <= G_MAXINT16)
	    {
	      cnst->data.data->int16_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_INT16;
	      cnst->size = sizeof(gint16);
	    }
	   else if(uint64 <= G_MAXUINT16)
	    {
	      cnst->data.data->uint16_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_UINT16;
	      cnst->size = sizeof(guint16);
	    }
	   else if(uint64 <= G_MAXINT32)
	    {
	      cnst->data.data->int32_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_INT32;
	      cnst->size = sizeof(gint32);
	    }
	   else if(uint64 <= G_MAXUINT32)
	    {
	      cnst->data.data->uint32_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_UINT32;
	      cnst->size = sizeof(guint32);
	    }
	   else if(uint64 <= G_MAXINT64)
	    {
	      cnst->data.data->int64_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_INT32;
	      cnst->size = sizeof(gint64);
	    }
	   else if(uint64 <= G_MAXUINT64)
	    {
	      cnst->data.data->uint64_v = uint64;
	      cnst->type = GOLEM_TYPE_CODE_UINT64;
	      cnst->size = sizeof(guint64);
	    }
	}
      done = TRUE;
    }
  return done;
}

static void
golem_const_dispose(GolemConst * cnst)
{
  if(cnst->type == GOLEM_TYPE_CODE_POINTER)
    g_free(cnst->data.data->pointer_v);
}

static gboolean
golem_const_check(GolemParser * parser)
{
  return golem_parser_check_is_const(parser);
}
