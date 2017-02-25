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
  gboolean	resolved: 1;
  gchar *	name;
  gchar *	return_type_name;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemClosureInfo,golem_closure_info,G_TYPE_OBJECT)

void golem_symbol_invoke (GClosure *closure,
                    GValue *return_value,
                    guint n_param_values,
                    const GValue *param_values,
                    gpointer invocation_hint,
                    gpointer marshal_data)
{
  GolemSymbol * self = (GolemSymbol*)closure;
  gboolean 	done = TRUE;
  GObjectClass * klass = NULL;
  GType 	return_type = golem_closure_info_get_return_type(self->parent_boxed.info);
  GType 	fundamental_return_type = G_TYPE_FUNDAMENTAL(return_type);
  GolemArgs * 	args = golem_args_new();
  GList * 	cur_param = g_list_first(golem_closure_info_get_parameters(self->parent_boxed.info));
  GValue * param_value = NULL;
  GolemClosureParameter * param_info = NULL;
  guint param_index = 0;

  //use first parameter for instance
  if(self->parent_boxed.instance)
    {
      golem_args_append_pointer(args,self->parent_boxed.instance);
    }

  //use first parameter for class
  if(self->parent_boxed.class_type != 0)
    {
      klass = g_type_class_ref(self->parent_boxed.class_type);
      golem_args_append_pointer(args,klass);
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
	      golem_args_append_pointer(args,&(self->parent_boxed.error));
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
	      golem_args_append_pointer(args,&(param_value->data[1].v_pointer));
	    }
	  else if((G_VALUE_TYPE(param_value) == param_info->type )||(g_type_is_a(G_VALUE_TYPE(param_value),param_info->type)))
	    {
	      golem_args_append(args,param_value);
	    }
	  else if(param_info->type == G_TYPE_VALUE)
	    {
	      GValue * new_value = g_new0(GValue,0);
	      g_value_init(new_value,G_VALUE_TYPE(param_value));
	      g_value_copy(param_value,new_value);
	      g_value_unset(param_value);
	      g_value_init(param_value,G_TYPE_VALUE);
	      g_value_take_boxed(param_value,new_value);
	      golem_args_append(args,param_value);
	    }
	  else if(g_value_type_transformable(G_VALUE_TYPE(param_value), param_info->type))
	    {
	      GValue transformed = G_VALUE_INIT;
	      g_value_init(&transformed,param_info->type);
	      g_value_transform(param_value,&transformed);
	      g_value_unset(param_value);
	      g_value_copy(&transformed,param_value);
	      g_value_unset(&transformed);
	      golem_args_append(args,param_value);
	    }
	  else
	    {
	      done = FALSE;
	      self->parent_boxed.error = g_error_new(
		  GOLEM_ERROR,
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
	  golem_args_append(args,param_value);
	}
    }

  //set empty parameters
  while(cur_param)
    {
      if(param_index == self->parent_boxed.info->throw_at)
	{
	  golem_args_append_pointer(args,&(self->parent_boxed.error));
	}
      param_info = (GolemClosureParameter*)cur_param->data;
      GValue empty_pass = G_VALUE_INIT;
      g_value_init(&empty_pass,param_info->type);
      golem_args_append(args,&empty_pass);
      cur_param = g_list_next(cur_param);
      param_index++;
    }

  //check last parameter is throw at
  if(param_index == self->parent_boxed.info->throw_at)
    {
      golem_args_append_pointer(args,&(self->parent_boxed.error));
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
  golem_args_free(args);

  if(klass)
    g_type_class_unref(klass);
}

void golem_symbol_finalizer(gpointer data,GClosure * closure)
{
  GolemSymbol * self = GOLEM_SYMBOL(closure);
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
  GolemFunction * self = GOLEM_FUNCTION(closure);
  GolemContext * this_context = golem_context_new(self->context);
  GList * cur_param = g_list_first(golem_closure_info_get_parameters(self->parent_boxed.info));
  GValue * param_value = NULL;
  GolemClosureParameter * param_info = NULL;
  guint param_index = 0;

  golem_context_declare(this_context,"::return::",G_TYPE_NONE,NULL);

  //set parameters
  for(param_index = 0;param_index < n_param_values;param_index ++)
    {
      param_value = (GValue*)&(param_values[param_index]);
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
	//declared parameter
	if(param_info->is_reference)
	  {

	  }
	else if((G_VALUE_TYPE(param_value) == param_info->type )||(g_type_is_a(G_VALUE_TYPE(param_value),param_info->type)))
	  {
	    golem_context_set_auto(this_context,param_info->name,param_value,NULL);
	  }
	else if(param_info->type == G_TYPE_VALUE)
	  {
	    GValue * new_value = g_new0(GValue,0);
	    g_value_init(new_value,G_VALUE_TYPE(param_value));
	    g_value_copy(param_value,new_value);
	    g_value_unset(param_value);
	    g_value_init(param_value,G_TYPE_VALUE);
	    g_value_take_boxed(param_value,new_value);
	    golem_context_set_auto(this_context,param_info->name,param_value,NULL);
	  }
	else if(g_value_type_transformable(G_VALUE_TYPE(param_value), param_info->type))
	  {
	    GValue transformed = G_VALUE_INIT;
	    g_value_init(&transformed,param_info->type);
	    g_value_transform(param_value,&transformed);
	    g_value_unset(param_value);
	    g_value_copy(&transformed,param_value);
	    g_value_unset(&transformed);
	    golem_context_set_auto(this_context,param_info->name,param_value,NULL);
	  }
	else
	  {
	    self->parent_boxed.error = g_error_new(
		GOLEM_ERROR,
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

	}
    }

  if(golem_statement_execute(self->sentence,this_context,&(self->parent_boxed.error)))
    {
      //return
    }
  //TODO: free param values
  g_object_unref(this_context);
}

void golem_function_finalizer(gpointer data,GClosure * closure)
{
  GolemFunction * self = GOLEM_FUNCTION(closure);
  if(self->parent_boxed.error)
    g_error_free(self->parent_boxed.error);

  if(self->parent_boxed.instance)
    g_object_unref(self->parent_boxed.instance);

  g_object_unref(self->parent_boxed.info);
}

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
  symbol->parent_boxed.class_type = 0;
  symbol->parent_boxed.instance = NULL;
  g_closure_set_marshal(G_CLOSURE(symbol),golem_symbol_invoke);
  g_closure_add_finalize_notifier(G_CLOSURE(symbol),NULL,golem_symbol_finalizer);
  return GOLEM_CLOSURE(symbol);
}

GolemClosure *
golem_symbol_instanced_new(GolemClosureInfo * info,gpointer symbol_address,gpointer instance)
{
  GolemSymbol  * symbol = GOLEM_SYMBOL(g_closure_new_simple(sizeof(GolemSymbol),NULL));
  symbol->parent_boxed.info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  symbol->symbol_address = symbol_address;
  symbol->parent_boxed.class_type = 0;
  symbol->parent_boxed.instance = g_object_ref(instance);
  g_closure_set_marshal(G_CLOSURE(symbol),golem_symbol_invoke);
  g_closure_add_finalize_notifier(G_CLOSURE(symbol),NULL,golem_symbol_finalizer);
  return GOLEM_CLOSURE(symbol);
}

GolemClosure *
golem_symbol_static_new(GolemClosureInfo * info,gpointer symbol_address,GType type_class)
{
  GolemSymbol  * symbol = GOLEM_SYMBOL(g_closure_new_simple(sizeof(GolemSymbol),NULL));
  symbol->parent_boxed.info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  symbol->symbol_address = symbol_address;
  symbol->parent_boxed.class_type = type_class;
  symbol->parent_boxed.instance = NULL;
  g_closure_set_marshal(G_CLOSURE(symbol),golem_symbol_invoke);
  g_closure_add_finalize_notifier(G_CLOSURE(symbol),NULL,golem_symbol_finalizer);
  return GOLEM_CLOSURE(symbol);
}

GolemClosure *
golem_function_new(GolemClosureInfo * info,GolemContext * context,GolemStatement * sentence)
{
  GolemFunction  * func = GOLEM_FUNCTION(g_closure_new_simple(sizeof(GolemFunction),NULL));
  func->parent_boxed.info = GOLEM_CLOSURE_INFO(g_object_ref(info));
  func->context = GOLEM_CONTEXT(g_object_ref(context));
  func->sentence = GOLEM_STATEMENT(g_object_ref(sentence));
  func->parent_boxed.class_type = 0;
  func->parent_boxed.instance = NULL;
  g_closure_set_marshal(G_CLOSURE(func),golem_function_invoke);
  g_closure_add_finalize_notifier(G_CLOSURE(func),NULL,golem_function_finalizer);
  return GOLEM_CLOSURE(func);
}

GolemClosure *
golem_function_instanced_new(GolemClosureInfo * info,GolemContext * context,GolemStatement * sentence,gpointer instance)
{

}

GolemClosure *
golem_function_static_new(GolemClosureInfo * info,GolemContext * context,GolemStatement * sentence,GType type_class)
{

}

GolemClosure *
golem_signal_new(gpointer instance,guint signal_id)
{

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
      info->return_const = TRUE;
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
		  gboolean is_reference = FALSE;
		  gboolean is_array = FALSE;
		  if(golem_parser_check_is_named(parser))
		    {
		      type_name = golem_parser_next_word(parser,NULL,TRUE);
		      if(golem_parser_next_word_check(parser,"&"))
			{
			  is_reference = TRUE;
			}
		      if(golem_parser_check_is_named(parser))
			{
			  name = golem_parser_next_word(parser,NULL,TRUE);
			  if(golem_parser_next_word_check(parser,"["))
			    {
			      if(golem_parser_next_word_check(parser,"]"))
				{
				  is_array = TRUE;
				}
			      else
				{
				  done = FALSE;
				  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected \"]\"");
				}
			    }
			  if(done)
			    {
			      GolemClosureParameter * param = g_new0(GolemClosureParameter,1);
			      param->is_array = is_array;
			      param->is_reference = is_reference;
			      param->name = g_strdup(name);
			      param->type_name = g_strdup(type_name);
			      param->type = G_TYPE_NONE;
			      info->parameters = g_list_append(info->parameters,param);
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
	      if(golem_parser_next_word_check(parser,"throw"))
		{
		  if(golem_parser_next_word_check(parser,"("))
		    {
		      if(golem_parser_check_is_number(parser))
			{
			  info->throw_at =  atoi(golem_parser_next_word(parser,NULL,TRUE));
			  if(!golem_parser_next_word_check(parser,")"))
			    {
			      done = FALSE;
			      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected \")\"");
			    }
			}
		      else
			{
			  done = FALSE;
			  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected position for error parameter");
			}
		    }
		  else
		    {
		      info->throw_at = g_list_length(info->parameters);
		    }
		}
	      else
		{
		  info->throw_at = -1;
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
  info->return_type = G_TYPE_VALUE;
  info->throw_at = -1;
  info->priv->name = g_strdup_printf("anonymous%lld",anonymous_id);
  anonymous_id++;

  if(golem_parser_next_word_check(parser,"("))
    {
      while(!golem_parser_next_word_check(parser,")"))
	{
	  const gchar * type_name, *name;
	  gboolean is_reference = FALSE;
	  gboolean is_array = FALSE;
	  if(golem_parser_check_is_named(parser))
	    {
	      type_name = golem_parser_next_word(parser,NULL,TRUE);
	      if(golem_parser_next_word_check(parser,"&"))
		{
		  is_reference = TRUE;
		}
	      if(golem_parser_check_is_named(parser))
		{
		  name = golem_parser_next_word(parser,NULL,TRUE);
		  if(golem_parser_next_word_check(parser,"["))
		    {
		      if(golem_parser_next_word_check(parser,"]"))
			{
			  is_array = TRUE;
			}
		      else
			{
			  done = FALSE;
			  golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected \"]\"");
			}
		    }
		  if(done)
		    {
		      GolemClosureParameter * param = g_new0(GolemClosureParameter,1);
		      param->is_array = is_array;
		      param->is_reference = is_reference;
		      param->name = g_strdup(name);
		      param->type_name = g_strdup(type_name);
		      param->type = G_TYPE_NONE;
		      info->parameters = g_list_append(info->parameters,param);
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
	  if(!(info->return_type = golem_resolve_type_name(context,info->priv->return_type_name)))
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
	  for(GList * params = g_list_first(info->parameters);params;params = g_list_next(params))
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
  return info->return_type;
}

GList *
golem_closure_info_get_parameters(GolemClosureInfo * info)
{
  return info->parameters;
}
