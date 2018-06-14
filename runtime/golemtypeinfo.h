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

#ifndef GOLEMTYPEINFO_H_
#define GOLEMTYPEINFO_H_

#define GOLEM_TYPE_TYPE_INFO	(golem_type_info_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemTypeInfo,golem_type_info,GOLEM,TYPE_INFO,GolemMetadata)

struct _GolemTypeInfoClass
{
  GolemMetadataClass parent_class;

  gboolean 	  (*is_derived_type)(GolemTypeInfo * type_info,
				     GolemTypeInfo * type_derived);
};

GType			golem_type_info_get_type(void);

const GolemTypeInfo *	golem_type_info_get_parent(GolemTypeInfo * type_info);

gboolean		golem_type_info_is_derived_type(GolemTypeInfo * type_info,
							GolemTypeInfo * type_derived);

#endif /* GOLEMTYPEINFO_H_ */
