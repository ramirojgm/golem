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

static GType
golem_var_value_type(GolemVar * var,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
  return G_TYPE_NONE;
}


static gboolean
golem_var_compile(GolemVar * var,
		  GolemVMBody * body,
		  GolemScopeBuilder * scope_builder,
		  GError ** error)
{
  gboolean done = TRUE;
  GType type = G_TYPE_OBJECT;

  for(GList * var_iter = g_list_first(var->vars);
      var_iter;
      var_iter = g_list_next(var_iter))
    {
      GolemVarInfo * info = (GolemVarInfo*)var_iter->data;
      if((done = golem_scope_builder_define(scope_builder,type,info->name,error)))
	{
	  if(info->value)
	    {
	      if((done = golem_statement_compile(info->value,body,scope_builder,error)))
		{
		  done = golem_scope_builder_set(scope_builder,info->name,error);
		  if(!done)
		    break;
		}
	      else
		{
		  break;
		}
	    }
	}
      else
	{
	  break;
	}
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
	  GolemVarInfo * info = g_new0(GolemVarInfo,1);
	  info->name = g_strdup(golem_parser_next_word(parser,TRUE));
	  if(golem_parser_check(parser,"="))
	    {
	      info->value = golem_expression_parse_new(parser,
						       GOLEM_EXPRESSION_LIMIT_SEMICOLON_COMA,
						       error);
	      if(!info->value)
		{
		  done = FALSE;
		  golem_var_info_free(info);
		}

	    }

	  if(done)
	    var->vars = g_list_append(var->vars,info);
	  else
	    break;
	}
      while (golem_parser_check(parser,","));
      if(done && !golem_parser_check(parser,";"))
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
