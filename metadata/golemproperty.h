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

#ifndef GOLEMPROPERTY_H_
#define GOLEMPROPERTY_H_

#define GOLEM_TYPE_PROPERTY	(golem_property_get_type())
G_DECLARE_FINAL_TYPE(GolemProperty,golem_property,GOLEM,PROPERTY,GolemMember)

typedef struct _GolemPropertyPrivate GolemPropertyPrivate;

struct _GolemPropertyClass
{
  GolemMemberClass parent_class;
};

struct _GolemProperty
{
  GolemMember parent_instance;

  GolemPropertyPrivate * priv;
};

GType		golem_property_get_type(void);

GParamSpec *	golem_property_get_spec(GolemProperty * property);

#endif /* GOLEMPROPERTY_H_ */
