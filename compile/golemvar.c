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

GOLEM_DEFINE_STATEMENT(GolemVar,golem_var)

static void
golem_var_init(GolemVar * var)
{
  var->type_name = NULL;
  var->vars = NULL;
}

static GolemTypeCode
golem_var_get_type_code(const gchar * type_name)
{
  if (g_strcmp0(type_name,"int8") == 0)
    return GOLEM_TYPE_CODE_INT8;
  else if (g_strcmp0(type_name,"uint8") == 0)
    return GOLEM_TYPE_CODE_UINT8;
  else if (g_strcmp0(type_name,"int16") == 0)
    return GOLEM_TYPE_CODE_INT16;
  else if (g_strcmp0(type_name,"uint16") == 0)
    return GOLEM_TYPE_CODE_UINT16;
  else if (g_strcmp0(type_name,"int32") == 0)
    return GOLEM_TYPE_CODE_INT32;
  else if (g_strcmp0(type_name,"uint32") == 0)
    return GOLEM_TYPE_CODE_UINT32;
  else if (g_strcmp0(type_name,"int") == 0)
    return GOLEM_TYPE_CODE_INT32;
  else if (g_strcmp0(type_name,"uint") == 0)
    return GOLEM_TYPE_CODE_UINT32;
  else if (g_strcmp0(type_name,"int64") == 0)
    return GOLEM_TYPE_CODE_INT64;
  else if (g_strcmp0(type_name,"uint64") == 0)
    return GOLEM_TYPE_CODE_UINT64;
  else if (g_strcmp0(type_name,"long") == 0)
    return GOLEM_TYPE_CODE_INT64;
  else if (g_strcmp0(type_name,"ulong") == 0)
    return GOLEM_TYPE_CODE_UINT64;
  else if (g_strcmp0(type_name,"int64") == 0)
    return GOLEM_TYPE_CODE_INT64;
  else if (g_strcmp0(type_name,"uint64") == 0)
    return GOLEM_TYPE_CODE_UINT64;
  else if (g_strcmp0(type_name,"float") == 0)
    return GOLEM_TYPE_CODE_FLOAT;
  else if (g_strcmp0(type_name,"double") == 0)
    return GOLEM_TYPE_CODE_DOUBLE;
  else if (g_strcmp0(type_name,"string") == 0)
    return GOLEM_TYPE_CODE_STRING;
  else if (g_strcmp0(type_name,"pointer") == 0)
    return GOLEM_TYPE_CODE_POINTER;
  else if (g_strcmp0(type_name,"object") == 0)
    return GOLEM_TYPE_CODE_OBJECT;
  else
    return GOLEM_TYPE_CODE_UNDEFINED;
}

static GolemTypeCode
golem_var_value_type(GolemVar * var,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
  return GOLEM_TYPE_CODE_UNDEFINED;
}


static gboolean
golem_var_compile(GolemVar * var,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = TRUE;
  GolemTypeCode type = golem_var_get_type_code(var->type_name);
  for(GList * var_iter = g_list_first(var->vars);
      var_iter;
      var_iter = g_list_next(var_iter))
    {
      if(!(done = golem_scope_builder_define(scope_builder,type,(gchar*)var_iter->data,error)))
	break;
    }
  return done;
}

static gboolean
golem_var_parse(GolemVar * var,
		GolemParser * parser,
		GolemExpressionLimit limit,
		GError ** error)
{
  gboolean done = TRUE;
  if(golem_parser_check_is_named(parser))
    {
      var->type_name = g_strdup(golem_parser_next_word(parser,TRUE));
      do
	{
	  gchar * var_name = g_strdup(golem_parser_next_word(parser,TRUE));
	  var->vars = g_list_append(var->vars,var_name);
	}
      while (golem_parser_check(parser,","));
      if(!golem_parser_check(parser,";"))
	{
	  //TODO: throw exception
	  done = FALSE;
	}
    }
  else
    {
      //TODO: throw exception
      done = FALSE;
    }
  return done;
}

static void
golem_var_info_free(GolemVarInfo * var_info)
{
  g_free(var_info->name);
  if(var_info->value)
    golem_statement_free(var_info->value);
  g_free(var_info);
}

static void
golem_var_dispose(GolemVar * var)
{
  g_free(var->type_name);
  g_list_free_full(var->vars,
		   (GDestroyNotify)golem_var_info_free);
}

static gboolean
golem_var_check(GolemParser * parser)
{
  gboolean check = FALSE;
  golem_parser_save_point(parser);
  if(golem_parser_check_is_named(parser)) {
      golem_parser_skip(parser);
      check = golem_parser_check_is_named(parser);
  }
  golem_parser_restore_point(parser);
  return check;
}
