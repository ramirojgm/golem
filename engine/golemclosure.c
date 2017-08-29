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

GType
golem_closure_invoke_get_gtype(GolemClosureInvoke * closure_invoke,gint index)
{
  GValue * argument = _golem_closure_invoke_get_value_at(closure_invoke,index);
  return g_value_get_gtype(argument);
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
  if(G_VALUE_TYPE(&(closure_invoke->result)) != 0)
    {
      g_value_init(value,G_VALUE_TYPE(&(closure_invoke->result)));
      g_value_copy(&(closure_invoke->result),value);
      if(G_VALUE_HOLDS_BOXED(value)){
      	  g_print("<Boxed: %p>\n",g_value_get_boxed(&(closure_invoke->result)));
      }
    }
  else
    {
      g_value_init(value,G_TYPE_INT);
      g_value_set_int(value,0);
    }
}

void
golem_closure_invoke_free(GolemClosureInvoke * closure_invoke)
{
  g_list_free_full(closure_invoke->arguments,(GDestroyNotify)g_value_free);
  if(closure_invoke->error)
    g_error_free(closure_invoke->error);
  g_value_unset(&closure_invoke->result);
}


static void
golem_closure_finalizer(gpointer data,GClosure * closure)
{
  GolemClosure * self = GOLEM_CLOSURE(closure);
  if(self->finalize_func)
    self->finalize_func(self,data);
  g_value_unset(&self->this_value);
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
  if(return_value)
    golem_closure_invoke_get_result(invoke,return_value);
  golem_closure_invoke_free(invoke);
}


