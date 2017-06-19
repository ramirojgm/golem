/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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


#include "golem.h"

struct _GolemExtendsPrivate
{
  gchar * type_name;
  GList * functions;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemExtends,golem_extends,GOLEM_TYPE_STATEMENT)

static gboolean
_golem_extends_execute(GolemStatement * statement,GolemRuntime * runtime,GError ** error)
{
  gboolean done = FALSE;
  GolemExtends * self = GOLEM_EXTENDS(statement);
  GType gtype = golem_context_get_type_define(golem_runtime_get_context(runtime),self->priv->type_name,error);
  if(gtype)
    {
      done = TRUE;
      GolemTypeInfo * info = golem_type_info_from_gtype(gtype);
      for(GList * func_iter = g_list_first(self->priv->functions);func_iter;func_iter = g_list_next(func_iter))
	{
	  golem_type_info_add_function(info,(GolemFunctionSpec *)func_iter->data);
	}
    }
  return done;
}

static void
golem_extends_init(GolemExtends * self)
{
  self->priv = golem_extends_get_instance_private(self);
}

static void
golem_extends_class_init(GolemExtendsClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_extends_execute;
}

gboolean
golem_extends_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"extends");
}

GolemExtends *
golem_extends_parse(GolemParser * parser,GError ** error)
{
  GolemExtends * self = GOLEM_EXTENDS(g_object_new(GOLEM_TYPE_EXTENDS,NULL));
  gboolean done = TRUE;
  if(golem_parser_next_word_check(parser,"extends"))
    {
      if(golem_parser_check_is_named(parser))
	{
	  self->priv->type_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
	  if(golem_parser_next_word_check(parser,"{"))
	    {
	      while(!golem_parser_next_word_check(parser,"}"))
		{
		  GolemFunctionType type_func = GOLEM_FUNCTION_INTERNAL;
		  if(golem_parser_next_word_check(parser,"extern"))
		    {
		      type_func = GOLEM_FUNCTION_SYMBOLIC;
		    }
		  else if(golem_parser_next_word_check(parser,"virtual"))
		    {
		      type_func = GOLEM_FUNCTION_VIRTUAL;
		    }
		  GolemClosureInfo * info = NULL;
		  if((info = golem_closure_info_parse(parser,error)))
		    {
		      if(type_func == GOLEM_FUNCTION_INTERNAL)
			{
			  if(golem_parser_is_next_word(parser,"{"))
			    {
			      GolemBlock * body = NULL;
			      if((body = golem_block_parse(parser,error)))
				{
				  self->priv->functions = g_list_append(self->priv->functions,golem_function_internal_new(info,GOLEM_STATEMENT(body)));
				}
			      else
				{
				  g_object_unref(info);
				  done = FALSE;
				  break;
				}
			    }
			  else
			    {
			      g_object_unref(info);
			      done = FALSE;
			      golem_parser_error(error,parser,"was expected \"{\"");
			      break;
			    }
			}
		      else if(type_func == GOLEM_FUNCTION_SYMBOLIC)
			{
			  gchar * real_name = g_strdup_printf("%s_%s",golem_type_get_prefix(self->priv->type_name),golem_closure_info_get_name(info));
			  if(golem_parser_next_word_check(parser,":"))
			    {
			      g_free(real_name);
			      real_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
			    }
			  if(golem_parser_next_word_check(parser,";"))
			    {
			      self->priv->functions = g_list_append(self->priv->functions,golem_function_symbol_new(info,real_name));
			    }
			  else
			    {
			      g_object_unref(info);
			      done = FALSE;
			      golem_parser_error(error,parser,"was expected \";\"");
			      g_free(real_name);
			      break;
			    }
			  g_free(real_name);
			}
		      else if(type_func == GOLEM_FUNCTION_VIRTUAL)
			{

			}
		    }
		  else
		    {
		      done = FALSE;
		    }
		}
	    }
	  else
	    {
	      done = FALSE;
	      golem_parser_error(error,parser,"was expected \"{\"");
	    }
	}
      else
	{
	  done = FALSE;
	  golem_parser_error(error,parser,"was expected the type to extend");
	}
    }
  if(!done)
    g_clear_object(&self);
  return self;
}
