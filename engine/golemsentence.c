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
#include "signal.h"

G_DEFINE_ABSTRACT_TYPE(GolemSentence,golem_sentence,G_TYPE_OBJECT)


static gboolean
_golem_sentence_execute_real(GolemSentence * self,GolemContext * context,GError ** error)
{
  golem_throw(error,
      GOLEM_NOT_IMPLEMENTED_ERROR,
      "not implement"
  );
  return FALSE;
}

static void
golem_sentence_init(GolemSentence * self)
{
  golem_sentence_get_instance_private(self);
}

static void
golem_sentence_class_init(GolemSentenceClass * klass)
{
  klass->execute = _golem_sentence_execute_real;
}


gboolean
golem_sentence_execute(GolemSentence * self,GolemContext * context,GError ** error)
{
  GolemSentenceClass * klass = GOLEM_SENTENCE_GET_CLASS(self);
  return klass->execute(self,context,error);
}


GolemSentence *
golem_sentence_parse(GolemParser * parser,GError ** error)
{
  if(golem_builder_class_check(parser))
      return GOLEM_SENTENCE(golem_builder_class_parse(parser,error));
  else if(golem_builder_extern_check(parser))
    return GOLEM_SENTENCE(golem_builder_extern_parse(parser,error));
  else if(golem_block_check(parser))
    return GOLEM_SENTENCE(golem_block_parse(parser,error));
  else
    golem_throw(error,GOLEM_SYNTAXIS_ERROR,"unknown sentence '%s'",golem_parser_next_word(parser,NULL,FALSE));
}
