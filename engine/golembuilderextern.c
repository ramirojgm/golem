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

#include "golem.h"
#include "gmodule.h"

struct _GolemBuilderExternPrivate
{
  GolemFuncMetaData * meta_data;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuilderExtern,golem_builder_extern,GOLEM_TYPE_SENTENCE)

gboolean
golem_builder_extern_execute(GolemSentence * sentence,GolemContext * context,GError ** error)
{
  GolemBuilderExtern * self = GOLEM_BUILDER_EXTERN(sentence);
  self->priv = golem_builder_extern_get_instance_private(self);
  GModule * global_module = g_module_open(NULL,G_MODULE_BIND_LAZY);
  gpointer address = NULL;
  gboolean done = TRUE;
  if(g_module_symbol(global_module,golem_func_meta_data_get_name(self->priv->meta_data),&address))
    {
      GValue func_value = G_VALUE_INIT;
      g_value_init(&func_value,GOLEM_TYPE_FUNC);
      g_value_take_object(&func_value,golem_func_new(self->priv->meta_data,address));
      golem_context_declare(context,golem_func_meta_data_get_name(self->priv->meta_data),GOLEM_TYPE_FUNC,error);
      golem_context_set(context,golem_func_meta_data_get_name(self->priv->meta_data),&func_value,error);
      g_value_unset(&func_value);
      done = TRUE;
    }
  else
    {
      golem_throw(error,
		  GOLEM_NOT_EXISTS_ERROR,
		  "the function \"%s\" not exists",
		  self->priv->meta_data->name
      );
    }
  return done;
}

static void
golem_builder_extern_init(GolemBuilderExtern * self)
{
  self->priv = golem_builder_extern_get_instance_private(self);
  self->priv->meta_data = NULL;
}

static void
golem_builder_extern_class_init(GolemBuilderExternClass * klass)
{
  GOLEM_SENTENCE_CLASS(klass)->execute = golem_builder_extern_execute;
}

gboolean
golem_builder_extern_check(GolemParser * parser)
{
 return golem_parser_is_next_word(parser,"extern");
}

GolemBuilderExtern *
golem_builder_extern_parse(GolemParser * parser,GError ** error)
{
  GolemBuilderExtern * self = GOLEM_BUILDER_EXTERN(g_object_new(GOLEM_TYPE_BUILDER_EXTERN,NULL));
  GolemBuilderExternPrivate * priv = golem_builder_extern_get_instance_private(self);

  if(golem_parser_next_word_check(parser,"extern"))
    {
      GolemFuncMetaData * meta_data = golem_func_meta_data_parse(parser,error);
      priv->meta_data = meta_data;
      if(!golem_parser_next_word_check(parser,";"))
	{
	  //TODO: throw error expected ';'
	  g_clear_object(&self);
	}
    }
  else
    {
      //TODO: throw error expected 'extern'
      g_clear_object(&self);
    }
  return self;
}
