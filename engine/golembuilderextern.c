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
  gchar * name;
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
  if(g_module_symbol(global_module,self->priv->name,&address))
    {
      GValue func_value;
      g_value_init(&func_value,GOLEM_TYPE_FUNC);
      g_value_take_object(&func_value,golem_func_new(self->priv->meta_data,address));
      golem_context_declare(context,self->priv->name,GOLEM_TYPE_FUNC,error);
      golem_context_set(context,self->priv->name,&func_value,error);
      g_value_unset(&func_value);
      done = TRUE;
    }

  return done;
}

static void
golem_builder_extern_init(GolemBuilderExtern * self)
{
  self->priv = golem_builder_extern_get_instance_private(self);
  self->priv->name = NULL;
  self->priv->meta_data = NULL;
}

static void
golem_builder_extern_class_init(GolemBuilderExternClass * klass)
{

}
