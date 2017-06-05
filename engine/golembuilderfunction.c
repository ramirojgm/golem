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

struct _GolemBuilderFunctionPrivate
{
  GolemClosureInfo * info;
  GolemStatement * body;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuilderFunction,golem_builder_function,GOLEM_TYPE_STATEMENT)

gboolean
golem_builder_function_execute(GolemStatement * sentence,GolemContext * context,GError ** error)
{
  GolemBuilderFunction * self = GOLEM_BUILDER_FUNCTION(sentence);
  gboolean done;
  done = golem_closure_info_resolve(self->priv->info,context,error);
  if(done)
    {
      GValue func_value = G_VALUE_INIT;
      g_value_init(&func_value,G_TYPE_CLOSURE);
      g_value_take_boxed(&func_value,golem_function_new(self->priv->info,context,self->priv->body));
      golem_context_declare(context,golem_closure_info_get_name(self->priv->info),G_TYPE_CLOSURE,error);
      golem_context_set(context,golem_closure_info_get_name(self->priv->info),&func_value,error);
      g_value_unset(&func_value);
      done = TRUE;
    }
  return done;
}

static void
golem_builder_function_init(GolemBuilderFunction * self)
{
  self->priv = golem_builder_function_get_instance_private(self);
  self->priv->info = NULL;
  self->priv->body= NULL;
}

static void
golem_builder_function_class_init(GolemBuilderFunctionClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = golem_builder_function_execute;
}

gboolean
golem_builder_function_check(GolemParser * parser)
{
  gboolean checked = FALSE;
  golem_parser_save_point(parser);
  if(golem_parser_check_is_named(parser)){
      golem_parser_next_word(parser,NULL,TRUE);
      if(golem_parser_check_is_named(parser)){
	  golem_parser_next_word(parser,NULL,TRUE);
	  if(golem_parser_next_word_check(parser,"("))
	    checked = TRUE;
      }
  }
  golem_parser_restore_point(parser);
  return checked;
}

GolemBuilderFunction *
golem_builder_function_parse(GolemParser * parser,GError ** error)
{
  GolemBuilderFunction * self = GOLEM_BUILDER_FUNCTION(g_object_new(GOLEM_TYPE_BUILDER_FUNCTION,NULL));
  GolemBuilderFunctionPrivate * priv = golem_builder_function_get_instance_private(self);

  GolemClosureInfo * info = golem_closure_info_parse(parser,error);
  if(info)
    {
      priv->info = info;
      if(golem_parser_is_next_word(parser,"{"))
	{
	  if(!(priv->body = GOLEM_STATEMENT(golem_block_parse(parser,error))))
	    {
	      g_clear_object(&self);
	    }
	}
      else
	{
	  golem_parser_error(error,parser,"was expected \"{\"");
	  g_clear_object(&self);
	}
    }
  else
    {
      g_clear_object(&self);
    }
  return self;
}
