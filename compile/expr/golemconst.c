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


#include "../../golem.h"

#include <ctype.h>
#include <stdio.h>
#include <math.h>

GOLEM_DEFINE_STATEMENT(GolemConst,golem_const)

static void
golem_const_init(GolemConst * cnst)
{
  cnst->primitive = NULL;
  cnst->data = 0;
}

static GolemMetadata *
golem_const_value_type(GolemConst * cnst,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
  return GOLEM_METADATA(cnst->primitive);
}


static gboolean
golem_const_compile(GolemConst * cnst,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = TRUE;
  guint32 data_index = 0;
  if (GOLEM_METADATA(cnst->primitive) == GOLEM_TYPE_STRING)
    {
      data_index = golem_vm_body_write_string(body,
					      GOLEM_STRING(&(cnst->data)),
					      cnst->size);
    }
  else if (GOLEM_METADATA(cnst->primitive) == GOLEM_TYPE_POINTER)
    {
      data_index = golem_vm_body_write_data(body,
					    GOLEM_POINTER(&(cnst->data)),
					    cnst->size);
    }
  else
    {
      data_index = golem_vm_body_write_value(body, &(cnst->data));
    }
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
  uintmax_t uint128 = 0;

  if(g_str_has_prefix(const_str,"\"") && g_str_has_suffix(const_str,"\""))
    {
      gchar * uncompressed = g_strndup(const_str + 1,g_utf8_strlen(const_str,G_MAXUINT16) - 2);
      GOLEM_STRING(&(cnst->data)) = g_strcompress(uncompressed);
      cnst->size = g_utf8_strlen(GOLEM_STRING(&(cnst->data)),G_MAXUINT16);
      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_STRING);
      g_free(uncompressed);
    }
  else if(g_str_has_prefix(const_str,"'") && g_str_has_suffix(const_str,"'"))
    {
      gchar * uncompressed = g_strndup(const_str + 1,g_utf8_strlen(const_str,6) - 2);
      gchar * compressed = g_strcompress(uncompressed);
      GOLEM_CHAR(&(cnst->data)) = compressed[0];
      cnst->size = 0;
      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_CHAR);
      g_free(compressed);
      g_free(uncompressed);
    }
  else if(g_str_has_prefix(const_str,"0x"))
    {
      sscanf(const_str + 2,"%jx",&uint128);
      cnst->size = 0;
      if(uint128 <= G_MAXINT8)
	{
	  GOLEM_INT8(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_SBYTE);
	}
      else if(uint128 <= G_MAXUINT8)
	{
	  GOLEM_UINT8(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_BYTE);
	}
      else if(uint128 <= G_MAXINT16)
	{
	  GOLEM_INT16(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_SHORT);
	}
      else if(uint128 <= G_MAXUINT16)
      	{
	  GOLEM_UINT16(&(cnst->data)) = uint128;
      	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_USHORT);
      	}
      else if(uint128 <= G_MAXINT32)
	{
	  GOLEM_INT32(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_INT);
	}
      else if(uint128 <= G_MAXUINT32)
	{
	  GOLEM_UINT32(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_UINT);
	}
      else if(uint128 <= G_MAXINT64)
	{
	  GOLEM_INT64(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_LONG);
	}
      else if(uint128 <= G_MAXUINT64)
	{
	  GOLEM_UINT64(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_ULONG);
	}
      else if(uint128 <= INTMAX_MAX)
	{
	  GOLEM_INT128(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_INT128);
	}
      else if(uint128 <= UINTMAX_MAX)
	{
	  GOLEM_UINT128(&(cnst->data)) = uint128;
	  cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_UINT128);
	}
    }
  else if (g_str_has_prefix(const_str,"0b"))
    {

    }
  else
    {
      sscanf(const_str,"%ju",&uint128);
      if(golem_parser_check(parser,"."))
	{
	  const gchar * decimal_str = golem_parser_next_word(parser,TRUE);
	  guint64 decimals = 0;
	  sscanf(decimal_str,"%lu",&decimals);
	  gfloat128_t float128 = uint128;
	  if (decimals)
	    float128 = uint128 +  (decimals / pow(10.0,(int) log10(decimals) + 1));

	  if(g_str_has_suffix(decimal_str,"f"))
	    {
	      GOLEM_FLOAT32(&(cnst->data)) = (gfloat32_t)float128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_FLOAT);
	    }
	  if(g_str_has_suffix(decimal_str,"q"))
	    {
	      GOLEM_FLOAT128(&(cnst->data)) = float128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_QUAD);
	    }
	  else
	    {
	      GOLEM_FLOAT64(&(cnst->data)) = (gfloat64_t)float128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_DOUBLE);
	    }
	}
      else
	{
	  if(g_str_has_suffix(const_str,"l"))
	    {
	      GOLEM_INT64(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_LONG);
	    }
	  else if(g_str_has_suffix(const_str,"ul") && uint128 <= G_MAXUINT64)
	    {
	      GOLEM_UINT64(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_ULONG);
	    }
	  else if(g_str_has_suffix(const_str,"sb") && uint128 <= G_MAXINT8)
	    {
	      GOLEM_INT8(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_SBYTE);
	    }
	   else if(g_str_has_suffix(const_str,"b") && uint128 <= G_MAXUINT8)
	    {
	      GOLEM_UINT8(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_BYTE);
	    }
	   else if(g_str_has_suffix(const_str,"s") && uint128 <= G_MAXINT16)
	    {
	      GOLEM_INT16(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_SHORT);
	    }
	   else if(g_str_has_suffix(const_str,"us") && uint128 <= G_MAXUINT16)
	    {
	      GOLEM_UINT16(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_USHORT);
	    }
	   else if(uint128 <= G_MAXINT32)
	    {
	      GOLEM_INT32(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_INT);
	    }
	   else if(uint128 <= G_MAXUINT32)
	    {
	      GOLEM_UINT32(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_UINT);
	    }
	   else if(uint128 <= G_MAXINT64)
	    {
	      GOLEM_INT64(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_LONG);
	    }
	   else if(uint128 <= G_MAXUINT64)
	    {
	      GOLEM_UINT64(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_ULONG);
	    }
	   else if(uint128 <= INTMAX_MAX)
	    {
	      GOLEM_INT128(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_INT128);
	    }
	   else if(uint128 <= UINTMAX_MAX)
	    {
	      GOLEM_UINT128(&(cnst->data)) = uint128;
	      cnst->primitive = GOLEM_PRIMITIVE(GOLEM_TYPE_UINT128);
	    }
	  done = TRUE;
	}
    }
  return done;
}

static void
golem_const_dispose(GolemConst * cnst)
{
  if(GOLEM_METADATA(cnst->primitive) == GOLEM_TYPE_STRING ||
     GOLEM_METADATA(cnst->primitive) == GOLEM_TYPE_POINTER)
    g_free(GOLEM_POINTER(&(cnst->data)));
}

static gboolean
golem_const_check(GolemParser * parser)
{
  return golem_parser_check_is_const(parser);
}
