/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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


#include "golem.h"
#include "gmodule.h"
#include <ctype.h>
#include <string.h>

static GList * 	_golem_module_list = NULL;
static GMutex 	_golem_module_mutex = G_STATIC_MUTEX_INIT;

typedef struct
{
 GType gtype;
 gpointer info;
}GolemModuleInfo;

struct _GolemModulePrivate
{
  gboolean initialized;
  GolemContext * context;
  GList * references;
  GList * statements;
  GList * type_info;
  GList * interface_info;
  GError * load_error;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemModule,golem_module,G_TYPE_OBJECT)


gboolean
golem_module_use(GolemModule * self,GError ** error)
{
  if(!self->priv->initialized)
    {
      gboolean done = FALSE;
      g_mutex_lock(&_golem_module_mutex);
      _golem_module_list = g_list_append(_golem_module_list,self);
      g_mutex_unlock(&_golem_module_mutex);
      GolemRuntime * runtime = golem_runtime_new(self->priv->context);
      for(GList * iter = g_list_first(self->priv->statements);iter;iter = g_list_next(iter))
      {
	if(GOLEM_IS_REGISTER(iter->data))
	    done = golem_register_register_type(GOLEM_REGISTER(iter->data),self,error);
	else
	    done = golem_statement_execute(GOLEM_STATEMENT(iter->data),runtime,error);

	if(!done)
	  break;
      }
      golem_runtime_destroy(runtime);

      if(!done)
	golem_module_unuse(self);
      else
	self->priv->initialized = TRUE;


      return done;
    }
  else
    {
      g_mutex_lock(&_golem_module_mutex);
      _golem_module_list = g_list_append(_golem_module_list,self);
      g_mutex_unlock(&_golem_module_mutex);
      return TRUE;
    }
}

void
golem_module_unuse(GolemModule * self)
{
  if(self->priv->initialized)
    {
      g_mutex_lock(&_golem_module_mutex);
      _golem_module_list = g_list_remove(_golem_module_list,self);
      g_mutex_unlock(&_golem_module_mutex);
    }
}


GType
golem_module_register_type(GolemModule *module,
			   GolemTypeInfo * info,
			   GType parent_type,
			   const gchar *type_name,
			   const GTypeInfo * type_info,
			   GTypeFlags flags)
{
  GType new_type = g_type_register_static(parent_type,type_name,type_info,flags);;
  if(new_type)
    {
      GolemModuleInfo * module_info = g_new0(GolemModuleInfo,1);
      module_info->gtype = new_type;
      module_info->info = info;
      module->priv->type_info = g_list_append(module->priv->type_info,module_info);
    }
  return new_type;
}

GType
golem_module_register_boxed_type(GolemModule *module,
			   GolemTypeInfo * info,
			   const gchar *type_name,
			   GBoxedCopyFunc copy,
			   GBoxedFreeFunc free)
{
  GType new_type = g_boxed_type_register_static(type_name,copy, free);
  if(new_type)
    {
      GolemModuleInfo * module_info = g_new0(GolemModuleInfo,1);
      module_info->gtype = new_type;
      module_info->info = info;
      module->priv->type_info = g_list_append(module->priv->type_info,module_info);
    }
  return new_type;
}

void
golem_module_import_type(GolemModule * module, GolemTypeInfo * info, GType type)
{
  if(type)
    {
      GolemModuleInfo * module_info = g_new0(GolemModuleInfo,1);
      module_info->gtype = type;
      module_info->info = info;
      module->priv->type_info = g_list_append(module->priv->type_info,module_info);
    }
}

static void
golem_module_init(GolemModule * self)
{
 g_mutex_init(&self->module_mutex);
 self->priv = golem_module_get_instance_private(self);
 self->priv->initialized = FALSE;
 self->priv->context = golem_context_new(NULL);
 self->priv->interface_info = NULL;
 self->priv->type_info = NULL;
 self->priv->statements = NULL;
}

static void
golem_module_class_init(GolemModuleClass * klass)
{

}

GolemContext *
golem_module_get_context(GolemModule * module)
{
  GolemContext * context = NULL;
  g_mutex_lock(&module->module_mutex);
  context = module->priv->context;
  g_mutex_unlock(&module->module_mutex);
  return context;
}

