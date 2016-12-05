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

#ifndef GOLEMSENTENCE_H_
#define GOLEMSENTENCE_H_

#define GOLEM_TYPE_SENTENCE (golem_sentence_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemSentence,golem_sentence,GOLEM,SENTENCE,GObject)


struct _GolemSentenceClass
{
  GObjectClass parent_class;

  gboolean (*execute)(GolemSentence *,GolemContext *,GError ** );
};

void	golem_sentence_throw_error(GError ** error,GError * err);

GType	golem_sentence_get_type(void);

gboolean golem_sentence_execute(GolemSentence * sentence,GolemContext * context,GError ** error);

GolemSentence * golem_sentence_parse(GolemParser * parser,GError ** error);

#endif /* GOLEMSENTENCE_H_ */
