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

typedef struct _GolemBuilderStructPrivate GolemBuilderStructPrivate;
typedef struct _GolemFieldInfo GolemFieldInfo;

struct _GolemFieldInfo
{
  gchar * name;
  gchar * type_name;
};

struct _GolemBuilderStructPrivate
{
  GolemStructInfo * type_info;
  GList * fields;
};

struct _GolemBuilderStruct
{
  GolemStatement parent_instance;
  GolemBuilderStructPrivate * priv;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBuilderStruct,golem_builder_struct,GOLEM_TYPE_REGISTER);

gboolean
_golem_builder_struct_register_type(GolemRegister * reg,GolemModule * module,GError ** error)
{
  GolemBuilderStructPrivate * priv = golem_builder_struct_get_instance_private(GOLEM_BUILDER_STRUCT(reg));
  if(priv->fields)
    {
      for(GList * iter = g_list_first(priv->fields); iter; iter = g_list_next(iter))
	{
	  GolemFieldInfo * field_info = (GolemFieldInfo *)iter->data;
	  GType type = golem_type_from_name(field_info->type_name);
	  golem_struct_info_add_field(priv->type_info,type,field_info->name);
	  g_free(field_info->name);
	  g_free(field_info->type_name);
	  g_free(field_info);
	}
      g_list_free(priv->fields);
      priv->fields = NULL;
    }
  return golem_type_info_register_type(GOLEM_TYPE_INFO(priv->type_info),module,error) != 0;
}

static void
golem_builder_struct_init(GolemBuilderStruct * self)
{
  self->priv = golem_builder_struct_get_instance_private(self);
}

static void
golem_builder_struct_class_init(GolemBuilderStructClass * klass)
{
  GOLEM_REGISTER_CLASS(klass)->register_type = _golem_builder_struct_register_type;
}

gboolean
golem_builder_struct_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"struct") || golem_parser_is_next_word(parser,"boxed");
}

GolemBuilderStruct *
golem_builder_struct_parse(GolemParser * parser,GError ** error)
{
  GolemBuilderStruct * self = GOLEM_BUILDER_STRUCT(g_object_new(GOLEM_TYPE_BUILDER_STRUCT,NULL));
  gboolean done = FALSE;
  gboolean copy_full = FALSE;
  if(golem_parser_next_word_check(parser,"struct"))
    {
      done = TRUE;
    }
  else if (golem_parser_next_word_check(parser,"boxed"))
    {
      copy_full = TRUE;
      done = TRUE;
    }

  if(done)
    {
      if(golem_parser_check_is_named(parser))
	{
	  self->priv->type_info = g_object_ref(golem_struct_info_new());
	  golem_struct_info_set_name(self->priv->type_info,golem_parser_next_word(parser,NULL,TRUE));
	  golem_struct_info_set_copy_full(self->priv->type_info,copy_full);

	  if(golem_parser_next_word_check(parser,"{"))
	    {
	      while(!golem_parser_next_word_check(parser,"}"))
		{
		  if(golem_parser_check_is_named(parser))
		    {
		      const gchar * type_name = golem_parser_next_word(parser,NULL,TRUE);
		      if(golem_parser_check_is_named(parser))
			{
			  do
			    {
			      const gchar * field_name = golem_parser_next_word(parser,NULL,TRUE);
			      GolemFieldInfo * field_info = g_new0(GolemFieldInfo,1);
			      field_info->name = g_strdup(field_name);
			      field_info->type_name = g_strdup(type_name);
			      self->priv->fields = g_list_append(self->priv->fields,field_info);
			    }while(golem_parser_next_word_check(parser,","));

			  if(!golem_parser_next_word_check(parser,";"))
			    {
			      done = FALSE;
			      //TODO: add exception
			    }
			}
		    }
		}
	    }
	  else
	    {
	      golem_parser_error(error,parser,"was expected \"{\"");
	      done = FALSE;
	    }
	}
      else
	{
	  //error
	}
    }
  else
    {
      //error
    }

  if(!done)
    {


    }
  return self;
}
