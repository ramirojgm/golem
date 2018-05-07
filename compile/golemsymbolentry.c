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

GOLEM_DEFINE_STATEMENT(GolemSymbolEntry,golem_symbol_entry)

static void
golem_symbol_entry_init(GolemSymbolEntry * symbol)
{
  symbol->body = NULL;
  symbol->external = FALSE;
  symbol->arguments = NULL;
  symbol->ret_const = FALSE;
  symbol->ret_type =  NULL;
}

static gboolean
golem_symbol_entry_check(GolemParser * parser)
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
golem_symbol_entry_parse(GolemSymbolEntry * symbol,
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
			   GolemSymbolEntryArgument * symbol_argument = g_new0(GolemSymbolEntryArgument,1);
			   symbol_argument->type = g_strdup(argument_type);
			   symbol_argument->name = g_strdup(golem_parser_next_word(parser,TRUE));
			   symbol->arguments = g_list_append(symbol->arguments,symbol_argument);
			 }
		       else
			 {
			   //TODO: exception
			   g_propagate_error(error,g_error_new(
			       GOLEM_ERROR,
			       GOLEM_COMPILE_ERROR_SYNTAXES,
			       ""
			   ));
			   done = FALSE;
			   break;
			 }
		    }
		  else
		    {
		      //TODO: throw exception
		      done = FALSE;
		      g_propagate_error(error,g_error_new(
			 GOLEM_ERROR,
			 GOLEM_COMPILE_ERROR_SYNTAXES,
			 ""
		      ));
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
	      g_propagate_error(error,g_error_new(
		 GOLEM_ERROR,
		 GOLEM_COMPILE_ERROR_SYNTAXES,
		 ""
	      ));
	    }
	}
      else
	{
	  //TODO: throw exception
	  g_propagate_error(error,g_error_new(
	     GOLEM_ERROR,
	     GOLEM_COMPILE_ERROR_SYNTAXES,
	     ""
	  ));
	}
    }
  else
    {
      //TODO: throw exception
      g_propagate_error(error,g_error_new(
	 GOLEM_ERROR,
	 GOLEM_COMPILE_ERROR_SYNTAXES,
	 ""
      ));
    }
  return done;
}



static gboolean
golem_symbol_entry_compile(GolemSymbolEntry * symbol,
		    GolemVMBody * body,
		    GolemScopeBuilder * scope_builder,
		    GError ** error)
{
  gboolean done = TRUE;
  GolemVMData functioName;
  functioName.data->pointer_v = symbol->name;
  golem_scope_builder_define(scope_builder,
			     GOLEM_TYPE_SYMBOL,
			     symbol->name,
			     error);

  golem_vm_body_write_data(body,
			   &functioName,
			   G_TYPE_STRING,
			   g_utf8_strlen(symbol->name,1024));

  golem_vm_body_write_op(body,GOLEM_OP_FN);
  golem_scope_builder_set(scope_builder,symbol->name,error);
  return done;
}

static GType
golem_symbol_entry_value_type(GolemSymbolEntry * symbol,
			GolemScopeBuilder * scope_builder,
			GError ** error)
{
  return G_TYPE_NONE;
}

static void
golem_symbol_entry_dispose(GolemSymbolEntry * symbol)
{

}
