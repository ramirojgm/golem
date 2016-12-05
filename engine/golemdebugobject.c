/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "golem.h"

typedef struct
{
  gchar * name;
}GolemDebugObjectPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GolemDebugObject,golem_debug_object,G_TYPE_OBJECT)

static void
golem_debug_object_dispose(GObject * instance)
{
  GolemDebugObjectPrivate * priv = golem_debug_object_get_instance_private(GOLEM_DEBUG_OBJECT(instance));
  g_print("dispose <%p as '%s'>\n",instance,priv->name);
  g_free(priv->name);
  G_OBJECT_CLASS(golem_debug_object_parent_class)->dispose(instance);
}

static void
golem_debug_object_init(GolemDebugObject * self)
{

}

static void
golem_debug_object_class_init(GolemDebugObjectClass * klass)
{
  G_OBJECT_CLASS(klass)->dispose = golem_debug_object_dispose;
}


GObject *
golem_debug_object_new(const gchar * name)
{
  GObject * self = G_OBJECT(g_object_new(GOLEM_TYPE_DEBUG_OBJECT,NULL));
  GolemDebugObjectPrivate * priv = golem_debug_object_get_instance_private(GOLEM_DEBUG_OBJECT(self));
  priv->name = g_strdup(name);
  g_print("create <%p as '%s'>\n",self,priv->name);
  return self;
}
