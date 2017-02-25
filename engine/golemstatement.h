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

#ifndef GOLEMSTATEMENT_H_
#define GOLEMSTATEMENT_H_

#define GOLEM_TYPE_STATEMENT (golem_statement_get_type())

G_DECLARE_DERIVABLE_TYPE(GolemStatement,golem_statement,GOLEM,STATEMENT,GObject)


struct _GolemStatementClass
{
  GObjectClass parent_class;

  gboolean (*execute)(GolemStatement *,GolemContext *,GError ** );
};

GType	golem_statement_get_type(void);

gboolean golem_statement_execute(GolemStatement * sentence,GolemContext * context,GError ** error);

GolemStatement * golem_statement_parse(GolemParser * parser,GError ** error);

#endif /* GOLEMSTATEMENT_H_ */
