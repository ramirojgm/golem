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

#ifndef GOLEMMARSHALL_H_
#define GOLEMMARSHALL_H_

#define GOLEM_TYPE_MARSHALL	(golem_marshall_get_type())
G_DECLARE_FINAL_TYPE(GolemMarshall,golem_marshall,GOLEM,MARSHALL,GolemType)

typedef struct _GolemMarshallPrivate GolemMarshallPrivate;

struct _GolemMarshallClass
{
  GolemTypeClass parent_class;
};

struct _GolemMarshall
{
  GolemType parent_instance;

  GolemMarshallPrivate * priv;
};

GType		golem_marshall_get_type(void);

GolemType *	golem_marshall_get_return(GolemMarshall * marshall);

GolemType **	golem_marshall_get_arguments(GolemMarshall * marshall,
					     gsize * length);

#endif /* GOLEMMARSHAL_H_ */
