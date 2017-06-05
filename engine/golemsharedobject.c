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
#include <gmodule.h>

struct _GolemSharedObjectPrivate
{
  gchar * name;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemSharedObject,golem_shared_object,GOLEM_TYPE_STATEMENT)

static gboolean
_golem_shared_object_execute(GolemStatement * statement,GolemContext * context,GError ** error)
{
  GolemSharedObject * self = GOLEM_SHARED_OBJECT(statement);
  if(!g_module_open(self->priv->name,0))
    {
      golem_runtime_error(error,
			  GOLEM_UNKNOWN_TYPE_ERROR,
			  "not found shared object \"%s\"",
			  self->priv->name);
    }
  return TRUE;
}

static void
golem_shared_object_init(GolemSharedObject * self)
{
  self->priv = golem_shared_object_get_instance_private(self);
  self->priv->name = NULL;
}

static void
golem_shared_object_class_init(GolemSharedObjectClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_shared_object_execute;
  //TODO:add dispose
}

gboolean
golem_shared_object_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"sharedobject");
}

GolemStatement *
golem_shared_object_parse(GolemParser * parser,GError ** error)
{
  GolemSharedObject * statement = GOLEM_SHARED_OBJECT(g_object_new(GOLEM_TYPE_SHARED_OBJECT,NULL));
  gboolean done = TRUE;
  if((done = golem_parser_next_word_check(parser,"sharedobject")))
    {
      if((done = golem_parser_check_is_string(parser)))
	{
	  const gchar * str = golem_parser_next_word(parser,NULL,TRUE);
	  statement->priv->name = g_strndup(str+1,g_utf8_strlen(str,-1) - 2);
	}
    }
  if(!done)
    {
      g_object_unref(statement);
      statement = NULL;
    }
  return GOLEM_STATEMENT(statement);
}
