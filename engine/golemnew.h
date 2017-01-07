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

#ifndef GOLEMNEW_H_
#define GOLEMNEW_H_

typedef struct _GolemNewPrivate GolemNewPrivate;

#define GOLEM_TYPE_NEW	(golem_new_get_type())
G_DECLARE_FINAL_TYPE(GolemNew,golem_new,GOLEM,NEW,GolemExpression)

struct _GolemNewClass
{
  GolemExpressionClass parent_class;
};


struct _GolemNew
{
  GolemExpression parent_instance;
  GolemNewPrivate * priv;
};

GType		  golem_new_get_type(void);

gboolean	  golem_new_check(GolemParser * parser);

GolemExpression * golem_new_parse(GolemParser * parser,GError ** error);


#endif /* GOLEMNEW_H_ */
