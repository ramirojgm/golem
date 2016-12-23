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

G_DEFINE_TYPE_WITH_PRIVATE(GolemDeclaration,golem_declaration,GOLEM_TYPE_SENTENCE)

struct _GolemDeclarationPrivate
{
  gboolean 		is_resolved;
  gboolean 		is_constant;
  gboolean		is_array;
  gchar *	  	type_name;
  GType			type;
  gchar *		name;
  GolemExpression * 	value;
};

static void
golem_declaration_init(GolemDeclaration * self)
{
  self->priv = golem_declaration_get_instance_private(self);
}

static void
golem_declaration_class_init(GolemDeclarationClass * klass)
{

}

gboolean
golem_declaration_check(GolemParser * parser)
{
  gboolean is_declaration = FALSE;
  golem_parser_save_point(parser);
  golem_parser_next_word_check(parser,"const");
  if(golem_parser_check_is_named(parser))
    {
      golem_parser_next_word(parser,NULL,TRUE);
      if(golem_parser_check_is_named(parser))
	{
	 is_declaration = TRUE;
	}
    }
  golem_parser_restore_point(parser);
  return is_declaration;
}

GolemSentence *
golem_declaration_parse(GolemParser * parser,GError ** error)
{
  GolemDeclaration * self = GOLEM_DECLARATION(g_object_new(GOLEM_TYPE_DECLARATION,NULL));

  return GOLEM_SENTENCE(self);
}
