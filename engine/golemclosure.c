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
  GolemSymbol * self = (GolemSymbol*)closure;
  GType return_type = golem_closure_info_get_return_type(self->parent_boxed.info);
  GType fundamental_return_type = G_TYPE_FUNDAMENTAL(return_type);
  GolemArgs * args = golem_args_new();
  GList * cur_param = g_list_first(golem_closure_info_get_parameters(self->parent_boxed.info));
  const GValue * param_value = NULL;
  GolemClosureParameter * param_info = NULL;

  for(guint param_index = 0;param_index < n_param_values;param_index ++)
    {
      const GValue * param_value = param_values[param_index];
      if(cur_param)
	{
	  param_info = (GolemClosureParameter*)cur_param->data;
	  cur_param = g_list_next(cur_param);
	  if(param_info->is_catch)
	    {
	      golem_args_append_pointer(args,&(self->parent_boxed.error));
	      cur_param = g_list_next(cur_param);
	      if(cur_param)
		{
		  param_info = (GolemClosureParameter*)cur_param->data;
		  cur_param = g_list_next(cur_param);
		}
	      else
		{
		  param_info = NULL;
		}
	    }
	}
      else
	{
	  param_info = NULL;
	}

      if(param_info)
	{


	}
      else
	{
	  golem_args_append(args,param_value);
	}
    }

  switch(fundamental_return_type)
  {

  }

  golem_args_free(args);
}

void golem_symbol_finalizer(gpointer data,GClosure * closure)
{
  GolemSymbol * self = (GolemSymbol*)closure;
  if(self->parent_boxed.error)
    g_error_free(self->parent_boxed.error);

  if(self->parent_boxed.instance)
    g_object_unref(self->parent_boxed.instance);

  g_object_unref(self->parent_boxed.info);
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
