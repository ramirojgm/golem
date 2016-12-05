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

#define GOLEM_SENTENCE_ERROR	(golem_sentence_error_quark())

enum GolemSentenceError
{
  GOLEM_SENTENCE_NOT_IMPLEMENT_ERROR
};

GQuark
golem_sentence_error_quark(void)
{
  return g_quark_from_static_string("golem-sentence-error-quark");
}

static gboolean
_golem_sentence_execute_real(GolemSentence * self,GolemContext * context,GError ** error)
{
  golem_sentence_throw_error(error,g_error_new(
      GOLEM_SENTENCE_ERROR,
      GOLEM_SENTENCE_NOT_IMPLEMENT_ERROR,
      "not implement"
  ));
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

void
golem_sentence_throw_error(GError ** error,GError * err)
{
  if(error)
    {
      *error = err;
    }
  else
    {
      g_printerr("%s",err->message);
      g_error_free(err);
      raise(SIGTRAP);
    }
}

gboolean
golem_sentence_execute(GolemSentence * self,GolemContext * context,GError ** error)
{
  GolemSentenceClass * klass = GOLEM_SENTENCE_GET_CLASS(self);
  return klass->execute(self,context,error);
}


GolemSentence * golem_sentence_parse(GolemParser * parser,GError ** error)
{
  if(golem_builder_class_check(parser))
    return GOLEM_SENTENCE(golem_builder_class_parse(parser,error));
  else if(golem_block_check(parser))
    return GOLEM_SENTENCE(golem_block_parse(parser,error));
  return NULL;
}
