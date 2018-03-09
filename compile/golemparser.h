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

G_BEGIN_DECLS

GLIB_AVAILABLE_IN_ALL
GType		golem_parser_get_type(void);

GLIB_AVAILABLE_IN_ALL
GolemParser * 	golem_parser_new(const gchar * source_name);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_parse(GolemParser * parser,
				   const gchar * str,gssize length);

GLIB_AVAILABLE_IN_ALL
const gchar *	golem_parser_get_source_name(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_skip(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_next_word_has_prefix(GolemParser * parser,
						  const gchar * prefix);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_next_word_has_suffix(GolemParser * parser,
						  const gchar * suffix);

GLIB_AVAILABLE_IN_ALL
void		golem_parser_rewind(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_is_end(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_is_next_word(GolemParser * parser,
					  const gchar * word);

GLIB_AVAILABLE_IN_ALL
const gchar *	golem_parser_next_word(GolemParser * parser,
				       gsize * length,
				       gboolean move);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_next_word_check(GolemParser * parser,
					     const gchar * str);

GLIB_AVAILABLE_IN_ALL
void		golem_parser_save_point(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
void		golem_parser_commit_point(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
void		golem_parser_restore_point(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gint		golem_parser_get_line(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gint		golem_parser_get_column(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_check_is_number(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_check_is_const(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_check_is_hex(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_check_is_named(GolemParser * parser);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_parser_check_is_string(GolemParser * parser);

G_END_DECLS

#endif /* GOLEMPARSER_H_ */
