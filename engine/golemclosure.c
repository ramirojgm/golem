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
#include <stdlib.h>

struct _GolemClosureInfoPrivate
{
  gboolean	resolved;
  gchar *	name;
  gchar *	return_type_name;
  GType 	return_type;
  gboolean	return_const;
  GList * 	parameters;
};

typedef struct
{
  guint		signal_id;
}GolemSignalData;

typedef struct
{
  GolemClosureInfo * info;
  gpointer	     symbol_address;
}GolemSymbolData;

typedef struct
{
  GolemClosureInfo * info;
  GolemContext*	   context;
  GolemStatement * statement;
}GolemFunctionData;

static GolemClosure *
_golem_closure_copy(GolemClosure * closure)
{
  return GOLEM_CLOSURE(g_closure_ref(G_CLOSURE(closure)));
}

static void
_golem_closure_free(GolemClosure * closure)
{
  g_closure_unref(G_CLOSURE(closure));
}

G_DEFINE_TYPE_WITH_PRIVATE(GolemClosureInfo,golem_closure_info,G_TYPE_OBJECT)
G_DEFINE_BOXED_TYPE(GolemClosure,golem_closure,_golem_closure_copy,_golem_closure_free)

GolemClosureInvoke *
golem_closure_invoke_new()
{
  return g_new0(GolemClosureInvoke,1);
}

GolemClosureInvoke *
golem_closure_invoke_new_with_values(guint n_param_values,const GValue *param_values)
{
  GolemClosureInvoke * invoke = g_new0(GolemClosureInvoke,1);
  for(gint n_param = 0;n_param < n_param_values; n_param ++)
      golem_closure_invoke_push(invoke,&(param_values[n_param]));
  return invoke;
}

gsize
golem_closure_invoke_get_length(GolemClosureInvoke * closure_invoke)
{
  return g_list_length(closure_invoke->arguments);
}

void
golem_closure_invoke_push(GolemClosureInvoke * closure_invoke,const GValue * value)
{
  GValue * new_value = g_new0(GValue,1);
  g_value_init(new_value,G_VALUE_TYPE(value));
  g_value_copy(value,new_value);
  closure_invoke->arguments = g_list_append(closure_invoke->arguments,new_value);
  if(!closure_invoke->current)
    closure_invoke->current = g_list_first(closure_invoke->arguments);
}

void
golem_closure_invoke_rewind(GolemClosureInvoke * closure_invoke)
{
  closure_invoke->current = g_list_first(closure_invoke->arguments);
}

