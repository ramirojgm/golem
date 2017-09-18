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

typedef struct _GolemParameter GolemParameter;

struct _GolemParameter
{
  gchar * name;
  GolemExpression * value;
};

struct _GolemNewPrivate
{
  gboolean referenced;
  gchar * type_name;
  GList * params;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemNew,golem_new,GOLEM_TYPE_EXPRESSION)

static gboolean
_golem_new_evaluate(GolemExpression * expression,GolemContext * context,GValue * result,GError ** error)
{
  GolemNew * self = GOLEM_NEW(expression);
  gboolean done = TRUE;
  GParameter * params_construct = NULL;
  GParameter * params_data = NULL;
  guint params_construct_n,params_data_n;
  GType type = 0;

  if(self->priv->type_name)
    {
      type = golem_type_from_name(self->priv->type_name);
      if(type == 0)
	{
	  done = FALSE;
	  golem_runtime_error(error,
			      GOLEM_UNKNOWN_TYPE_ERROR,
			      "unknown type \"%s\"",
			      self->priv->type_name);
	}
    }
  else
    {
      type = G_TYPE_OBJECT;
    }

  if(done)
    {
      if(G_TYPE_IS_OBJECT(type))
	{
	  GObjectClass * klass = G_OBJECT_CLASS(g_type_class_ref(type));
	  params_construct_n = 0;
	  params_data_n = 0;
	  params_construct = g_new0(GParameter,g_list_length(self->priv->params));
	  params_data = g_new0(GParameter,g_list_length(self->priv->params));

	  for(GList * param_iter = g_list_first(self->priv->params);param_iter;param_iter = g_list_next(param_iter))
	  {
	    GolemParameter * param_exp = (GolemParameter*)(param_iter->data);
	    GParamSpec * param = NULL;
	    if(klass)
	      param = g_object_class_find_property(klass,param_exp->name);
	    if(param && klass)
	      {
		params_construct[params_construct_n].name = g_strdup(param_exp->name);
		if(!(done = golem_expression_evaluate(param_exp->value,context,&(params_construct[params_construct_n].value),error)))
		  {
		    break;
		  }
		params_construct_n ++;
	      }
	    else
	      {
		params_data[params_data_n].name = g_strdup(param_exp->name);
		if(!(done = golem_expression_evaluate(param_exp->value,context,&(params_data[params_data_n].value),error)))
		  {
		    break;
		  }
		params_data_n ++;
	      }
	  }
	  if(done)
	  {
	    gpointer instance = g_object_newv(type,params_construct_n,params_construct);
	    for(guint params_index = 0;params_index < params_data_n;params_index++)
	      {
		if(!(params_data[params_index].name))
		  break;
		GValue * param_value = g_new0(GValue,1);
		g_value_init(param_value,(params_data[params_index].value).g_type);
		g_value_copy(&(params_data[params_index].value),param_value);
		g_object_set_data_full(instance,params_data[params_index].name,param_value,(GDestroyNotify)g_value_free);
	      }
	    g_value_init(result,type);
	    if(self->priv->referenced)
	      g_value_set_object(result,instance);
	    else
	      g_value_take_object(result,instance);
	  }

	  for(gint params_index = 0;params_index < params_construct_n;params_index ++)
	  {
	    g_free((gchar*)params_construct[params_index].name);
	    g_value_unset(&params_construct[params_index].value);
	  }

	  g_free(params_construct);

	  for(gint params_index = 0;params_index < params_data_n;params_index ++)
	  {
	    g_free((gchar*)params_data[params_index].name);
	    g_value_unset(&params_data[params_index].value);
	  }

	  g_free(params_data);
	}
      else if(G_TYPE_IS_BOXED(type))
	{
	  g_value_init(result,type);
	  g_value_take_boxed(result,g_malloc0(1024));
	  done = TRUE;
	}
      else
	{
	  g_value_init(result,G_TYPE_POINTER);
	  g_value_set_pointer(result,NULL);
	  done = TRUE;
	}
    }
  return done;
}

static void
golem_new_init(GolemNew * self)
{
  self->priv = golem_new_get_instance_private(self);
  self->priv->params = NULL;
  self->priv->type_name = NULL;
}

static void
golem_new_class_init(GolemNewClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = _golem_new_evaluate;
  //TODO: add dispose
}

gboolean
golem_new_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"new");
}

GolemExpression *
golem_new_parse(GolemParser * parser,GError ** error)
{
  GolemNew * expression = GOLEM_NEW(g_object_new(GOLEM_TYPE_NEW,NULL));
  gboolean done = TRUE;
  if((done = golem_parser_next_word_check(parser,"new")))
    {
      if(golem_parser_next_word_check(parser,"@"))
	{
	  expression->priv->referenced = TRUE;
	}

      if(golem_parser_check_is_named(parser))
	{
	  expression->priv->type_name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
	}
      if(done)
	{
	  if(golem_parser_next_word_check(parser,"{"))
	    {
	      while(!golem_parser_next_word_check(parser,"}"))
		{
		  gchar * name = NULL;
		  if(golem_parser_check_is_named(parser))
		    {
		      name = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
		      for(gchar * nchar = name;*nchar;nchar++)
			{
			  if(*nchar == '_')
			    *nchar = '-';
			}
		    }
		  else if(golem_parser_check_is_string(parser))
		    {
		      const gchar * str = golem_parser_next_word(parser,NULL,TRUE);
		      name = g_strndup(str + 1,g_utf8_strlen(str,-1) - 2);
		    }

		  if(name)
		    {
		      if((done = golem_parser_next_word_check(parser,":")))
			{
			  GolemParameter * param = g_new0(GolemParameter,1);
			  param->name = name;
			  param->value = golem_expression_complex_parse(parser,GOLEM_EXPRESSION_LIMIT_BRACKET_COMA,error);
			  expression->priv->params = g_list_append(expression->priv->params,param);
			}
		      else
			{
			  golem_parser_error(error,parser,"was expected \":\"");
			  break;
			}
		    }
		  else
		    {
		      done = FALSE;
		      golem_parser_error(error,parser,"was expected name");
		      break;
		    }

		  if(!golem_parser_next_word_check(parser,",") && golem_parser_next_word_check(parser,"}"))
		    break;
		}
	    }
	}
    }
  return GOLEM_EXPRESSION(expression);
}
