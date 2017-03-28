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
_golem_builder_class_execute(GolemStatement * sentence,GolemContext * context,GError ** error)
{

  return TRUE;
}

static void
golem_builder_class_init(GolemBuilderClass * self)
{
  self->priv = golem_builder_class_get_instance_private(self);
}

static void
golem_builder_class_class_init(GolemBuilderClassClass * klass)
{

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

  if(golem_parser_next_word_check(parser,"class"))
    {
      if(golem_parser_check_is_named(parser))
	{

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
