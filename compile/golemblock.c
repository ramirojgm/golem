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

GOLEM_DEFINE_STATEMENT(GolemBlock,golem_block)

static void
golem_block_init(GolemBlock * block)
{
  block->statements = NULL;
}

static GType
golem_block_value_type(GolemBlock * var,
		     GolemScopeBuilder *scope_builder,
		     GError ** error)
{
  return G_TYPE_NONE;
}


static gboolean
golem_block_compile(GolemBlock * block,
		    GolemVMBody * body,
		    GolemScopeBuilder * scope_builder,
		    GError ** error)
{
  gboolean done = TRUE;
  if((done = golem_scope_builder_enter(scope_builder,body,error)))
    {
      for(GList * stmt_iter = g_list_first(block->statements);
	  stmt_iter;
	  stmt_iter = g_list_next(stmt_iter))
	{
	  GolemStatement * stmt = (GolemStatement *)stmt_iter->data;
	  if(!(done = golem_statement_compile(
	       stmt,
	       body,
	       scope_builder
	       ,error)))
	    {
	      break;
	    }
	  else if(stmt->klass == GOLEM_EXPRESSION_CLASS)
	    {
	      golem_vm_body_write_op(body,GOLEM_OP_DC);
	    }
	}

      if(done)
	done = golem_scope_builder_exit(scope_builder,error);
    }
  return done;
}

static gboolean
golem_block_parse(GolemBlock * block,
		  GolemParser * parser,
		  GolemExpressionLimit limit,
		  GError ** error)
{
  if(golem_parser_check(parser,"{"))
    {
      gboolean done = TRUE;
      while(!(golem_parser_is_end(parser) || golem_parser_is_next_word(parser,"}")) && done)
	{
	  GolemStatement * statement = golem_statement_parse(parser,error);
	  if(statement)
	    block->statements = g_list_append(block->statements,statement);
	  else
	    done = FALSE;
	}

      if(done && !golem_parser_check(parser,"}"))
	{
	  //TODO: throw exception
	  done = FALSE;
	}
      return done;
    }
  else
    {
      //TODO: throw exception
      return FALSE;
    }
}

static void
golem_block_dispose(GolemBlock * block)
{
  g_list_free_full(block->statements,
		   (GDestroyNotify)golem_statement_free);
}

static gboolean
golem_block_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"{");
}

