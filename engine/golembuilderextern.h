/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

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

#ifndef GOLEMBUILDEREXTERN_H_
#define GOLEMBUILDEREXTERN_H_

#define GOLEM_TYPE_BUILDER_EXTERN	(golem_builder_extern_get_type())
G_DECLARE_FINAL_TYPE(GolemBuilderExtern,golem_builder_extern,GOLEM,BUILDER_EXTERN,GolemStatement)

typedef struct _GolemBuilderExternPrivate GolemBuilderExternPrivate;

struct _GolemBuilderExternClass
{
  GolemStatementClass parent_class;

};

struct _GolemBuilderExtern
{
  GolemStatement parent_instance;
  GolemBuilderExternPrivate * priv;
};

GType			golem_builder_extern_get_type(void);

gboolean		golem_builder_extern_check(GolemParser * parser);

GolemBuilderExtern * 	golem_builder_extern_parse(GolemParser * parser,GError ** error);

#endif /* GOLEMBUILDEREXTERN_H_ */
