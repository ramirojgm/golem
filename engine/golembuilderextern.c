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
  GolemClosureInfo * info;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuilderExtern,golem_builder_extern,GOLEM_TYPE_STATEMENT)

gboolean
golem_builder_extern_execute(GolemStatement * sentence,GolemContext * context,GError ** error)
{
  GolemBuilderExtern * self = GOLEM_BUILDER_EXTERN(sentence);
  GModule * global_module = g_module_open(NULL,G_MODULE_BIND_LOCAL);
  gpointer address = NULL;
  gboolean done;

  done = golem_closure_info_resolve(self->priv->info,context,error);
  if(done)
    {
      if(g_module_symbol(global_module,golem_closure_info_get_name(self->priv->info),&address))
	{
	  GValue func_value = G_VALUE_INIT;
	  g_value_init(&func_value,G_TYPE_CLOSURE);
	  g_value_take_boxed(&func_value,golem_symbol_new(self->priv->info,address));
	  golem_context_declare(context,golem_closure_info_get_name(self->priv->info),G_TYPE_CLOSURE,error);
	  golem_context_set(context,golem_closure_info_get_name(self->priv->info),&func_value,error);
	  g_value_unset(&func_value);
	  done = TRUE;
	}
      else
	{
	  golem_throw(error,
		      GOLEM_NOT_EXISTS_ERROR,
		      "the function \"%s\" not exists",
		      golem_closure_info_get_name(self->priv->info)
	  );
	}
    }
  g_module_close(global_module);
  return done;
}

static void
golem_builder_extern_init(GolemBuilderExtern * self)
{
  self->priv = golem_builder_extern_get_instance_private(self);
  self->priv->info = NULL;
}

static void
golem_builder_extern_class_init(GolemBuilderExternClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = golem_builder_extern_execute;
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
      GolemClosureInfo * info = golem_closure_info_parse(parser,error);
      priv->info = info;
      if(!golem_parser_next_word_check(parser,";"))
	{
	  //TODO: throw error expected ';'
	  g_clear_object(&self);
	}
      g_print("extern:%s\n",golem_parser_next_word(parser,NULL,FALSE));
    }
  else
    {
      //TODO: throw error expected 'extern'
      g_clear_object(&self);
    }
  return self;
}