gboolean
golem_closure_invoke_next(GolemClosureInvoke * closure_invoke,GValue * value)
{
  if(closure_invoke->current)
    {
      GValue * current_value = (GValue*)closure_invoke->current->data;
      g_value_init(value,G_VALUE_TYPE(current_value));
      g_value_copy(current_value,value);
      closure_invoke->current = g_list_next(closure_invoke->current);
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

static GValue *
_golem_closure_invoke_get_value_at(GolemClosureInvoke * closure_invoke,gint index)
{
  GList * arguments = g_list_first(closure_invoke->arguments);
  guint n_arguments = g_list_length(closure_invoke->arguments);
  g_return_val_if_fail(index >= 0 && index < n_arguments,NULL);
  return (GValue*)g_list_nth_data(arguments,index);
}

void
golem_closure_invoke_get_value(GolemClosureInvoke * closure_invoke,gint index,GValue * value)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  if(argument)
    {
      g_value_init(value,G_VALUE_TYPE(argument));
      g_value_copy(argument,value);
    }
}

guchar
golem_closure_invoke_get_char(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_uchar(argument);
}

gint32
golem_closure_invoke_get_int(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_int(argument);
}

gint64
golem_closure_invoke_get_int64(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_int64(argument);
}

gfloat
golem_closure_invoke_get_float(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_float(argument);
}

gdouble
golem_closure_invoke_get_double(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_double(argument);
}

gpointer
golem_closure_invoke_get_pointer(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_pointer(argument);
}

gpointer
golem_closure_invoke_get_boxed(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_boxed(argument);
}


gpointer
golem_closure_invoke_get_object(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_object(argument);
}

const gchar *
golem_closure_invoke_get_string(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_string(argument);
}

void
golem_closure_invoke_set_error(GolemClosureInvoke * closure_invoke,GError * error)
{
  if(closure_invoke->error)
    g_error_free(closure_invoke->error);
  closure_invoke->error = error;
}

GError *
golem_closure_invoke_get_error(GolemClosureInvoke * closure_invoke)
{
  return closure_invoke->error;
}

void
golem_closure_invoke_set_result(GolemClosureInvoke * closure_invoke,const GValue * value)
{
  g_value_unset(&(closure_invoke->result));
  g_value_init(&(closure_invoke->result),G_VALUE_TYPE(value));
  g_value_copy(value,&(closure_invoke->result));
}

void
golem_closure_invoke_get_result(GolemClosureInvoke * closure_invoke,GValue * value)
{
  g_value_init(value,G_VALUE_TYPE(&(closure_invoke->result)));
  g_value_copy(&(closure_invoke->result),value);
}

void
golem_closure_invoke_free(GolemClosureInvoke * closure_invoke)
{
  g_list_free_full(closure_invoke->arguments,(GDestroyNotify)g_value_free);
  if(closure_invoke->error)
    g_free(closure_invoke->error);
  g_value_unset(&closure_invoke->result);
}


static void
golem_closure_finalizer(gpointer data,GClosure * closure)
{
  GolemClosure * self = GOLEM_CLOSURE(closure);

  if(self->context_type == GOLEM_CLOSURE_CONTEXT_INSTANCED)
    g_object_unref(self->context.instance);

  if(self->finalize_func)
    self->finalize_func(self,data);
}

static void
golem_closure_marshal(GClosure *closure,
                    GValue *return_value,
                    guint n_param_values,
                    const GValue *param_values,
                    gpointer invocation_hint,
                    gpointer marshal_data)
{
  GolemClosure * self = GOLEM_CLOSURE(closure);
  GolemClosureInvoke * invoke = golem_closure_invoke_new_with_values(n_param_values,param_values);
  if(!self->invoke_func(self,invoke,marshal_data))
    {
      GError * error = golem_closure_invoke_get_error(invoke);
      g_error("%s",error->message);
      g_error_free(error);
    }
  golem_closure_invoke_get_result(invoke,return_value);
  golem_closure_invoke_free(invoke);
}

/*static void
golem_symbol_invoke (GolemClosure *closure,
                    GValue *return_value,
                    guint n_param_values,
                    const GValue *param_values,
                    GError ** error)
{
  GolemSymbol * self = GOLEM_SYMBOL(closure);
  gboolean 	done = TRUE;
  GObjectClass * klass = NULL;
  GType 	return_type = golem_closure_info_get_return_type(self->parent_boxed.info);
  GType 	fundamental_return_type = G_TYPE_FUNDAMENTAL(return_type);
  GolemStructBuilder * 	args = golem_struct_builder_new();
  GList * 	cur_param = g_list_first(golem_closure_info_get_parameters(self->parent_boxed.info));
  GValue * param_value = NULL;
  GolemClosureParameter * param_info = NULL;
  guint param_index = 0;

  //use first parameter for instance
  if(self->parent_boxed.context_type == GOLEM_CLOSURE_CONTEXT_INSTANCED)
    {
      golem_struct_builder_append_pointer(args,self->parent_boxed.context.instance);
    }

  //use first parameter for class
  if(self->parent_boxed.context_type == GOLEM_CLOSURE_CONTEXT_CLASSED)
    {
      klass = g_type_class_ref(self->parent_boxed.context.class_type);
      golem_struct_builder_append_pointer(args,klass);
    }

  //set parameters
  for(param_index = 0;param_index < n_param_values;param_index ++)
    {
      param_value = (GValue*)&(param_values[param_index]);
      if(cur_param)
	{
	  param_info = (GolemClosureParameter*)cur_param->data;
	  cur_param = g_list_next(cur_param);
	  if(param_index == self->parent_boxed.info->throw_at)
	    {
		golem_struct_builder_append_pointer(args,error);
	    }
	}
      else
	{
	  param_info = NULL;
	}

      if(param_info)
	{
	  //declared parameter
	  if(param_info->is_reference)
	    {
	      golem_struct_builder_append_pointer(args,&(param_value->data[0].v_pointer));
	    }
	  else if((G_VALUE_TYPE(param_value) == param_info->type )||(g_type_is_a(G_VALUE_TYPE(param_value),param_info->type)))
	    {
	      golem_struct_builder_append(args,param_value);
	    }
	  else if(param_info->type == G_TYPE_VALUE)
	    {
	      GValue * new_value = g_new0(GValue,0);
	      g_value_init(new_value,G_VALUE_TYPE(param_value));
	      g_value_copy(param_value,new_value);
	      g_value_unset(param_value);
	      g_value_init(param_value,G_TYPE_VALUE);
	      g_value_take_boxed(param_value,new_value);
	      golem_struct_builder_append(args,param_value);
	    }
	  else if(g_value_type_transformable(G_VALUE_TYPE(param_value), param_info->type))
	    {
	      GValue transformed = G_VALUE_INIT;
	      g_value_init(&transformed,param_info->type);
	      g_value_transform(param_value,&transformed);
	      g_value_unset(param_value);
	      g_value_copy(&transformed,param_value);
	      g_value_unset(&transformed);
	      golem_struct_builder_append(args,param_value);
	    }
	  else
	    {
	      done = FALSE;
	      golem_throw(error,
		  GOLEM_INVALID_CAST_ERROR,
		  "can't transform from '%s' to '%s'",
		  g_type_name(G_VALUE_TYPE(param_value)),
		  g_type_name(param_info->type));
	      break;
	    }
	}
      else
	{
	  //extra parameter
	  golem_struct_builder_append(args,param_value);
	}
    }

  //set empty parameters
  while(cur_param)
    {
      if(param_index == self->parent_boxed.info->throw_at)
	{
	  golem_struct_builder_append_pointer(args,error);
	}
      param_info = (GolemClosureParameter*)cur_param->data;
      GValue empty_pass = G_VALUE_INIT;
      g_value_init(&empty_pass,param_info->type);
      golem_struct_builder_append(args,&empty_pass);
      cur_param = g_list_next(cur_param);
      param_index++;
    }

  //check last parameter is throw at
  if(param_index == self->parent_boxed.info->throw_at)
    {
      golem_struct_builder_append_pointer(args,error);
    }

  if(done)
    {
      g_value_unset(return_value);
      if(self->parent_boxed.info->return_type != G_TYPE_NONE)
	g_value_init(return_value,return_type);
      switch(fundamental_return_type)
      {
	case G_TYPE_CHAR:
	  g_value_set_schar(return_value,golem_invoke_gint8(self->symbol_address,args));
	  break;
	case G_TYPE_INT:
	  g_value_set_int(return_value,golem_invoke_gint(self->symbol_address,args));
	  break;
	case G_TYPE_INT64:
	  g_value_set_int64(return_value,golem_invoke_gint64(self->symbol_address,args));
	  break;
	case G_TYPE_LONG:
	  g_value_set_long(return_value,golem_invoke_glong(self->symbol_address,args));
	  break;
	case G_TYPE_UCHAR:
	  g_value_set_uchar(return_value,golem_invoke_guint8(self->symbol_address,args));
	  break;
	case G_TYPE_UINT:
	  g_value_set_uint(return_value,golem_invoke_guint(self->symbol_address,args));
	  break;
	case G_TYPE_UINT64:
	  g_value_set_uint64(return_value,golem_invoke_guint64(self->symbol_address,args));
	  break;
	case G_TYPE_ULONG:
	  g_value_set_ulong(return_value,golem_invoke_gulong(self->symbol_address,args));
	  break;
	case G_TYPE_FLOAT:
	  g_value_set_float(return_value,golem_invoke_gfloat(self->symbol_address,args));
	  break;
	case G_TYPE_DOUBLE:
	  g_value_set_double(return_value,golem_invoke_gdouble(self->symbol_address,args));
	  break;
	case G_TYPE_BOXED:
	  if(self->parent_boxed.info->return_const)
	    g_value_set_boxed(return_value,golem_invoke_gpointer(self->symbol_address,args));
	  else
	    g_value_take_boxed(return_value,golem_invoke_gpointer(self->symbol_address,args));
	  break;
	case G_TYPE_OBJECT:
	  {
	    gpointer instance = golem_invoke_gpointer(self->symbol_address,args);
	    if(self->parent_boxed.info->return_const)
	      g_value_set_object(return_value,instance);
	    else
	      g_value_take_object(return_value,instance);
	  }
	  break;
	case G_TYPE_STRING:
	  if(self->parent_boxed.info->return_const)
	    g_value_set_string(return_value,golem_invoke_gpointer(self->symbol_address,args));
	  else
	    g_value_take_string(return_value,golem_invoke_gpointer(self->symbol_address,args));
	  break;
	case G_TYPE_POINTER:
	  g_value_set_pointer(return_value,golem_invoke_gpointer(self->symbol_address,args));
	  break;
	default:
	  golem_invoke(self->symbol_address,args);
      }
    }
  golem_struct_builder_free(args);

  if(klass)
    g_type_class_unref(klass);
}

void golem_symbol_finalizer(gpointer data,GClosure * closure)
{
  GolemSymbol * self = GOLEM_SYMBOL(closure);
  if(self->parent_boxed.context_type == GOLEM_CLOSURE_CONTEXT_INSTANCED)
    {
      g_object_unref(self->parent_boxed.context.instance);
    }
  g_object_unref(self->parent_boxed.info);
}
*/

static gboolean
golem_function_invoke (GolemClosure *closure,
		       GolemClosureInvoke * invoke,
		       gpointer data)
{
  gboolean done = TRUE;
  GolemFunctionData * func_data = (GolemFunctionData*)data;
  GolemContext * this_context = golem_context_new(func_data->context);
  GolemClosureInfo * info = func_data->info;
  GError * error = NULL;
  GList * cur_param = golem_closure_info_get_parameters(info);
  GolemClosureParameter * param_info = NULL;
  guint param_index = 0;
  gint n_param_values = golem_closure_invoke_get_length(invoke);

  golem_context_declare(this_context,"::return::",G_TYPE_VALUE,NULL);

  for(param_index = 0;param_index < n_param_values;param_index ++)
    {
      GValue param_value = G_VALUE_INIT;
      if(cur_param)
      {
	param_info = (GolemClosureParameter*)cur_param->data;
	cur_param = g_list_next(cur_param);
      }
      else
      {
	param_info = NULL;
      }

      if(param_info)
      {
	g_value_unset(&param_value);
	g_value_init(&param_value,param_info->type);
	golem_closure_invoke_get_value(invoke,param_index,&param_value);

	if((G_VALUE_TYPE(&param_value) == param_info->type )||(g_type_is_a(G_VALUE_TYPE(&param_value),param_info->type)))
	  {
	    golem_context_set_auto(this_context,param_info->name,&param_value,NULL);
	  }
	else if(param_info->type == G_TYPE_VALUE)
	  {
	    GValue * new_value = g_new0(GValue,0);
	    g_value_init(new_value,G_VALUE_TYPE(&param_value));
	    g_value_copy(&param_value,new_value);
	    g_value_unset(&param_value);
	    g_value_init(&param_value,G_TYPE_VALUE);
	    g_value_take_boxed(&param_value,new_value);
	    golem_context_set_auto(this_context,param_info->name,&param_value,NULL);
	  }
	else if(g_value_type_transformable(G_VALUE_TYPE(&param_value), param_info->type))
	  {
	    GValue transformed = G_VALUE_INIT;
	    g_value_unset(&transformed);
	    g_value_init(&transformed,param_info->type);
	    g_value_transform(&param_value,&transformed);
	    g_value_unset(&param_value);
	    g_value_init(&param_value,param_info->type);
	    g_value_copy(&transformed,&param_value);
	    g_value_unset(&transformed);
	    golem_context_set_auto(this_context,param_info->name,&param_value,NULL);
	  }
	else
	  {
	    error = g_error_new(
		GOLEM_ERROR,
		GOLEM_INVALID_CAST_ERROR,
		"can't transform from '%s' to '%s'",
		g_type_name(G_VALUE_TYPE(&param_value)),
		g_type_name(param_info->type)
	    );
	    done = FALSE;
	    break;
	  }
	}
      else
	{
	  //extra parameter
	}
      g_value_unset(&param_value);
    }

  if(done)
      done = golem_statement_execute(func_data->statement,this_context,&error);

  if(done)
    {
      golem_closure_invoke_set_error(invoke,error);
    }
  else
    {
      GValue return_value = G_VALUE_INIT;
      golem_context_get(this_context,"::return::",&return_value,NULL);
      golem_closure_invoke_set_result(invoke,&return_value);
      g_value_unset(&return_value);
    }
  g_object_unref(this_context);
  return done;
}

static void
golem_function_finalizer(GolemClosure * closure,gpointer data)
{
  GolemFunctionData * func_data = (GolemFunctionData*)data;
  g_object_unref(func_data->info);
  g_object_unref(func_data->context);
  g_object_unref(func_data->statement);
  g_free(func_data);
}

/*

void golem_signal_invoke (GClosure *closure,
                    GValue *return_value,
                    guint n_param_values,
                    const GValue *param_values,
                    gpointer invocation_hint,
                    gpointer marshal_data)
{
  g_print("try invoke");
}

void golem_signal_finalizer(gpointer data,GClosure * closure)
{

}



GolemClosure *
golem_symbol_new(GolemClosureInfo * info,gpointer symbol_address)
{
  GolemSymbol  * symbol = GOLEM_SYMBOL(g_closure_new_simple(sizeof(GolemSymbol),NULL));
  symbol->parent_boxed.info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  symbol->symbol_address = symbol_address;
  symbol->parent_boxed.type = GOLEM_CLOSURE_SYMBOL;
  symbol->parent_boxed.context_type = GOLEM_CLOSURE_CONTEXT_NONE;
  symbol->parent_boxed.context.class_type = G_TYPE_NONE;
  symbol->parent_boxed.context.instance = NULL;
  symbol->parent_boxed.callback = golem_symbol_invoke;
  g_closure_set_marshal(G_CLOSURE(symbol),golem_closure_marshal);
  g_closure_add_finalize_notifier(G_CLOSURE(symbol),NULL,golem_symbol_finalizer);
  return GOLEM_CLOSURE(symbol);
}

GolemClosure *
golem_symbol_instanced_new(GolemClosureInfo * info,gpointer symbol_address,gpointer instance)
{
  GolemSymbol  * symbol = GOLEM_SYMBOL(g_closure_new_simple(sizeof(GolemSymbol),NULL));
  symbol->parent_boxed.info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  symbol->symbol_address = symbol_address;
  symbol->parent_boxed.type = GOLEM_CLOSURE_SYMBOL;
  symbol->parent_boxed.context_type = GOLEM_CLOSURE_CONTEXT_INSTANCED;
  symbol->parent_boxed.context.class_type = G_TYPE_NONE;
  symbol->parent_boxed.context.instance = g_object_ref(instance);
  symbol->parent_boxed.callback = golem_symbol_invoke;
  g_closure_set_marshal(G_CLOSURE(symbol),golem_closure_marshal);
  g_closure_add_finalize_notifier(G_CLOSURE(symbol),NULL,golem_symbol_finalizer);
  return GOLEM_CLOSURE(symbol);
}

GolemClosure *
golem_symbol_static_new(GolemClosureInfo * info,gpointer symbol_address,GType type_class)
{
  GolemSymbol  * symbol = GOLEM_SYMBOL(g_closure_new_simple(sizeof(GolemSymbol),NULL));
  symbol->parent_boxed.info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  symbol->symbol_address = symbol_address;
  symbol->parent_boxed.type = GOLEM_CLOSURE_SYMBOL;
  symbol->parent_boxed.context_type = GOLEM_CLOSURE_CONTEXT_CLASSED;
  symbol->parent_boxed.context.class_type = type_class;
  symbol->parent_boxed.context.instance = NULL;
  symbol->parent_boxed.callback = golem_symbol_invoke;
  g_closure_set_marshal(G_CLOSURE(symbol),golem_closure_marshal);
  g_closure_add_finalize_notifier(G_CLOSURE(symbol),NULL,golem_symbol_finalizer);
  return GOLEM_CLOSURE(symbol);
}
*/


GolemClosure *
golem_closure_new(GolemClosureInvokeFunc invoke_func,GolemClosureFinalizeFunc finalize_func,gpointer data)
{
  GolemClosure  * closure = GOLEM_CLOSURE(g_closure_new_simple(sizeof(GolemClosure),NULL));
  closure->context_type = GOLEM_CLOSURE_CONTEXT_NONE;
  closure->context.class_type = G_TYPE_NONE;
  closure->context.instance = NULL;
  closure->invoke_func = invoke_func;
  closure->finalize_func = finalize_func;
  closure->data = data;
  g_closure_set_meta_marshal(G_CLOSURE(closure),data,golem_closure_marshal);
  g_closure_add_finalize_notifier(G_CLOSURE(closure),data,golem_closure_finalizer);
  return closure;
}

void
golem_closure_set_instance(GolemClosure * closure,gpointer instance)
{
  g_return_if_fail(closure->context_type != GOLEM_CLOSURE_CONTEXT_NONE);
  closure->context_type = GOLEM_CLOSURE_CONTEXT_INSTANCED;
  closure->context.instance = g_object_ref(instance);
}

gpointer
golem_closure_get_instance(GolemClosure * closure)
{
  g_return_val_if_fail(closure->context_type == GOLEM_CLOSURE_CONTEXT_INSTANCED,NULL);
  return closure->context.instance;
}

void
golem_closure_set_class(GolemClosure * closure,GType klass)
{
  g_return_if_fail(closure->context_type != GOLEM_CLOSURE_CONTEXT_NONE);
  closure->context_type = GOLEM_CLOSURE_CONTEXT_CLASSED;
  closure->context.class_type = klass;
}

GType
golem_closure_get_class(GolemClosure * closure)
{
  g_return_val_if_fail(closure->context_type == GOLEM_CLOSURE_CONTEXT_CLASSED,G_TYPE_NONE);
  return closure->context.class_type;
}

GTypeClass *
golem_closure_get_type_class(GolemClosure * closure)
{
  g_return_val_if_fail(closure->context_type == GOLEM_CLOSURE_CONTEXT_CLASSED,NULL);
  return g_type_class_peek(closure->context.class_type);
}

gpointer
golem_closure_hold_address(GolemClosure * closure)
{
  return NULL;
}

void
golem_closure_release_address(GolemClosure * closure,gpointer native_address)
{

}

gboolean
golem_closure_invoke(GolemClosure * closure,GolemClosureInvoke * invoke)
{
  if(closure->invoke_func)
    {
      return closure->invoke_func(closure,invoke,closure->data);
    }
  else
    {
      golem_closure_invoke_set_error(
	  invoke,
	  g_error_new(
	      GOLEM_ERROR,
	      GOLEM_NOT_IMPLEMENTED_ERROR,
	      "not implemented yet"
	      ));
      return FALSE;
    }
}

GolemClosure *
golem_function_new(GolemClosureInfo * info,GolemContext * context,GolemStatement * statement)
{
  GolemFunctionData * func = g_new0(GolemFunctionData,1);
  func->info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  func->context = GOLEM_CONTEXT(g_object_ref(context));
  func->statement = GOLEM_STATEMENT(g_object_ref(statement));
  GolemClosure * closure = golem_closure_new(golem_function_invoke,golem_function_finalizer,func);
  return GOLEM_CLOSURE(closure);
}


static void
golem_closure_info_init(GolemClosureInfo * self)
{
  self->priv = golem_closure_info_get_instance_private(self);
}

static void
golem_closure_info_class_init(GolemClosureInfoClass * klass)
{

}

GolemClosureInfo *
golem_closure_info_parse(GolemParser * parser,GError ** error)
{
  GolemClosureInfo *  info = GOLEM_CLOSURE_INFO(g_object_new(GOLEM_TYPE_CLOSURE_INFO,NULL));
  gboolean done = TRUE;
  if(golem_parser_next_word_check(parser,"const"))
    {
      info->priv->return_const = TRUE;
    }

  if(golem_parser_check_is_named(parser))
    {
      info->priv->return_type_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
      if(golem_parser_check_is_named(parser))
	{
	  info->priv->name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
	  if(golem_parser_next_word_check(parser,"("))
	    {
	      while(!golem_parser_next_word_check(parser,")"))
		{
		  const gchar * type_name, *name;
		  if(golem_parser_check_is_named(parser))
		    {
		      type_name = golem_parser_next_word(parser,NULL,TRUE);

		      if(golem_parser_check_is_named(parser))
			{
			  name = golem_parser_next_word(parser,NULL,TRUE);
			  if(done)
			    {
			      GolemClosureParameter * param = g_new0(GolemClosureParameter,1);
			      param->name = g_strdup(name);
			      param->type_name = g_strdup(type_name);
			      param->type = G_TYPE_NONE;
			      info->priv->parameters = g_list_append(info->priv->parameters,param);
			      if(!golem_parser_next_word_check(parser,",") && !golem_parser_is_next_word(parser,")"))
				{
				  done = FALSE;
				  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected \",\" or \")\"");
				}
			    }
			}
		      else
			{
			  done = FALSE;
			  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"the name of the parameter was expected");
			}
		    }
		  else
		    {
		      done = FALSE;
		      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"the type of the parameter was expected");
		    }

		  if(!done)
		    break;
		}
	    }
	  else
	    {
	      done = FALSE;
	      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"expected \"(\"");
	    }
	}
      else
	{
	  done = FALSE;
	  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"expected the function name");
	}
    }
  else
    {
      done = FALSE;
      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"expected a type");
    }

  if(!done)
    {
      g_object_unref(info);
      info = NULL;
    }
  return info;
}

