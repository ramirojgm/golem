/*
	Copyright (C) 2019 Ramiro Jose Garcia Moraga

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


#include "../golem.h"

G_DEFINE_INTERFACE (GolemIterable, golem_iterable,GOLEM_TYPE_ITERABLE)

static void
golem_iterable_default_init (GolemIterableInterface *iface)
{
  /* pass */
}


gboolean
golem_iterable_get_iter (GolemIterable * iterable)
{
    g_return_val_if_fail (GOLEM_IS_ITERABLE(iterable),FALSE);
    GolemIterableInterface *iface;
    iface = GOLEM_ITERABLE_GET_IFACE (iterable);
    g_return_val_if_fail (iface->get_iter != NULL,FALSE);
    return iface->get_iter(iterable);
}

