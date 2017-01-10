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

typedef struct _GolemClosure GolemClosure;

struct _GolemBuilderClosurePrivate
{
  GList * names;
  GolemBlock * block;
};

struct _GolemClosure
{
  GClosure closure;
  GolemContext * parent;
  GolemBuilderClosure * self;
  GError * error;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuilderClosure,golem_builder_closure,GOLEM_TYPE_EXPRESSION)

static void
_golem_closure_free(gpointer data,GClosure * closure)
{
  GolemClosure * self = (GolemClosure*)closure;
  g_object_unref(self->self);
  g_object_unref(self->parent);
}

static void
_golem_closure_invoke(GClosure *closure,GValue *return_value,guint n_param_values,const GValue *param_values,gpointer invocation_hint,gpointer marshal_data)
{
  GError * error = NULL;
  GolemClosure * self = (GolemClosure*)closure;
  GolemContext * context = golem_context_new(self->parent);
  if(golem_context_declare(context,"_@return_",G_TYPE_NONE,&error))
    {

    }
  g_object_unref(context);
}

static gboolean
_golem_builder_closure_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemBuilderClosure * self = GOLEM_BUILDER_CLOSURE(expression);
  GolemClosure * closure = (GolemClosure*)g_closure_new_simple(sizeof(GolemClosure),NULL);
  closure->parent = GOLEM_CONTEXT(g_object_ref(context));
  closure->self = GOLEM_BUILDER_CLOSURE(g_object_ref(self));
  closure->error = NULL;
  g_closure_set_marshal((GClosure*)closure,_golem_closure_invoke);
  g_closure_add_finalize_notifier((GClosure*)closure,NULL,_golem_closure_free);
  g_value_init(result,G_TYPE_CLOSURE);
  g_value_set_boxed(result,closure);
  return TRUE;
}

static void
golem_builder_closure_init(GolemBuilderClosure * self)
{
  self->priv = golem_builder_closure_get_instance_private(self);
}


static void
golem_builder_closure_class_init(GolemBuilderClosureClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = _golem_builder_closure_evaluate;
}

