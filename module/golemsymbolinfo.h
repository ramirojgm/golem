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

typedef struct _GolemSymbolCallable GolemSymbolCallable;

struct _GolemSymbolArgumentInfo
{
  gchar * 	name;
  gchar * 	type_name;
  GolemTypeCode type_code;
};

struct _GolemSymbolInfo
{
  /* data */
  gboolean is_external;
  gboolean is_static;
  gchar * name;
  /* return */
  GolemTypeCode return_type_code;
  gboolean return_constant;
  gchar * return_type_name;
  /* arguments */
  guint32 n_arguments;
  GolemSymbolArgumentInfo ** arguments;
  /* function */
  gpointer symbol_func;

  /* body */
  GolemStatement * stmt_body;
  GolemVMScope * vm_scope;
  GolemVMBody * vm_body;
};

struct _GolemSymbolCallable
{
  GolemCallable parent;
  gpointer this_value;
  GolemSymbolInfo * symbol_info;
};


gboolean
golem_symbol_info_check(GolemParser * parser)
{
  gboolean result = FALSE;
  golem_parser_save_point(parser);
  golem_parser_check(parser,"static");
  golem_parser_check(parser,"const");
  if((result = golem_parser_check_is_named(parser))){
      golem_parser_skip(parser);
      if((result = golem_parser_check_is_named(parser)))
	  result = golem_parser_check(parser,"(");
  }
  golem_parser_restore_point(parser);
  return result;
}

void
golem_symbol_argument_info_free(GolemSymbolArgumentInfo * info)
{
  g_free(info->type_name);
  g_free(info->name);
  g_free(info);
}

gboolean
golem_symbol_callable_call(GolemSymbolCallable * callable,
			   guint8 argc,
			   GolemVMData * argv,
			   GolemVMData * ret,
			   GError ** error)
{
  gboolean done = TRUE;
  if(callable->symbol_info->is_external)
    {

    }
  else
    {
      guint8 real_argc = argc + 1;
      GolemVMData * real_argv = g_new0(GolemVMData,real_argc);
      real_argv[0].data->pointer_v = callable->this_value;
      for(guint8 arg_index = 0;arg_index < argc; arg_index ++)
	real_argv[arg_index + 1] = argv[arg_index + 1];
      done = golem_vm_body_run(callable->symbol_info->vm_body,
			       callable->symbol_info->vm_scope,
			       real_argc,
			       real_argv,
			       ret,
			       error);
      g_free(real_argv);
    }
  return done;
}

gboolean
golem_symbol_callable_static_call(GolemSymbolCallable * callable,
				   guint8 argc,
				   GolemVMData * argv,
				   GolemVMData * ret,
				   GError ** error)
{

  return FALSE;
}

void
golem_symbol_callable_finalize(GolemSymbolCallable * callable)
{
  if(callable->this_value)
    g_object_unref(callable->this_value);
}

GolemCallable *
golem_symbol_callable_new(gpointer object_instance,
			  GolemSymbolInfo * symbol_info,
			  GError ** error)
{
  GolemSymbolCallable * symbol_callable = g_new0(GolemSymbolCallable,1);
  symbol_callable->this_value = g_object_ref(object_instance);
  symbol_callable->symbol_info = symbol_info;
  symbol_callable->parent.call = (GolemCallableCall)golem_symbol_callable_call;
  symbol_callable->parent.finalize = (GolemCallableFinalize)golem_symbol_callable_finalize;
  return (GolemCallable*)symbol_callable;
}

GolemCallable *
golem_symbol_callable_new_static(GolemSymbolInfo * symbol_info,
				 GError ** error)
{
  GolemSymbolCallable * symbol_callable = g_new0(GolemSymbolCallable,1);
  symbol_callable->this_value = NULL;
  symbol_callable->symbol_info = symbol_info;
  symbol_callable->parent.call = (GolemCallableCall)golem_symbol_callable_static_call;
  symbol_callable->parent.finalize = (GolemCallableFinalize)golem_symbol_callable_finalize;
  return (GolemCallable*)symbol_callable;
}

GolemSymbolInfo *
golem_symbol_info_parse(GolemParser * parser,
			GError ** error)
{
  GolemSymbolInfo * symbol_info = NULL;
  gboolean is_static = golem_parser_check(parser,"static");
  gboolean is_const = golem_parser_check(parser,"const");

  if(golem_parser_check_is_named(parser))
    {
      const gchar * type_result_name = golem_parser_next_word(parser,TRUE);
      if(golem_parser_check_is_named(parser))
	{
	  const gchar * symbol_name = golem_parser_next_word(parser,TRUE);
	  if(golem_parser_check(parser,"("))
	    {
	      GList * symbol_argument_info = NULL;
	      gboolean done = TRUE;

	      while(!golem_parser_check(parser,")"))
		{
		  if(golem_parser_check_is_named(parser))
		    {
		       const gchar * argument_type = golem_parser_next_word(parser,TRUE);
		       if(golem_parser_check_is_named(parser))
			 {
			   GolemSymbolArgumentInfo * symbol_argument = g_new0(GolemSymbolArgumentInfo,1);
			   symbol_argument->type_name = g_strdup(argument_type);
			   symbol_argument->name = g_strdup(golem_parser_next_word(parser,TRUE));
			   symbol_argument_info = g_list_append(symbol_argument_info,symbol_argument);
			 }
		       else
			 {
			   //TODO: throw exception
			   done = FALSE;
			   break;
			 }
		    }
		  else
		    {
		      //TODO: throw exception
		      done = FALSE;
		      break;
		    }

		  if(golem_parser_check(parser,")"))
		    {
		      break;
		    }
		  else if(!golem_parser_check(parser,","))
		    {
		      //TODO: throw exception
		      done = FALSE;
		      break;
		    }
		}

	      if(done)
		{
		  symbol_info = g_new0(GolemSymbolInfo,1);
		  if(golem_parser_check(parser,";"))
		    {
		      symbol_info->is_external = TRUE;
		    }
		  else
		    {
		      symbol_info->is_external = FALSE;
		      symbol_info->stmt_body = golem_statement_parse(parser,error);
		      symbol_info->vm_body = NULL;
		      if(!symbol_info->stmt_body)
			{
			  done = FALSE;
			  g_free(symbol_info);
			  symbol_info = NULL;
			}
		    }

		  if(done)
		    {
		      symbol_info->name = g_strdup(symbol_name);
		      symbol_info->return_type_name = g_strdup(type_result_name);
		      symbol_info->is_static = is_static;
		      symbol_info->return_constant = is_const;
		      symbol_info->n_arguments = g_list_length(g_list_first(symbol_argument_info));
		      symbol_info->arguments = g_new0(GolemSymbolArgumentInfo*,symbol_info->n_arguments);
		      GList * arg_iter = g_list_first(symbol_argument_info);
		      for(guint32 arg_index = 0;arg_index < symbol_info->n_arguments; arg_index ++)
			{
			  symbol_info->arguments[arg_index] = (GolemSymbolArgumentInfo*)arg_iter->data;
			  arg_iter = g_list_next(arg_iter);
			}
		      g_list_free(symbol_argument_info);
		    }
		}
	      else
		{
		  g_list_free_full(symbol_argument_info,
				 (GDestroyNotify)golem_symbol_argument_info_free);
		}
	    }
	  else
	    {
	      //TODO:throw exception
	    }
	}
      else
	{
	  //TODO: throw exception
	}
    }
  else
    {
      //TODO: throw exception
    }
  return symbol_info;
}
