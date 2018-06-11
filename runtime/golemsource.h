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

#ifndef GOLEMSOURCE_H_
#define GOLEMSOURCE_H_

#define GOLEM_TYPE_SOURCE (golem_source_get_type())
G_DECLARE_INTERFACE (GolemSource, golem_source, GOLEM, SOURCE, GObject)

struct _GolemSourceInterface
{
  GTypeInterface parent_iface;


};


#endif /* GOLEMAPPLICATIONCONTEXT_H_ */
