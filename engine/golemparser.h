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

#ifndef GOLEMPARSER_H_
#define GOLEMPARSER_H_

#include <glib.h>
#include <glib-object.h>

#define GOLEM_TYPE_PARSER (golem_parser_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemParser,golem_parser,GOLEM,PARSER,GObject)

struct _GolemParserClass
{
  GObjectClass parent_class;
};


GType		golem_parser_get_type(void);

GolemParser * 	golem_parser_new();

gboolean	golem_parser_parse(GolemParser * parser,const gchar * str,gssize length);

gboolean	golem_parser_skip(GolemParser * parser);

gboolean	golem_parser_next_word_has_prefix(GolemParser * parser,const gchar * prefix);

gboolean	golem_parser_next_word_has_suffix(GolemParser * parser,const gchar * suffix);

void		golem_parser_rewind(GolemParser * parser);

gboolean	golem_parser_is_end(GolemParser * parser);

gboolean	golem_parser_is_next_word(GolemParser * parser,const gchar * word);

const gchar *	golem_parser_next_word(GolemParser * parser,gsize * length,gboolean move);

gboolean	golem_parser_next_word_check(GolemParser * parser,const gchar * str);

void		golem_parser_save_point(GolemParser * parser);

void		golem_parser_restore_point(GolemParser * parser);

gint		golem_parser_get_line(GolemParser * parser);

gint		golem_parser_get_column(GolemParser * parser);

gboolean	golem_parser_check_is_number(GolemParser * parser);

gboolean	golem_parser_check_is_const(GolemParser * parser);

gboolean	golem_parser_check_is_hex(GolemParser * parser);

gboolean	golem_parser_check_is_named(GolemParser * parser);

gboolean	golem_parser_check_is_string(GolemParser * parser);

#endif /* GOLEMPARSER_H_ */