GolemClosureInfo *
golem_closure_info_parse_anonymous(GolemParser * parser,GError ** error)
{
  GolemClosureInfo *  info = GOLEM_CLOSURE_INFO(g_object_new(GOLEM_TYPE_CLOSURE_INFO,NULL));
  static volatile guint64 anonymous_id = 0;
  gboolean done = TRUE;
  info->priv->return_type_name = NULL;
  info->priv->name = g_strdup_printf("anonymous%ld",anonymous_id);
  anonymous_id++;

  if(golem_parser_next_word_check(parser,"("))
    {
      while(!golem_parser_next_word_check(parser,")"))
	{
	  const gchar * type_name, *name;
	  if(golem_parser_check_is_named(parser))
	    {
	      type_name = golem_parser_next_word(parser,NULL,TRUE);
	      if(golem_parser_check_is_named(parser))
		{
		  name = golem_parser_next_word(parser,NULL,TRUE);
		  if(done)
		    {
		      GolemClosureParameter * param = g_new0(GolemClosureParameter,1);
		      param->name = g_strdup(name);
		      param->type_name = g_strdup(type_name);
		      param->type = G_TYPE_NONE;
		      info->priv->parameters = g_list_append(info->priv->parameters,param);
		      if(!golem_parser_next_word_check(parser,",") && !golem_parser_is_next_word(parser,")"))
			{
			  done = FALSE;
			  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected \",\" or \")\"");
			}
		    }
		}
	      else
		{
		  done = FALSE;
		  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"the name of the parameter was expected");
		}
	    }
	  else
	    {
	      done = FALSE;
	      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"the type of the parameter was expected");
	    }

	  if(!done)
	    break;
	}
    }
  else
    {
      done = FALSE;
      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"expected \"(\"");
    }

  if(!done)
    {
      g_object_unref(info);
      info = NULL;
    }
  return info;
}

