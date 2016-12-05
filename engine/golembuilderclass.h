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

#ifndef GOLEMBUILDERCLASS_H_
#define GOLEMBUILDERCLASS_H_

#define GOLEM_TYPE_BUILDER_CLASS	(golem_builder_class_get_type())
G_DECLARE_FINAL_TYPE(GolemBuilderClass,golem_builder_class,GOLEM,BUILDER_CLASS,GolemSentence)

struct _GolemBuilderClassClass
{
  GolemSentenceClass parent_class;
};

GType	golem_builder_class_get_type(void);

gboolean golem_builder_class_check(GolemParser * parser);

GolemBuilderClass * golem_builder_class_parse(GolemParser * parser,GError ** error);

#endif /* GOLEMBUILDERCLASS_H_ */
