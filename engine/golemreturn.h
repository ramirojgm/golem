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

#ifndef GOLEMRETURN_H_
#define GOLEMRETURN_H_

typedef struct _GolemReturnPrivate GolemReturnPrivate;

#define GOLEM_TYPE_RETURN (golem_return_get_type())
G_DECLARE_FINAL_TYPE(GolemReturn,golem_return,GOLEM,RETURN,GolemStatement)

struct _GolemReturnClass
{
  GolemStatementClass parent_class;
};

struct _GolemReturn
{
  GolemStatement	     parent_instance;
  GolemReturnPrivate * priv;
};

GType		 golem_return_get_type(void);

gboolean	 golem_return_check(GolemParser * parser);

GolemStatement * golem_return_parse(GolemParser * parser,GError ** error);


#endif /* GOLEMRETURN_H_ */
