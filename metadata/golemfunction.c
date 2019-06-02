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


#include <golem.h>

typedef struct _GolemFunctionPrivate GolemFunctionPrivate;

struct _GolemFunctionPrivate
{
  GolemMetadata * 	m_return_type;
  GolemTransferMode 	n_transfer_mode;
  gchar * 		m_link_name;
  GolemParamSpec **	m_args;
  gsize 		n_args;

};

enum {
  GOLEM_FUNCTION_PROP_RETURN_TYPE = 1,
  GOLEM_FUNCTION_PROP_TRANSFER_MODE,
  GOLEM_FUNCTION_PROP_LINK_NAME,
  GOLEM_FUNCTION_PROP_ARGS,
  GOLEM_FUNCTION_N_PROP,
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemFunction,golem_function,GOLEM_TYPE_METADATA)

gboolean
golem_function_call_default (GolemFunction * 	function,
			      GolemValue *	self,
			      guint32 		argc,
			      GolemValue * 	argv,
			      GolemValue * 	ret,
			      GError ** 	error)
{
  GOLEM_INT32(ret) = 0;
  g_set_error(error,
	      GOLEM_ERROR,
	      GOLEM_ERROR_NOT_IMPLEMENTED,
	      "Function unimplemented");
  return FALSE;
}

static void
golem_function_set_property(GObject * obj,
			    guint property_id,
			    const GValue * src,
			    GParamSpec * pspec)
{
  g_assert_nonnull(obj);
  g_assert(GOLEM_IS_FUNCTION(obj));

  GolemFunctionPrivate *
  priv = golem_function_get_instance_private(GOLEM_FUNCTION(obj));

  switch (property_id)
  {
    case GOLEM_FUNCTION_PROP_RETURN_TYPE:
      g_clear_object(&priv->m_return_type);
      priv->m_return_type = g_value_dup_object(src);
      break;
    case GOLEM_FUNCTION_PROP_TRANSFER_MODE:
      priv->n_transfer_mode = g_value_get_enum(src);
      break;
    case GOLEM_FUNCTION_PROP_LINK_NAME:
      g_clear_pointer(&priv->m_link_name,g_free);
      priv->m_link_name = g_value_dup_string(src);
      break;
    case GOLEM_FUNCTION_PROP_ARGS:
      priv->m_args = (GolemParamSpec **)(g_value_get_pointer(src));
      priv->n_args = 0;
      if (priv->m_args)
	  priv->n_args = g_strv_length((gchar**)priv->m_args);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,pspec);
  }
}

static void
golem_function_get_property(GObject * obj,
			    guint property_id,
			    GValue * dest,
			    GParamSpec * pspec)
{
  g_assert_nonnull(obj);
  g_assert(GOLEM_IS_FUNCTION(obj));

  GolemFunctionPrivate *
  priv = golem_function_get_instance_private(GOLEM_FUNCTION(obj));

  switch (property_id)
  {
    case GOLEM_FUNCTION_PROP_RETURN_TYPE:
      g_value_set_object(dest,priv->m_return_type);
      break;
    case GOLEM_FUNCTION_PROP_TRANSFER_MODE:
      g_value_set_enum(dest,priv->n_transfer_mode);
      break;
    case GOLEM_FUNCTION_PROP_LINK_NAME:
      g_value_set_string(dest,priv->m_link_name);
      break;
    case GOLEM_FUNCTION_PROP_ARGS:
      g_value_set_pointer(dest,priv->m_args);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,pspec);
  }
}


static void
golem_function_init(GolemFunction * self)
{
  GolemFunctionPrivate *
  priv = golem_function_get_instance_private(self);

  priv->m_link_name = NULL;
  priv->m_return_type = NULL;
  priv->n_transfer_mode = GOLEM_TRANSFER_NONE;
}

static void
golem_function_class_init(GolemFunctionClass * klass)
{
  static GParamSpec * properties[GOLEM_FUNCTION_N_PROP] = {0,};

  klass->call =  golem_function_call_default;

  properties[GOLEM_FUNCTION_PROP_RETURN_TYPE] =
      g_param_spec_object("return-type",
			  "Return type",
			  "Describe the return type",
			  GOLEM_TYPE_METADATA,
			  G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  properties[GOLEM_FUNCTION_PROP_LINK_NAME] =
      g_param_spec_string("link-name",
			  "Link name",
			  "Link name",
			  "",
			  G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  properties[GOLEM_FUNCTION_PROP_TRANSFER_MODE] =
      g_param_spec_enum("transfer-mode",
			"Transfer mode",
			"Return transfer mode",
			GOLEM_TYPE_TRANSFER_MODE,
			GOLEM_TRANSFER_NONE,
			G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  properties[GOLEM_FUNCTION_PROP_ARGS] =
      g_param_spec_pointer("args",
			    "Args",
			    "Arguments",
			    G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);


  G_OBJECT_CLASS(klass)->set_property = golem_function_set_property;
  G_OBJECT_CLASS(klass)->get_property = golem_function_get_property;


  g_object_class_install_properties(G_OBJECT_CLASS(klass),
				    GOLEM_FUNCTION_N_PROP,
				    properties);
}

GolemMetadata	*
golem_function_get_return_type(GolemFunction * function)
{
  g_assert_nonnull(function);

  GolemFunctionPrivate *
  priv = golem_function_get_instance_private(function);

  return priv->m_return_type;
}

GolemTransferMode
golem_function_get_transfer_mode(GolemFunction * function)
{
  g_assert_nonnull(function);

  GolemFunctionPrivate *
  priv = golem_function_get_instance_private(function);

  return priv->n_transfer_mode;
}

const gchar *
golem_function_get_link_name(GolemFunction * function)
{
  g_assert_nonnull(function);

  GolemFunctionPrivate *
  priv = golem_function_get_instance_private(function);

  return priv->m_link_name;
}

const GolemParamSpec **
golem_function_get_args(GolemFunction * function,
			gsize * args_count)
{
  g_assert_nonnull(function);
  GolemFunctionPrivate *
  priv = golem_function_get_instance_private(function);

  if (args_count)
    *args_count = priv->n_args;

  return (const GolemParamSpec**)priv->m_args;
}


gboolean
golem_function_call(GolemFunction * function,
		      GolemValue * 	self,
		      guint32 		argc,
		      GolemValue * 	argv,
		      GolemValue *	ret,
		      GError ** 	error)
{
  g_assert_nonnull(function);
  GolemFunctionClass * klass = GOLEM_FUNCTION_GET_CLASS(function);

  return klass->call(function,self,argc,argv,ret,error);

}
