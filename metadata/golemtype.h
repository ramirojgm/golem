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

#ifndef GOLEMTYPE_H_
#define GOLEMTYPE_H_

#define GOLEM_TYPE_TYPE		(golem_type_get_type())
G_DECLARE_DERIVABLE_TYPE	(GolemType,golem_type,GOLEM,TYPE,GolemMetadata)

struct _GolemTypeClass
{
  GolemMetadata parent_class;

  GType   (*get_gtype) (GolemType * type);

  GList *   (*get_attributes) (GolemType * type);
  GList *   (*get_functions) (GolemType * type);
  GList *   (*get_properties) (GolemType * type);
};


GType     golem_type_get_type(void);

GType     golem_type_get_gtype();




#endif /* GOLEMTYPE_H_ */
