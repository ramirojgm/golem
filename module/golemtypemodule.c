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
#include <stdio.h>
#include <ffi.h>

struct _GolemTypeModulePrivate
{
  gboolean loaded;

  gchar * name;
  GolemVMBody * body;

  /* statement */
  GList * statement;

  /* symbol */
  guint32	n_symbol;
  GolemSymbol** symbol;

  /* ffi */
  ffi_cif cif;
  GList * closure;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemTypeModule,golem_type_module,G_TYPE_TYPE_MODULE)

static gboolean
_golem_type_module_load(GTypeModule * module,GError ** error);

GolemTypeModule *
golem_type_module_new(void)
{
  return GOLEM_TYPE_MODULE(g_object_new(GOLEM_TYPE_TYPE_MODULE,NULL));
}


gboolean
golem_type_module_load_from_file(GolemTypeModule * type_module,
				 const gchar * filename,
				 GError ** error)
{
  return FALSE;
}


gboolean
golem_type_module_load_from_data(GolemTypeModule * type_module,
				  gpointer data,
				  gsize data_size,
				  GError ** error)
{
  return FALSE;
}

gboolean
golem_type_module_load(GolemTypeModule * type_module,
			GInputStream * stream,
			GError ** error)
{

  return FALSE;
}

static GolemStatement *
golem_type_module_statement_parse(GolemParser * parser,
				  GError ** error)
{
  GolemStatementClass * klass = NULL;
  GolemStatement * statement = NULL;
   while(golem_parser_check(parser,";"));

   /* search class */
   if(golem_statement_check(GOLEM_SYMBOL_ENTRY_CLASS,parser))
     klass = GOLEM_SYMBOL_ENTRY_CLASS;

   /* initialize and parse */
   if(klass)
     {
       statement = g_malloc0(klass->size);
       statement->klass = klass;
       statement->source = g_strdup(golem_parser_get_source_name(parser));
       statement->line = golem_parser_get_line(parser);
       klass->init(statement);
       if(!klass->parse(statement,parser,GOLEM_EXPRESSION_LIMIT_SEMICOLON,error))
 	{
 	  golem_statement_free(statement);
 	  statement = NULL;
 	}
       else if( klass == GOLEM_EXPRESSION_CLASS && !golem_parser_check(parser,";"))
 	{
 	  g_propagate_error(error,
 	  		g_error_new(GOLEM_ERROR,
 	  			  GOLEM_COMPILE_ERROR_SYNTAXES,
 	  			  "%s: %d: was expected \";\" instead \"%s\"",
 	  			  golem_parser_get_source_name(parser),
 	  			  golem_parser_get_line(parser),
 	  			  golem_parser_next_word(parser,FALSE))
 			    );

 	  golem_statement_free(statement);
 	  statement = NULL;
 	}
     }
   else
     {
       g_propagate_error(error,
 		g_error_new(GOLEM_ERROR,
 			  GOLEM_COMPILE_ERROR_SYNTAXES,
 			  "%s: %d: can't solve syntaxes \"%s\"",
 			  golem_parser_get_source_name(parser),
 			  golem_parser_get_line(parser),
 			  golem_parser_next_word(parser,FALSE))
       );
     }
   return statement;
}

gboolean
golem_type_module_parse(GolemTypeModule * type_module,
			 const gchar * name,
			 const gchar * str,
			 gssize length,
			 GError ** error)
{
  gboolean done = TRUE;
  GolemParser * parser = golem_parser_new(name);
  golem_parser_parse(parser,str,length);



  while((!golem_parser_is_end(parser)) && done)
    {
      GolemStatement * statement = golem_type_module_statement_parse(parser,
								     error);
      if(statement)
	type_module->priv->statement = g_list_append(type_module->priv->statement,
						      statement);
      else
	done = FALSE;
    }


  g_object_unref(parser);
  return done;
}

