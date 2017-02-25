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

struct _GolemCompiledPrivate
{
  GList * sentences;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemCompiled,golem_compiled,G_TYPE_OBJECT)

static void
_golem_compiled_disponse(GObject * object)
{
  GolemCompiled * self = GOLEM_COMPILED(object);
  g_list_free_full(self->priv->sentences,g_object_unref);
  G_OBJECT_CLASS(golem_compiled_parent_class)->dispose(object);
}

static void
golem_compiled_init(GolemCompiled * self)
{
  self->priv = golem_compiled_get_instance_private(self);
}

static void
golem_compiled_class_init(GolemCompiledClass * klass)
{
  G_OBJECT_CLASS(klass)->dispose = _golem_compiled_disponse;
}

gboolean
golem_compiled_add_string(GolemCompiled * compiled,const gchar * str,gssize length,GError ** error)
{
  GolemStatement * sentence;
  gboolean done = TRUE;
  GolemParser * parser = golem_parser_new();
  golem_parser_parse(parser,str,length);
  GList * sentences = NULL;
  while(!golem_parser_is_end(parser))
    {
      sentence = golem_statement_parse(parser,error);
      if(sentence)
	{
	  sentences = g_list_append(sentences,sentence);
	}
      else
	{
	  g_list_free_full(sentences,g_object_unref);
	  sentences = NULL;
	  break;
	}
    }
  if(sentences)
      compiled->priv->sentences = g_list_concat(compiled->priv->sentences,sentences);
  g_object_unref(parser);
  return done;
}

gboolean
golem_compiled_run(GolemCompiled * compiled,GolemContext * context,GError ** error)
{
  GolemStatement * sentence;
  gboolean done = TRUE;
  for(GList * iter = g_list_first(compiled->priv->sentences);iter;iter = g_list_next(iter))
    {
      sentence = GOLEM_STATEMENT(iter->data);
      done = golem_statement_execute(sentence,context,error);
      if(!done)
	break;

    }
  return done;
}

GolemCompiled *
golem_compiled_new()
{
  return GOLEM_COMPILED(g_object_new(GOLEM_TYPE_COMPILED,NULL));
}
