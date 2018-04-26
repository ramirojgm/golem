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
#include <ffi.h>

struct _GolemTypeModulePrivate
{
  GolemVMBody * body;
  GList * 	statements;

  /* type_info */
  GList * symbols;
  GList * type_objects;
  GList * type_structs;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemTypeModule,golem_type_module,G_TYPE_TYPE_MODULE)


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
   if(golem_statement_check(GOLEM_SYMBOL_CLASS,parser))
       klass = GOLEM_SYMBOL_CLASS;
   else if(golem_statement_check(GOLEM_BLOCK_CLASS,parser))
     klass = GOLEM_BLOCK_CLASS;
   else if(golem_statement_check(GOLEM_VAR_CLASS,parser))
     klass = GOLEM_VAR_CLASS;
   else
     klass = GOLEM_EXPRESSION_CLASS;

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
	type_module->priv->statements = g_list_append(type_module->priv->statements,
						      statement);
      else
	done = FALSE;
    }


  g_object_unref(parser);
  return done;
}

gboolean
golem_type_module_compile(GolemTypeModule * type_module,
			   GError ** error)
{
  gboolean done = TRUE;
  for(GList * iter = g_list_first(type_module->priv->statements);
      iter;
      iter = g_list_next(iter))
    {
      GolemStatement * statement = (GolemStatement*)(iter->data);
      if(statement->klass == GOLEM_SYMBOL_CLASS)
	{
	  golem_symbol_
	}

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
			      gpointer * symbol,
			      GolemSymbolInfo ** symbol_info,
			      GError ** error)
{

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
  /* previous compile */
  self->priv->statements = NULL;

  /* post compile */
  self->priv->body = NULL;
  self->priv->symbols = NULL;
  self->priv->type_objects = NULL;
  self->priv->type_structs = NULL;
}

static void
golem_type_module_class_init(GolemTypeModuleClass * klass)
{

}
