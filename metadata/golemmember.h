/*
	Copyright (C) 2018 Ramiro Jose Garcia Moraga

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

#ifndef GOLEMMEMBER_H_
#define GOLEMMEMBER_H_

#define GOLEM_TYPE_MEMBER	(golem_member_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemMember,golem_member,GOLEM,MEMBER,GObject)

struct _GolemMemberClass
{
  GObjectClass parent_class;

  gboolean (*get_value)(GolemMember * member,
			gpointer instance,
			gpointer dest,
			GError ** error);

  gboolean (*set_value)(GolemMember * member,
  			gpointer instance,
			gconstpointer src,
  			GError ** error);
};


GType			golem_member_get_type(void);

const gchar *		golem_member_get_name(GolemMember * member);

GolemModule *		golem_member_get_module(GolemMember * member);

GolemTypeReference	golem_member_get_value_type(GolemMember * member);

gboolean		golem_member_get_value(GolemMember * member,
					       gpointer instance,
					       gpointer dest,
					       GError ** error);

gboolean		golem_member_set_value(GolemMember * member,
					       gpointer instance,
					       gconstpointer src,
					       GError ** error);

#endif /* GOLEMMEMBER_H_ */
