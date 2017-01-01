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
#include <stdio.h>

typedef struct _GolemFuncPrivate GolemFuncPrivate;

struct _GolemFuncPrivate
{
  GolemFuncMetaData * meta_data;
  gpointer address;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemFunc,golem_func,G_TYPE_OBJECT)

gboolean
_golem_func_invoke_real(GolemFunc * func,GValue ** args,GValue * result,GError ** error)
{
  struct GolemArgReference
  {
    GValue * arg;
    gpointer ref;
  };

  GolemFuncPrivate * priv = golem_func_get_instance_private(func);
  GolemFuncMetaData * meta_data = priv->meta_data;
  GError * catch = NULL;
  gboolean done = TRUE;
  GolemArgs * v_args = golem_args_new();
  guint i_args = 0;
  gsize n_args = g_strv_length((gchar**)args);

  for(GList * iter = g_list_first(meta_data->params);iter;iter = g_list_next(iter))
    {
      GolemFuncParam * param = (GolemFuncParam*)iter->data;
      if(param->catch_exception)
	{
	  golem_args_pointer(v_args,&catch);
	}
      else
	{
	  if(i_args >= n_args)
	    break;
	  if(param->is_reference)
	    {
	      golem_args_pointer(v_args,&(args[i_args]->data[0]));
	    }
	  else if((args[i_args]->g_type == param->type)||(g_type_is_a(args[i_args]->g_type,param->type)))
	    {
	      golem_args_append(v_args,args[i_args]);
	    }
	  else
	    {
	      //TODO: invalid cast error
	    }
	  i_args ++;
	}
    }

  for(;i_args < n_args;i_args++)
    {
      golem_args_append(v_args,args[i_args]);
    }

  gpointer address = golem_func_get_address(func);
  GType fundamental_return  = G_TYPE_FUNDAMENTAL(meta_data->return_type);
  if(meta_data->return_type != G_TYPE_NONE)
    g_value_init(result,meta_data->return_type);
  switch(fundamental_return)
  {
    case G_TYPE_BOOLEAN:
      g_value_set_boolean(result,golem_invoke_gint(address,v_args));
      break;
    case G_TYPE_INT:
      g_value_set_int(result,golem_invoke_gint(address,v_args));
      break;
    case G_TYPE_POINTER:
      g_value_set_pointer(result,golem_invoke_gpointer(address,v_args));
      break;
    default:
      golem_invoke(address,v_args);
      break;
  }
  golem_args_free(v_args);
  return done;
}

gpointer
_golem_func_get_address_real(GolemFunc * func)
{
  GolemFuncPrivate * priv = golem_func_get_instance_private(func);
  return priv->address;
}

static void
golem_func_init(GolemFunc * self)
{
  GolemFuncPrivate * priv = golem_func_get_instance_private(self);
  priv->meta_data = NULL;
  priv->address = NULL;
}

static void
golem_func_class_init(GolemFuncClass * klass)
{
  klass->invoke = _golem_func_invoke_real;
  klass->get_address = _golem_func_get_address_real;
}

GolemFunc *
golem_func_new(GolemFuncMetaData * meta_data,gpointer address)
{
  GolemFunc * self = GOLEM_FUNC(g_object_new(GOLEM_TYPE_FUNC,NULL));
  GolemFuncPrivate * priv = golem_func_get_instance_private(self);
  priv->meta_data = meta_data;
  priv->address = address;
  return self;
}

gboolean
golem_func_invoke(GolemFunc * func,GValue ** args,GValue * result,GError ** error)
{
  GolemFuncClass * klass = GOLEM_FUNC_GET_CLASS(func);
  return klass->invoke(func,args,result,error);
}

gpointer
golem_func_get_address(GolemFunc * func)
{
  GolemFuncClass * klass = GOLEM_FUNC_GET_CLASS(func);
  return klass->get_address(func);
}


GolemFuncMetaData *
golem_func_meta_data_new()
{
  GolemFuncMetaData * self = g_new0(GolemFuncMetaData,1);
  self->params = NULL;
  self->return_type = G_TYPE_NONE;
  self->return_type_name = NULL;
  self->is_resolved = TRUE;
  self->name = NULL;
  return self;
}

GolemFuncMetaData *
golem_func_meta_data_parse(GolemParser * parser,GError ** error)
{
  GolemFuncMetaData * meta_data = golem_func_meta_data_new();
  gboolean done = TRUE;
  meta_data->is_resolved = FALSE;
  if(golem_parser_check_is_named(parser))
    {
      meta_data->return_type_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
      if(golem_parser_check_is_named(parser))
	{
	  meta_data->name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
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
			      GolemFuncParam * param = g_new0(GolemFuncParam,1);
			      param->catch_exception = FALSE;
			      param->is_array = is_array;
			      param->is_reference = is_reference;
			      param->name = g_strdup(name);
			      param->type_name = g_strdup(type_name);
			      param->type = G_TYPE_NONE;
			      meta_data->params = g_list_append(meta_data->params,param);
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
	      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"was expected \"(\"");
	    }
	}
    }
  else
    {
      done = FALSE;
      golem_throw(error,GOLEM_SYNTAXIS_ERROR,"the name of the function was expected");
    }
  if(!done)
    {
      g_print("FREE FOR ERROR");

      //TODO: free the meta_data and set to NULL
    }
  return meta_data;
}

void
golem_func_meta_data_set_return_type(GolemFuncMetaData * meta_data,GType return_type)
{
  meta_data->return_type = return_type;
}

GType
golem_func_meta_data_get_return_type(GolemFuncMetaData * meta_data)
{
  return meta_data->return_type;
}

void
golem_func_meta_data_add_param(GolemFuncMetaData * meta_data,const gchar * name,GType type,gboolean is_reference,gboolean is_array)
{
  GolemFuncParam * param = g_new0(GolemFuncParam,1);
  param->name = g_strdup(name);
  param->type = type;
  param->is_array = is_array;
  param->is_reference = is_reference;
  param->catch_exception = FALSE;
  meta_data->params = g_list_append(meta_data->params,param);
}

void
golem_func_meta_data_catch_exception(GolemFuncMetaData * meta_data)
{
  GolemFuncParam * param = g_new0(GolemFuncParam,1);
  param->name = NULL;
  param->type = G_TYPE_ERROR;
  param->is_array = FALSE;
  param->is_reference = TRUE;
  param->catch_exception = TRUE;
  meta_data->params = g_list_append(meta_data->params,param);
}

const gchar *
golem_func_meta_data_get_name(GolemFuncMetaData * meta_data)
{
  return meta_data->name;
}

gboolean
golem_func_meta_data_resolve(GolemFuncMetaData * meta_data,GError ** error)
{
  gboolean done = TRUE;
  if(!meta_data->is_resolved)
    {
      meta_data->return_type = golem_resolve_type_name(meta_data->return_type_name);
      if(meta_data->return_type_name)
	{
	  for(GList * iter = g_list_first(meta_data->params);iter;iter = g_list_next(iter))
	    {
	      GolemFuncParam * param = (GolemFuncParam *)iter->data;
	      param->type = golem_resolve_type_name(param->type_name);
	      if(!param->type)
		{
		  //TODO: throw unknown type
		  done = FALSE;
		  break;
		}
	    }
	}
      else
	{
	  //TODO: throw error unknown type
	  done = FALSE;
	}
    }
  return done;
}