static gboolean
golem_function_invoke (GolemClosure *closure,
		       GolemClosureInvoke * invoke,
		       gpointer data)
{
  gboolean done = TRUE;
  GolemFunctionData * func_data = (GolemFunctionData*)data;
  GolemClosureInfo * info = func_data->info;
  GError * error = NULL;
  GList * cur_param = golem_closure_info_get_parameters(info);
  GolemClosureParameter * param_info = NULL;

  GolemRuntime * runtime = golem_runtime_new(func_data->context);
  guint param_index = 0;
  gint n_param_values = golem_closure_invoke_get_length(invoke);

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
	golem_closure_invoke_get_value(invoke,param_index,&param_value);

	if((G_VALUE_TYPE(&param_value) == param_info->type )||(g_type_is_a(G_VALUE_TYPE(&param_value),param_info->type)))
	  {
	    golem_context_set_auto(golem_runtime_get_context(runtime),param_info->name,&param_value,NULL);
	  }
	else if(param_info->type == G_TYPE_VALUE)
	  {
	    golem_context_set_auto(golem_runtime_get_context(runtime),param_info->name,&param_value,NULL);
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
	    golem_context_set_auto(golem_runtime_get_context(runtime),param_info->name,&param_value,NULL);
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
      done = golem_statement_execute(func_data->statement,runtime,&error);

  if(!done && error)
    {
      g_print("%s",error->message);
      golem_closure_invoke_set_error(invoke,error);
    }
  else
    {
      GValue return_value = G_VALUE_INIT;
      if(!golem_runtime_get_return(runtime,&return_value))
	{
	  g_value_init(&return_value,G_TYPE_POINTER);
	  g_value_set_pointer(&return_value,NULL);
	}

      golem_closure_invoke_set_result(invoke,&return_value);
      g_value_unset(&return_value);
    }
  golem_runtime_destroy(runtime);
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

static gboolean
golem_symbol_invoke (GolemClosure *closure,
		     GolemClosureInvoke * invoke,
		     gpointer data)
{
  gboolean done = TRUE;
  GolemSymbolData * func_data = (GolemSymbolData*)data;
  GolemClosureInfo * info = func_data->info;
  GolemCInvoke * cinvoke = golem_cinvoke_new(info->priv->return_type,info->priv->return_const);
  GList * cur_param = golem_closure_info_get_parameters(info);
  GError * error = NULL;

  GolemClosureParameter * param_info = NULL;
  guint param_index = 0;
  gint n_param_values = golem_closure_invoke_get_length(invoke);

  GValue * param_values = g_new0(GValue,n_param_values);
  if(closure->this_value.g_type)
    {
      if(G_VALUE_HOLDS_GTYPE(&closure->this_value))
	{
	  GTypeClass * klass = g_type_class_peek(g_value_get_gtype(&closure->this_value));
	  golem_cinvoke_push_pointer(cinvoke,klass);
	}
      else
	{
	  golem_cinvoke_push_value(cinvoke,&closure->this_value);
	}
    }

  for(param_index = 0;param_index < n_param_values;param_index ++)
    {
      GValue * param_value = &(param_values[param_index]);
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
	g_value_unset(param_value);
	golem_closure_invoke_get_value(invoke,param_index,param_value);
	if((G_VALUE_TYPE(param_value) == param_info->type )||(g_type_is_a(G_VALUE_TYPE(param_value),param_info->type)))
	  {
	    golem_cinvoke_push_value(cinvoke,param_value);
	  }
	else if(param_info->type == G_TYPE_VALUE)
	  {
	    GValue * new_value = g_new0(GValue,0);
	    g_value_init(new_value,G_VALUE_TYPE(param_value));
	    g_value_copy(param_value,new_value);
	    g_value_unset(param_value);
	    g_value_init(param_value,G_TYPE_VALUE);
	    g_value_take_boxed(param_value,new_value);
	    golem_cinvoke_push_value(cinvoke,param_value);
	  }
	else if(g_value_type_transformable(G_VALUE_TYPE(&param_value), param_info->type))
	  {
	    GValue transformed = G_VALUE_INIT;
	    g_value_unset(&transformed);
	    g_value_init(&transformed,param_info->type);
	    g_value_transform(param_value,&transformed);
	    g_value_unset(param_value);
	    g_value_init(param_value,param_info->type);
	    g_value_copy(&transformed,param_value);
	    g_value_unset(&transformed);
	    golem_cinvoke_push_value(cinvoke,param_value);
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
	  g_value_unset(param_value);
	  golem_closure_invoke_get_value(invoke,param_index,param_value);
	  golem_cinvoke_push_value(cinvoke,param_value);
	}
    }

  GValue result_value = G_VALUE_INIT;
  if(done)
    {
      golem_cinvoke_invoke(cinvoke,func_data->symbol_address,&result_value);
      golem_closure_invoke_set_result(invoke,&result_value);
      g_value_unset(&result_value);
    }
  else
    {
      g_print("error");
      golem_closure_invoke_set_error(invoke,error);
    }

  for(param_index = 0;param_index < n_param_values;param_index ++)
    g_value_unset(&param_values[param_index]);
  g_free(param_values);
  golem_cinvoke_free(cinvoke);
  return done;
}

static void
golem_symbol_finalizer(GolemClosure * closure,gpointer data)
{
  GolemSymbolData * func_data = (GolemSymbolData*)data;
  g_object_unref(func_data->info);
  g_free(func_data);
}


GolemClosure *
golem_closure_new(GolemClosureInvokeFunc invoke_func,GolemClosureFinalizeFunc finalize_func,gpointer data)
{
  GolemClosure  * closure = GOLEM_CLOSURE(g_closure_new_simple(sizeof(GolemClosure),NULL));
  closure->invoke_func = invoke_func;
  closure->finalize_func = finalize_func;
  closure->data = data;
  g_closure_set_meta_marshal(G_CLOSURE(closure),data,golem_closure_marshal);
  g_closure_add_finalize_notifier(G_CLOSURE(closure),data,golem_closure_finalizer);
  return closure;
}

void
golem_closure_set_this(GolemClosure * closure,const GValue * src)
{
  g_value_unset(&closure->this_value);
  if(src)
    {
      g_value_init(&closure->this_value,G_VALUE_TYPE(src));
      g_value_copy(src,&closure->this_value);
    }
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
      gboolean result = closure->invoke_func(closure,invoke,closure->data);
      return result;
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
  return golem_closure_new(golem_function_invoke,golem_function_finalizer,func);
}

GolemClosure *
golem_symbol_new(GolemClosureInfo * info,gpointer symbol_address)
{
  GolemSymbolData * func = g_new0(GolemSymbolData,1);
  func->info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  func->symbol_address = symbol_address;
  GolemClosure * closure = golem_closure_new(golem_symbol_invoke,golem_symbol_finalizer,func);
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
				  golem_parser_error(error,parser,"was expected \",\" or \")\"");
				}
			    }
			}
		      else
			{
			  done = FALSE;
			  golem_parser_error(error,parser,"the name of the parameter was expected");
			}
		    }
		  else
		    {
		      done = FALSE;
		      golem_parser_error(error,parser,"the type of the parameter was expected");
		    }

		  if(!done)
		    break;
		}
	    }
	  else
	    {
	      done = FALSE;

	      golem_parser_error(error,parser,"expected \"(\"");
	    }
	}
      else
	{
	  done = FALSE;
	  golem_parser_error(error,parser,"expected the function name");
	}
    }
  else
    {
      done = FALSE;
      golem_parser_error(error,parser,"expected a type");
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
			  golem_parser_error(error,parser,"was expected \",\" or \")\"");
			}
		    }
		}
	      else
		{
		  done = FALSE;
		  golem_parser_error(error,parser,"the name of the parameter was expected");
		}
	    }
	  else
	    {
	      done = FALSE;
	      golem_parser_error(error,parser,"the type of the parameter was expected");
	    }

	  if(!done)
	    break;
	}
    }
  else
    {
      done = FALSE;
      golem_parser_error(error,parser,"expected \"(\"");
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
	  if(!(info->priv->return_type = golem_context_get_type_define(context,info->priv->return_type_name,error)))
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
		  if(!(param->type = golem_context_get_type_define(context,param->type_name,error)))
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
	    golem_runtime_error(error,GOLEM_SYNTAXIS_ERROR,"unknown type \"%s\"",type_unresolved);
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
