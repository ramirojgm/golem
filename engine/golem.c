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

gboolean
golem_compile_string(GolemContext * context,const gchar * script,gssize length,GError ** error)
{
  GolemSentence * sentence;
  gboolean done = TRUE;
  GolemParser * parser = golem_parser_new();
  golem_parser_parse(parser,script,length);
  GList * sentences = NULL;
  while(!golem_parser_is_end(parser))
    {
      sentence = golem_sentence_parse(parser,error);
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
  for(GList * iter = g_list_first(sentences);iter;iter = g_list_next(iter))
    {
      sentence = GOLEM_SENTENCE(iter->data);
      done = golem_sentence_execute(sentence,context,error);
      if(!done)
	break;
    }
  g_list_free_full(sentences,g_object_unref);
  sentences = NULL;
  g_object_unref(parser);
  return done;
}

