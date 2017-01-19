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

G_DEFINE_BOXED_TYPE(GolemClosure,golem_closure,g_closure_ref,g_closure_unref)
G_DEFINE_BOXED_TYPE(GolemSymbol,golem_symbol,g_closure_ref,g_closure_unref)
G_DEFINE_BOXED_TYPE(GolemFunction,golem_function,g_closure_ref,g_closure_unref)

void golem_symbol_invoke (GClosure *closure,
                    GValue *return_value,
                    guint n_param_values,
                    const GValue *param_values,
                    gpointer invocation_hint,
                    gpointer marshal_data)
{

}

void golem_symbol_finalizer(gpointer data,GClosure * closure)
{

}

void golem_function_invoke (GClosure *closure,
                    GValue *return_value,
                    guint n_param_values,
                    const GValue *param_values,
                    gpointer invocation_hint,
                    gpointer marshal_data)
{

}

void golem_function_finalizer(gpointer data,GClosure * closure)
{

}

void golem_signal_invoke (GClosure *closure,
                    GValue *return_value,
                    guint n_param_values,
                    const GValue *param_values,
                    gpointer invocation_hint,
                    gpointer marshal_data)
{

}

void golem_signal_finalizer(gpointer data,GClosure * closure)
{

}

GolemClosure *
golem_symbol_new(GolemClosureInfo * info,gpointer symbol_address)
{
  GolemSymbol  * symbol = g_closure_new_simple(sizeof(GolemSymbol),NULL);
  symbol->parent_boxed.info = G_CLOSURE_INFO(g_object_ref(info));
  symbol->symbol_address = symbol_address;
  g_closure_set_marshal((GClosure*)symbol,golem_symbol_invoke);
  g_closure_add_finalize_notifier((GClosure*symbol),NULL,golem_symbol_finalizer);
  return (GolemClosure*)symbol;
}

GolemClosure *
golem_symbol_instanced_new(GolemClosureInfo * info,gpointer symbol_address,gpointer instance)
{
  GolemSymbol * symbol = g_closure_new_simple(sizeof(GolemSymbol),NULL);
  symbol->parent_boxed.info = G_CLOSURE_INFO(g_object_ref(info));

  g_closure_set_marshal(((GClosure*)symbol),golem_symbol_invoke);
  g_closure_add_finalize_notifier(((GClosure*)symbol),NULL,golem_symbol_finalizer);
}

GolemClosure *
golem_symbol_static_new(GolemClosureInfo * info,gpointer symbol_address,GType type_class)
{

}

GolemClosure *
golem_function_new(GolemClosureInfo * info,GolemContext * context,GolemSentence * sentence)
{

}

GolemClosure *
golem_function_instanced_new(GolemClosureInfo * info,GolemContext * context,GolemSentence * sentence,gpointer instance)
{

}

GolemClosure *
golem_function_static_new(GolemClosureInfo * info,GolemContext * context,GolemSentence * sentence,GType type_class)
{

}

GolemClosure *
golem_signal_new(gpointer instance,guint signal_id)
{

}
