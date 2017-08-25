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

#ifndef GOLEMBUILDERCLASS_C_
#define GOLEMBUILDERCLASS_C_

#include "golem.h"

typedef struct _GolemBuilderClassPrivate GolemBuilderClassPrivate;

struct _GolemBuilderClassPrivate
{
  GolemTypeInfo * type_info;
};

struct _GolemBuilderClass
{
  GolemStatement parent_instance;
  GolemBuilderClassPrivate * priv;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuilderClass,golem_builder_class,GOLEM_TYPE_STATEMENT);


gboolean
_golem_builder_class_execute(GolemStatement * sentence,GolemRuntime * runtime,GError ** error)
{
  GolemBuilderClassPrivate * priv = golem_builder_class_get_instance_private(GOLEM_BUILDER_CLASS(sentence));
  GType gtype = golem_type_info_register(priv->type_info,golem_runtime_get_context(runtime),error);
  if(gtype)
    {
      GValue value = G_VALUE_INIT;
      gboolean done = FALSE;
      g_value_init(&value,G_TYPE_GTYPE);
      done = golem_context_set_auto(golem_runtime_get_context(runtime),g_type_name(gtype),&value,error);
      g_value_unset(&value);
      return done;
    }
  else
    {
      return FALSE;
    }
}

static void
golem_builder_class_init(GolemBuilderClass * self)
{
  self->priv = golem_builder_class_get_instance_private(self);
}

static void
golem_builder_class_class_init(GolemBuilderClassClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_builder_class_execute;
}

gboolean
golem_builder_class_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"class");
}

GolemBuilderClass *
golem_builder_class_parse(GolemParser * parser,GError ** error)
{
  GolemBuilderClass * self = GOLEM_BUILDER_CLASS(g_object_new(GOLEM_TYPE_BUILDER_CLASS,NULL));
  gboolean done = TRUE;

  if(golem_parser_next_word_check(parser,"class"))
    {
      if(golem_parser_check_is_named(parser))
	{
	  self->priv->type_info = golem_type_info_new(golem_parser_next_word(parser,NULL,TRUE));
	  if(golem_parser_next_word_check(parser,":"))
	    {
	      do
		{
		  GolemTypeSpec * base_type = golem_type_spec_parse(parser,error);
		  if(base_type)
		    golem_type_info_add_base(self->priv->type_info,base_type);
		  else
		    done = FALSE;
		}
	      while(golem_parser_next_word_check(parser,","));
	    }

	  if(golem_parser_next_word_check(parser,"{"))
	    {
	      while(!golem_parser_next_word_check(parser,"}"))
		{
		  if(golem_parser_next_word_check(parser,"init"))
		    {
		      if(golem_block_check(parser))
			{
			  GolemBlock * block = golem_block_parse(parser,error);
			  if(block)
			    golem_type_info_set_init(self->priv->type_info,GOLEM_STATEMENT(block));
			}
		    }
		  else if(golem_parser_next_word_check(parser,"@"))
		    {

		    }
		  else if(golem_parser_next_word_check(parser,"property"))
		    {
		      GolemTypeSpec * type_spec = NULL;
		      if((type_spec = golem_type_spec_parse(parser,error)))
			{
			  //TODO: add error for wrong definition

			  g_autofree gchar * property_name = NULL;
			  GolemStatement * getter = NULL;
			  GolemStatement * setter = NULL;
			  if(golem_parser_check_is_named(parser))
			    {
			      property_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
			      for(gchar * iter_name = property_name;*iter_name;iter_name++)
				{
				  if(*iter_name == '_')
				    *iter_name = '-';
				}

			      if(golem_parser_next_word_check(parser,"{"))
				{
				  while(!golem_parser_next_word_check(parser,"}"))
				    {
				      if(golem_parser_next_word_check(parser,"getter"))
					{
					  if(getter)
					    g_object_unref(getter);
					  getter = GOLEM_STATEMENT(golem_block_parse(parser,error));
					}
				      else if(golem_parser_next_word_check(parser,"setter"))
					{
					  if(setter)
					    g_object_unref(getter);
					  setter = GOLEM_STATEMENT(golem_block_parse(parser,error));
					}
				      else
					{
					  //TODO: add error for wrong definition
					  break;
					}
				    }
				  golem_type_info_add_property(self->priv->type_info,golem_property_spec_new(type_spec,property_name,getter,setter));
				}
			      else
				{
				  //TODO: add error for wrong definition
				  //TODO: free type spec
				}
			    }
			}
		    }
		  else if(golem_parser_next_word_check(parser,"constructed"))
		    {
		      if(golem_block_check(parser))
			{
			  GolemBlock * block = golem_block_parse(parser,error);
			  if(block)
			    golem_type_info_set_constructed(self->priv->type_info,GOLEM_STATEMENT(block));
			}
		    }
		  else if(golem_parser_next_word_check(parser,"dispose"))
		    {
		      if(golem_block_check(parser))
			{
			  GolemBlock * block = golem_block_parse(parser,error);
			  if(block)
			    golem_type_info_set_dispose(self->priv->type_info,GOLEM_STATEMENT(block));
			}
		    }
		  else if(golem_parser_check_is_named(parser))
		    {
		      GolemClosureInfo * func_info = golem_closure_info_parse(parser,error);
		      if(func_info)
			{
			  GolemStatement * body = NULL;
			  if(golem_parser_is_next_word(parser,"{"))
			    {
			      if(!(body = GOLEM_STATEMENT(golem_block_parse(parser,error))))
				{
				  g_clear_object(&self);
				}
			      else
				{
				  golem_type_info_add_function(self->priv->type_info,golem_function_internal_new(func_info,body));
				}
			    }
			  else
			    {
			      golem_parser_error(error,parser,"was expected \"{\"");
			      g_clear_object(&func_info);
			    }
			}
		    }
		}
	    }
	  else
	    {
	      golem_parser_error(error,parser,"was expected \"{\"");
	      done = FALSE;
	    }
	}
      else
	{
	  //error
	}
    }
  else
    {
      //error
    }
  return self;
}

#endif /* GOLEMBUILDERCLASS_C_ */
