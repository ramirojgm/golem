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

GOLEM_DEFINE_STATEMENT(GolemSymbol,golem_symbol)

static void
golem_symbol_init(GolemSymbol * symbol)
{
  symbol->body = NULL;
  symbol->external = FALSE;
  symbol->arguments = NULL;
  symbol->ret_const = FALSE;
  symbol->ret_type =  NULL;
}

static gboolean
golem_symbol_check(GolemParser * parser)
{
  gboolean result = FALSE;
  golem_parser_save_point(parser);
  golem_parser_check(parser,"const");
  if((result = golem_parser_check_is_named(parser))){
      golem_parser_skip(parser);
      if((result = golem_parser_check_is_named(parser)))
	{
	  golem_parser_skip(parser);
	  result = golem_parser_check(parser,"(");
	}
  }
  golem_parser_restore_point(parser);
  return result;
}

static gboolean
golem_symbol_parse(GolemSymbol * symbol,
		    GolemParser * parser,
		    GolemExpressionLimit limit,
		    GError ** error)
{
  gboolean done = TRUE;

  symbol->ret_const = golem_parser_check(parser,"const");

  if(golem_parser_check_is_named(parser))
    {
      symbol->ret_type = g_strdup(golem_parser_next_word(parser,TRUE));
      if(golem_parser_check_is_named(parser))
	{
	  symbol->name = g_strdup(golem_parser_next_word(parser,TRUE));
	  if(golem_parser_check(parser,"("))
	    {
	      while(!golem_parser_check(parser,")"))
		{
		  if(golem_parser_check_is_named(parser))
		    {
		       const gchar * argument_type = golem_parser_next_word(parser,TRUE);
		       if(golem_parser_check_is_named(parser))
			 {
			   GolemSymbolArgument * symbol_argument = g_new0(GolemSymbolArgument,1);
			   symbol_argument->type = g_strdup(argument_type);
			   symbol_argument->name = g_strdup(golem_parser_next_word(parser,TRUE));
			   symbol->arguments = g_list_append(symbol_argument,symbol_argument);
			 }
		       else
			 {
			   //TODO: throw exception
			   done = FALSE;
			   break;
			 }
		    }
		  else
		    {
		      //TODO: throw exception
		      done = FALSE;
		      break;
		    }

		  if(golem_parser_check(parser,")"))
		    {
		      break;
		    }
		  else if(!golem_parser_check(parser,","))
		    {
		      //TODO: throw exception
		      done = FALSE;
		      break;
		    }
		}

	      if(done)
		{
		  if(!golem_parser_check(parser,";"))
		    {
		      symbol->external = FALSE;
		      symbol->body = golem_statement_parse(parser,error);
		      if(!symbol->body)
			{
			  done = FALSE;
			  g_free(symbol);
			  symbol = NULL;
			}
		    }
		  else
		    {
		      symbol->external = TRUE;
		    }
		}
	    }
	  else
	    {
	      //TODO:throw exception
	    }
	}
      else
	{
	  //TODO: throw exception
	}
    }
  else
    {
      //TODO: throw exception
    }
  return done;
}

static gboolean
golem_symbol_compile(GolemSymbol * symbol,
		      GolemVMBody * body,
		      GolemScopeBuilder * scope_builder,
		      GError ** error)
{
  return FALSE;
}

static GolemTypeCode
golem_symbol_value_type(GolemSymbol * symbol,
			GolemScopeBuilder * scope_builder,
			GError ** error)
{
  return GOLEM_TYPE_CODE_UNDEFINED;
}

static void
golem_symbol_dispose(GolemSymbol * symbol)
{

}