GType *
golem_module_get_types(GolemModule * module,gsize * n_types)
{
  g_mutex_lock(&module->module_mutex);
  gsize count = g_list_length(g_list_first(module->priv->type_info)) + g_list_length(g_list_first(module->priv->interface_info)) ;
  if(n_types)
    *n_types = count;

  GType * result = g_new0(GType,count+1);
  gint index = 0;
  for(GList * iter = g_list_first(module->priv->type_info);iter;iter = g_list_next(iter))
    {
      GolemModuleInfo * info = (GolemModuleInfo *)iter->data;
      result[index] = info->gtype;
      index ++;
    }
  for(GList * iter = g_list_first(module->priv->interface_info);iter;iter = g_list_next(iter))
    {
      GolemModuleInfo * info = (GolemModuleInfo *)iter->data;
      result[index] = info->gtype;
      index ++;
    }
  g_mutex_unlock(&module->module_mutex);
  return result;
}

gchar **
golem_module_get_references(GolemModule * module,gsize * n_references)
{
  g_mutex_lock(&module->module_mutex);
  gsize count = g_list_length(g_list_first(module->priv->references));
  if(n_references)
    *n_references = count;
  gchar ** result = g_new0(gchar*,count+1);
  gint index = 0;
  for(GList * iter = g_list_first(module->priv->references);iter;iter = g_list_next(iter))
    {
      result[index] = g_strdup((gchar*)iter->data);
      index ++;
    }
  g_mutex_unlock(&module->module_mutex);
  return result;
}


GolemTypeInfo *
golem_module_get_type_info(GolemModule * module,GType type)
{
  g_return_val_if_fail(module->priv->initialized == TRUE,NULL);
  GolemTypeInfo * info = NULL;
  g_mutex_lock(&module->module_mutex);
  for(GList * iter = g_list_first(module->priv->type_info);iter;iter = g_list_next(iter))
    {
      GolemModuleInfo * mod_info = (GolemModuleInfo*)iter->data;
      if(mod_info->gtype == type)
	{
	  info = GOLEM_TYPE_INFO(mod_info->info);
	  break;
	}
    }
  g_mutex_unlock(&module->module_mutex);
  return info;
}

gboolean
golem_module_compile(GolemModule * module,const gchar * source_name,const gchar * code,gssize code_length,GError ** error)
{
  g_return_val_if_fail(module->priv->initialized == FALSE,FALSE);
  gpointer sentence;
  gboolean done = TRUE;
  GolemParser * parser = golem_parser_new(source_name);
  golem_parser_parse(parser,code,code_length);

  while(!golem_parser_is_end(parser))
    {
      if(golem_parser_next_word_check(parser,"using"))
      {
	gchar * reference = g_new0(gchar,1024);
	while(!(golem_parser_is_end(parser) || golem_parser_next_word_check(parser,";")))
	  {
	    strcat(reference,golem_parser_next_word(parser,NULL,TRUE));
	  }
	module->priv->references = g_list_append(module->priv->references,reference);
      }
      else
      {
	if(golem_builder_class_check(parser))
	  sentence = GOLEM_REGISTER(golem_builder_class_parse(parser,error));
	if(golem_builder_struct_check(parser))
	  sentence = GOLEM_REGISTER(golem_builder_struct_parse(parser,error));
	else if(golem_shared_object_check(parser))
	  sentence = GOLEM_STATEMENT(golem_shared_object_parse(parser,error));
	else if(golem_builder_extern_check(parser))
	  sentence = GOLEM_STATEMENT(golem_builder_extern_parse(parser,error));
	else if(golem_extends_check(parser))
	  sentence = GOLEM_STATEMENT(golem_extends_parse(parser,error));
	else
	  sentence = golem_statement_parse(parser,error);

	if(sentence)
	  {
	    module->priv->statements = g_list_append(module->priv->statements,sentence);
	    sentence = NULL;
	  }
	else
	  {
	    g_list_free_full(module->priv->statements,g_object_unref);
	    g_list_free_full(module->priv->references,g_free);
	    module->priv->statements = NULL;
	    module->priv->references = NULL;
	    done = FALSE;
	    break;
	  }
      }
    }
  g_object_unref(parser);
  return done;
}

