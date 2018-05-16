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

#ifndef GOLEMMARSHAL_H_
#define GOLEMMARSHAL_H_

typedef struct _GolemMarshalInfo GolemMarshalInfo;

struct _GolemMarshalInfo
{
  /* return */
  gboolean 	return_const;
  GType		return_type;

  /* arguments*/
  guint8	n_arguments;
  GType *	argument_types;
};

GolemMarshalInfo *
		g_type_get_marshal_info(GType type);

GType 		golem_declare_marshal(gboolean 	return_const,
				       GType		return_type,
				       guint8		n_arguments,
				       const GType * 	argument_types);


#endif /* GOLEMMARSHAL_H_ */