gboolean
golem_closure_info_resolve(GolemClosureInfo * info,GolemContext * context,GError ** error)
{
  gboolean done = TRUE;
  const gchar * type_unresolved = NULL;
  if(!info->priv->resolved)
    {
      if(info->priv->return_type_name)
	{
	  if(!(info->priv->return_type = golem_resolve_type_name(context,info->priv->return_type_name)))
	    {
	      done =  FALSE;
	      type_unresolved = info->priv->return_type_name;
	    }
	  else
	    {
	      g_clear_pointer(&(info->priv->return_type_name),g_free);
	    }
	}

      if(done)
	{
	  for(GList * params = g_list_first(info->priv->parameters);params;params = g_list_next(params))
	    {
	      GolemClosureParameter * param = (GolemClosureParameter*)params->data;
	      if(param->type_name)
		{
		  if(!(param->type = golem_resolve_type_name(context,param->type_name)))
		    {
		      done = FALSE;
		      type_unresolved = param->type_name;
		      break;
		    }
		  else
		    {
		      g_clear_pointer(&(param->type_name),g_free);
		    }
		}
	    }

	  if(done)
	    info->priv->resolved = TRUE;
	  else
	    golem_throw(error,GOLEM_UNKNOWN_TYPE_ERROR,"unknown type \"%s\"",type_unresolved);
	}
    }
  return done;
}

const gchar *
golem_closure_info_get_name(GolemClosureInfo * info)
{
  return info->priv->name;
}

GType
golem_closure_info_get_return_type(GolemClosureInfo * info)
{
  return info->priv->return_type;
}

GList *
golem_closure_info_get_parameters(GolemClosureInfo * info)
{
  return g_list_first(info->priv->parameters);
}
