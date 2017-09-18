/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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

#ifndef GOLEM_MAP_H_
#define GOLEM_MAP_H_

#define GOLEM_TYPE_MAP (golem_map_get_type())
typedef struct _GolemMap GolemMap;


GType		golem_map_get_type(void);

GolemMap * 	golem_map_new();

gboolean	golem_map_get(GolemMap * map,const gchar * name,GValue * dest);

void		golem_map_set(GolemMap * map,const gchar * name,const GValue * src);

void		golem_map_unset(GolemMap * map,const gchar * name);

void		golem_map_reset(GolemMap * map);

GolemMap *	golem_map_ref(GolemMap * map);

void		golem_map_unref(GolemMap * map);


#endif /* GOLEM_MAP_H_ */