GType
golem_resolve_type_name(const gchar * type_name)
{
  GType result = G_TYPE_NONE;
  if (g_strcmp0(type_name,"int8") == 0)
    result = G_TYPE_CHAR;
  else if (g_strcmp0(type_name,"uint8") == 0)
    result = G_TYPE_UCHAR;
  else if (g_strcmp0(type_name,"int16") == 0)
    result = G_TYPE_INT16;
  else if (g_strcmp0(type_name,"uint16") == 0)
    result = G_TYPE_UINT16;
  else if (g_strcmp0(type_name,"int32") == 0)
    result = G_TYPE_INT;
  else if (g_strcmp0(type_name,"uint32") == 0)
    result = G_TYPE_UINT;
  else if (g_strcmp0(type_name,"int") == 0)
    result = G_TYPE_INT;
  else if (g_strcmp0(type_name,"uint") == 0)
    result = G_TYPE_UINT;
  else if (g_strcmp0(type_name,"int64") == 0)
    result = G_TYPE_INT64;
  else if (g_strcmp0(type_name,"uint64") == 0)
    result = G_TYPE_UINT64;
  else if (g_strcmp0(type_name,"long") == 0)
    result = G_TYPE_LONG;
  else if (g_strcmp0(type_name,"ulong") == 0)
    result = G_TYPE_ULONG;
  else if (g_strcmp0(type_name,"float") == 0)
    result = G_TYPE_FLOAT;
  else if (g_strcmp0(type_name,"double") == 0)
    result = G_TYPE_DOUBLE;
  else if (g_strcmp0(type_name,"string") == 0)
    result = G_TYPE_STRING;
  else if (g_strcmp0(type_name,"pointer") == 0)
    result = G_TYPE_POINTER;
  else if (g_strcmp0(type_name,"object") == 0)
    result = G_TYPE_OBJECT;
  return result;
}

static GolemSymbol *
golem_type_module_symbol_entry(GolemSymbolEntry * symbol)
{
  GolemSymbol * symbol_info = g_new0(GolemSymbol,1);
  symbol_info->name = g_strdup(symbol->name);
  symbol_info->return_constant = symbol->ret_const;
  symbol_info->return_type = golem_resolve_type_name(symbol->ret_type);
  symbol_info->n_arguments = g_list_length(symbol->arguments);
  symbol_info->arguments = g_new(GolemSymbolArgument,symbol_info->n_arguments);
  guint8 argument_index = 0;
  for(GList * iter = g_list_first(symbol->arguments); iter; iter = g_list_next(iter))
    {
      GolemSymbolEntryArgument * arg = (GolemSymbolEntryArgument*)iter->data;
      symbol_info->arguments[argument_index].name = g_strdup(arg->name);
      symbol_info->arguments[argument_index].type = golem_resolve_type_name(arg->type);
      argument_index ++;
    }
  return symbol_info;
}

gboolean
golem_type_module_compile(GolemTypeModule * type_module,
			   GError ** error)
{
  gboolean done = TRUE;
  GList * symbols_list = NULL;

  //TODO: Bind libraries
  //TODO: Loading dependences
  //TODO: Compiling type registration

  GolemScopeBuilder * scope_builder = golem_scope_builder_new();
  GolemVMBody * body = golem_vm_body_new();

  //Compiling functions bodies
  for(GList * iter = g_list_first(type_module->priv->statement);
      iter;
      iter = g_list_next(iter))
    {
      GolemStatement * statement = (GolemStatement*)(iter->data);
      if(statement->klass == GOLEM_SYMBOL_ENTRY_CLASS)
	{
	  GolemSymbolEntry * symbol_entry = GOLEM_SYMBOL_ENTRY(statement);
	  GolemSymbol * symbol_info = golem_type_module_symbol_entry(symbol_entry);

	  symbols_list = g_list_append(
	      symbols_list,
	      symbol_info);

	  if(!symbol_entry->external)
	    {
	      GolemVMBody * symbol_body = golem_vm_body_new();
	      golem_scope_builder_enter(scope_builder,symbol_body,error);
	      for(guint8 arg_index = 0;
		  arg_index < symbol_info->n_arguments;
		  arg_index ++)
		{
		  GolemSymbolArgument * arg = &(symbol_info->arguments[arg_index]);
		  golem_scope_builder_argument(scope_builder,
					       G_TYPE_INT,
					       arg->name,
					       error);
		}
	      golem_statement_compile(symbol_entry->body,
				      symbol_body,
				      scope_builder,
				      error);
	      golem_scope_builder_exit(scope_builder,error);
	      symbol_info->body_vm = symbol_body;
	    }
	}
    }

  type_module->priv->n_symbol = g_list_length(symbols_list);
  type_module->priv->symbol = g_new0(GolemSymbol*,type_module->priv->n_symbol);
  guint32 symbol_index = 0;
  for(GList * symbol_iter = g_list_first(symbols_list);
      symbol_iter;
      symbol_iter = g_list_next(symbol_iter))
    {
      type_module->priv->symbol[symbol_index] = (GolemSymbol*)symbol_iter->data;
      symbol_index ++;
    }

  if(done)
    {
      type_module->priv->body = body;
      g_list_free_full(type_module->priv->statement,
		       (GFreeFunc)golem_statement_free);
      type_module->priv->statement = NULL;
    }
  return done;
}