GolemTypeInfo *
golem_type_info_from_gtype(GType type)
{
  GolemTypeInfo * info = NULL;
  g_mutex_lock(&_golem_module_mutex);
  for(GList * iter = g_list_first(_golem_module_list);iter; iter = g_list_next(iter))
    {
      GolemModule * mod = GOLEM_MODULE(iter->data);
      if((info = golem_module_get_type_info(mod,type)) != NULL)
	break;
    }
  g_mutex_unlock(&_golem_module_mutex);
  return info;
}

GolemModule *
golem_module_new()
{
  return GOLEM_MODULE(g_object_new(GOLEM_TYPE_MODULE,NULL));
}

GType
golem_type_from_name(const gchar * name)
{
  gboolean is_builtin = TRUE;
  GType type = 0;
  GType native_type = 0;
  if(g_strcmp0(name,"void") == 0)
    native_type = G_TYPE_NONE;
  else if(g_strcmp0(name,"var") == 0)
    native_type = G_TYPE_VALUE;
  else if(g_strcmp0(name,"bool") == 0)
    native_type = G_TYPE_BOOLEAN;
  else if(g_strcmp0(name,"string") == 0)
    native_type = G_TYPE_STRING;
  else if(g_strcmp0(name,"byte") == 0 || g_strcmp0(name,"char") == 0)
    native_type = G_TYPE_CHAR;
  else if(g_strcmp0(name,"int") == 0)
    native_type = G_TYPE_INT;
  else if(g_strcmp0(name,"long") == 0)
    native_type = G_TYPE_LONG;
  else if(g_strcmp0(name,"ubyte") == 0 || g_strcmp0(name,"uchar") == 0)
    native_type = G_TYPE_UCHAR;
  else if(g_strcmp0(name,"uint") == 0)
    native_type = G_TYPE_UINT;
  else if(g_strcmp0(name,"ulong") == 0)
    native_type = G_TYPE_ULONG;
  else if(g_strcmp0(name,"pointer") == 0)
    native_type = G_TYPE_POINTER;
  else if(g_strcmp0(name,"float") == 0)
    native_type = G_TYPE_FLOAT;
  else if(g_strcmp0(name,"double") == 0)
    native_type = G_TYPE_DOUBLE;
  else if(g_strcmp0(name,"function") == 0)
    native_type = GOLEM_TYPE_CLOSURE;
  else if(g_strcmp0(name,"object") == 0)
    native_type = G_TYPE_OBJECT;
  else if(g_strcmp0(name,"array") == 0)
    native_type = G_TYPE_ARRAY;
  else
   {
     is_builtin = FALSE;
     native_type = g_type_from_name(name);
     static gchar type_named[256] = {0,};
     memset(type_named,0,256);
     if(native_type == 0)
      {
	GModule * module = g_module_open(NULL,0);
	guint type_named_index = 0;
	for(const gchar * iter = name;*iter;iter ++)
	  {
	    if(isupper(*iter) && (iter != name))
	      {
		type_named[type_named_index] = '_';
		type_named_index++;

	      }
	    type_named[type_named_index] = tolower(*iter);
	    type_named_index++;
	  }
	strcat(type_named,"_get_type");
	GType (*get_type)() = 0;
	g_module_symbol(module,type_named,(gpointer*)&get_type);
	if(get_type)
	  native_type = get_type();
	else
	  native_type = 0;
	g_module_close(module);
      }
   }

  if(native_type)
   {

    if(is_builtin)
      {
	type = native_type;
      }
    else
      {
	g_mutex_lock(&_golem_module_mutex);
	for(GList * iter = g_list_first(_golem_module_list);iter; iter = g_list_next(iter))
	  {
	    GolemModule * mod = GOLEM_MODULE(iter->data);
	    g_mutex_lock(&mod->module_mutex);

	    for(GList * iter_type = g_list_first(mod->priv->type_info); iter_type; iter_type = g_list_next(iter_type))
	      {
		GolemModuleInfo * info = (GolemModuleInfo*)iter_type->data;
		if(info->gtype == native_type)
		  {
		    type = info->gtype;
		    break;
		  }
	      }

	    g_mutex_unlock(&mod->module_mutex);
	    if(type)
		break;
	  }
	g_mutex_unlock(&_golem_module_mutex);
      }
    }
  return type;
}

