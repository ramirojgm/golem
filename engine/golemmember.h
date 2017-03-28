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

#ifndef GOLEMMEMBER_H_
#define GOLEMMEMBER_H_

#define GOLEM_TYPE_MEMBER	(golem_member_get_type())
G_DECLARE_FINAL_TYPE(GolemMember,golem_member,GOLEM,MEMBER,GolemExpression)

typedef struct _GolemMemberPrivate GolemMemberPrivate;

struct _GolemMemberClass
{
  GolemExpressionClass parent_class;

};

struct _GolemMember
{
  GolemExpression parent_instance;
  GolemMemberPrivate * priv;
};

GType		golem_member_get_type(void);

gboolean 	golem_member_check(GolemParser * parser);

GolemExpression* golem_member_parse(GolemParser * parser,GolemExpression * instance,GolemExpressionLimit limit,GError ** error);


#endif /* GOLEMMEMBER_H_ */