gchar **
golem_type_module_get_type_names(GolemTypeModule * type_module,
				  gsize * length)
{

  return NULL;
}

gchar **
golem_type_module_get_symbol_names(GolemTypeModule * type_module,
				    gsize * length)
{

  return NULL;
}

gboolean
golem_type_module_get_symbol(GolemTypeModule * type_module,
			      const gchar * symbol_name,
			      gpointer * symbol_callback,
			      GolemSymbol ** symbol_info,
			      GError ** error)
{
  _golem_type_module_load((GTypeModule*)type_module,error);

  if(symbol_callback)
    *symbol_callback = NULL;

  if(symbol_info)
    *symbol_info = NULL;

  for(guint symbol_index = 0;
      symbol_index < type_module->priv->n_symbol;
      symbol_index ++)
    {
      GolemSymbol * symbol = type_module->priv->symbol[symbol_index];
      if(g_strcmp0(symbol->name,symbol_name) == 0)
     	{
     	  if(symbol_callback)
     	    *symbol_callback = symbol->callback;

     	  if(symbol_info)
     	    *symbol_info = symbol;

     	  return TRUE;
     	}
    }
  return FALSE;
}

gboolean
golem_type_module_save_to_file(GolemTypeModule * type_module,
				const gchar * filename,
				GError ** error)
{

  return FALSE;
}

gboolean
golem_type_module_save_to_buffer(GolemTypeModule * type_module,
				  gpointer * buffer,
				  gsize * length,
				  GError ** error)
{

  return FALSE;
}

gboolean
golem_type_module_save(GolemTypeModule * type_module,
		       GOutputStream * stream,
		       GError ** error)
{

  return FALSE;
}

static void
golem_type_module_init(GolemTypeModule * self)
{
  self->priv = golem_type_module_get_instance_private(self);
  self->priv->loaded = FALSE;

  /* previous compile */
  self->priv->statement = NULL;

  /* post compile */
  self->priv->body = NULL;
  self->priv->symbol = NULL;
}

static void
golem_symbol_call(ffi_cif *cif,
		 gpointer ret,
		 gpointer args[],
		 gpointer user_data)
{

  GolemSymbol * symbol = (GolemSymbol*)user_data;
  ffi_arg * 	result = (ffi_arg*) ret;
  GolemVMData   vm_result;
  GolemVMData * vm_arg = g_new(GolemVMData,symbol->n_arguments);

  for(guint8 arg_index = 0;
      arg_index < symbol->n_arguments;
      arg_index ++)
    {
      vm_arg[arg_index].data->int64_v = *((gint64*)args[arg_index]);
    }

  golem_vm_body_run(symbol->body_vm,
		    symbol->scope_vm,
		    symbol->n_arguments,
		    vm_arg,
		    &vm_result,
		    NULL);
  g_free(vm_arg);

  *result = vm_result.data->int64_v;
  /**(ffi_arg *)ret = fputs(*(char **)args[0], (FILE *)stream);*/
}

