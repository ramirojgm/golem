/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ENGINE_GOLEMIF_H_
#define ENGINE_GOLEMIF_H_

typedef struct _GolemIfPrivate GolemIfPrivate;

#define GOLEM_TYPE_IF	(golem_if_get_type())
G_DECLARE_FINAL_TYPE(GolemIf,golem_if,GOLEM,IF,GolemStatement);

struct _GolemIfClass
{
  GolemStatementClass parent_class;
};

struct _GolemIf
{
  GolemStatement parent_instance;
  GolemIfPrivate * priv;
};

GType		golem_if_get_type(void);

gboolean 	golem_if_check(GolemParser * parser);

GolemIf *	golem_if_parse(GolemParser * parser,GError ** error);

#endif /* ENGINE_GOLEMIF_H_ */
