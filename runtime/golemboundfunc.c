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


#include "../golem.h"

struct _GolemBoundFuncPrivate {
  gpointer inst;
  GolemFunction * func;
};

static void
golem_bound_func_callable_interface_init (GolemCallableInterface *iface);

G_DEFINE_TYPE_WITH_CODE (GolemBoundFunc, golem_bound_func,G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (GOLEM_TYPE_CALLABLE,
						golem_bound_func_callable_interface_init))


static gboolean
golem_bound_func_call(GolemCallable * callable,
		      GolemValue * result,
		      guint8 argc,
		      GolemValue * argv,
		      GError ** error)
{

  GolemBoundFunc * bound_func = GOLEM_BOUND_FUNC(callable);
  return golem_function_call(bound_func->priv->func,
			     bound_func->priv->inst,
			     result,
			     argc,
			     argv,
			     error);
}

static void
golem_bound_func_dispose(GObject * object)
{
  GolemBoundFunc * bound_func = GOLEM_BOUND_FUNC(object);
  g_object_unref(bound_func->priv->func);
  g_object_unref(bound_func->priv->inst);
}

static void
golem_bound_func_init(GolemBoundFunc * self)
{
  self->priv = golem_bound_func_get_instance_private(self);
}

static void
golem_bound_func_callable_interface_init (GolemCallableInterface *iface)
{
  iface->call = golem_bound_func_call;
}

static void
golem_bound_func_class_init(GolemBoundFuncClass * klass)
{
  G_OBJECT_CLASS(klass)->dispose = golem_bound_func_dispose;
}

GolemBoundFunc *
golem_bound_func_new(GolemFunction * func,
		     gpointer inst)
{
  GolemBoundFunc * bound_func = GOLEM_BOUND_FUNC(
      g_object_new(GOLEM_TYPE_BOUND_FUNC,NULL));

  bound_func->priv->func = (GolemFunction*)g_object_ref(func);
  bound_func->priv->inst = g_object_ref(inst);
  return bound_func;
}