static ffi_type *
golem_ffi_type_of(GType type)
{
  GType fundamental = G_TYPE_FUNDAMENTAL(type);
  ffi_type * type_result = NULL;

  switch(fundamental)
    {
    case G_TYPE_NONE:
      type_result = &ffi_type_void;
      break;
    case G_TYPE_CHAR:
      type_result = &ffi_type_sint8;
      break;
    case G_TYPE_UCHAR:
      type_result = &ffi_type_uint8;
      break;
    case G_TYPE_INT16:
      type_result = &ffi_type_sint16;
      break;
    case G_TYPE_UINT16:
      type_result = &ffi_type_uint16;
      break;
    case G_TYPE_INT:
    case G_TYPE_BOOLEAN:
      type_result = &ffi_type_sint32;
      break;
    case G_TYPE_UINT:
      type_result = &ffi_type_uint32;
      break;
    case G_TYPE_INT64:
    case G_TYPE_LONG:
      type_result = &ffi_type_sint64;
      break;
    case G_TYPE_UINT64:
    case G_TYPE_ULONG:
      type_result = &ffi_type_uint64;
      break;
    case G_TYPE_FLOAT:
      type_result = &ffi_type_float;
      break;
    case G_TYPE_DOUBLE:
      type_result = &ffi_type_double;
      break;
    default:
      type_result = &ffi_type_pointer;
    }
  return type_result;
}

static gboolean
_golem_type_module_load(GTypeModule * module,
			GError ** error)
{
  GolemTypeModule * type_module = GOLEM_TYPE_MODULE(module);
  if(!type_module->priv->loaded)
    {
      gboolean done = TRUE;
      if(type_module->priv->statement)
	done = golem_type_module_compile(type_module,error);

      if(done)
	{
	  type_module->priv->loaded = TRUE;
	  GolemVMScope * scope = golem_vm_scope_new();

	    //ffi_closure_free(closure);
	  GModule * global_module = g_module_open(NULL,G_MODULE_BIND_LOCAL);
	  for(guint32 symbol_index = 0;
	      symbol_index < type_module->priv->n_symbol;
	      symbol_index ++)
	    {
	      GolemSymbol * symbol = type_module->priv->symbol[symbol_index];
	      if(symbol->body_vm)
		{
		  symbol->scope_vm = scope;
		  ffi_type ** args = NULL;
		  ffi_closure *closure;
		  gpointer callback = NULL;
		  closure = ffi_closure_alloc(sizeof(ffi_closure), &callback);
		  if(closure)
		    {
		      args = g_new0(ffi_type*,symbol->n_arguments);
		      for(guint8 arg_index = 0;
			  arg_index < symbol->n_arguments;
			  arg_index ++)
			args[arg_index] = golem_ffi_type_of(symbol->arguments[arg_index].type);

		      done = ffi_prep_cif(&(type_module->priv->cif),
					  FFI_DEFAULT_ABI,
					  symbol->n_arguments,
		                          golem_ffi_type_of(symbol->return_type),
					  args) == FFI_OK;
		      if(done)
			{
			  done = ffi_prep_closure_loc(closure,
						      &(type_module->priv->cif),
						      golem_symbol_call,
						      symbol,
						      callback) == FFI_OK;
			  if(done)
			    {
			      symbol->callback = callback;

			    }
			  else
			    {
			      //TODO:throw exception
			    }
			}
		      else
			{
			  //TODO:throw exception
			}
		      //g_free(args);
		    }
		  else
		    {
		      //TODO:throw exception
		    }
		}
	      else
		{
		  done = g_module_symbol(global_module,
					 symbol->name,
					 &(symbol->callback));
		}
	    }
	  g_module_close(global_module);
	  /*done = golem_vm_body_run(type_module->priv->body,
				      scope,
				      0,
				      NULL,
				      NULL,
				      error);*/
	}
      return done;
    }

  return TRUE;
}

static void
golem_type_module_class_init(GolemTypeModuleClass * klass)
{

}
