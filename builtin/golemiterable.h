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

#ifndef GOLEM_ITERABLE_H_
#define GOLEM_ITERABLE_H_


#define GOLEM_TYPE_ITERABLE (golem_iterable_get_type())
G_DECLARE_INTERFACE(GolemIterable,golem_iterable,GOLEM,ITERABLE,GObject)

typedef gboolean (*GolemIteratorStepFunc) (GolemIterator * iterator,
                                           GolemIterable * iterable,
                                           gpointer dest);

typedef void     (*GolemIteratorFreeFunc) (GolemIterator *iterator,
                                           GolemIterable *iterable);

typedef struct _GolemIterator GolemIterator;

struct _GolemIterator
{
  GolemIterable * iterable;
  GolemIteratorStepFunc step_func;
  GolemIteratorFreeFunc free_func;
};

struct _GolemIterableInterface
{
  GTypeInterface parent_iface;

  /* virtual */
  GolemIterator * (*get_iter)(GolemIterable * iterable);
};


GType		          golem_iterable_get_type(void);

GolemIterator * 	golem_iterable_get_iter(GolemIterable * iterable);


GolemIterator *   golem_iterator_new_full (GolemIterable         *iterable,
                                           gsize                  iter_size,
                                           GolemIteratorStepFunc  step_func,
                                           GolemIteratorFreeFunc  free_func);

#define           golem_iterator_new (iterable,iterator,step_func,free_fn) \
                  (iterator*)golem_iterator_new_full(iterable,sizeof(iterator)),step_func,free_func)

gboolean          golem_iterator_next(GolemIterator * iter, gpointer dest);

void              golem_iterator_free(GolemIterator * iter);

#endif /* GOLEM_ITERABLE_H */
