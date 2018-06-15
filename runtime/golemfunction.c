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

typedef struct _GolemFunctionPrivate GolemFunctionPrivate;

struct _GolemFunctionPrivate
{
  gpointer instance;
  gpointer native;
  GolemFunctionInfo * info;
};

G_DEFINE_ABSTRACT_TYPE(GolemFunction,golem_function,G_TYPE_OBJECT)

enum GolemFunctionProps
{
  GOLEM_FUNCTION_PROP_0,
  GOLEM_FUNCTION_PROP_INSTANCE,
  GOLEM_FUNCTION_PROP_INFO,
  GOLEM_FUNCTION_PROP_NATIVE,
  GOLEM_FUNCTION_PROP_N
};

static GParamSpec *_golem_function_properties[GOLEM_FUNCTION_PROP_N] = {0,};

static void
golem_function_init(GolemFunction * self)
{

}

static gboolean
golem_function_real_invoke(GolemFunction * func,
			   guint8 argc,
			   GolemVMData * argv,
			   GolemVMData * ret,
			   GError ** error)
{
  g_propagate_error(error,
		    g_error_new(GOLEM_ERROR,
				GOLEM_RUNTIME_ERROR_NOT_IMPLEMENTED_YET,
				"not implemented yet")
				);
  return FALSE;
}

static void
_golem_function_set_property(GObject        *object,
                             guint           property_id,
                             const GValue   *value,
                             GParamSpec     *pspec)
{
  GolemFunctionPrivate * priv = golem_function_get_instance_private(GOLEM_FUNCTION(object));
  switch(property_id)
  {
    case GOLEM_FUNCTION_PROP_INSTANCE:
      g_clear_object(&(priv->instance));
      priv->instance = g_value_get_object(value);
      break;
    case GOLEM_FUNCTION_PROP_NATIVE:
      priv->native = g_value_get_pointer(value);
      break;
    case GOLEM_FUNCTION_PROP_INFO:
      g_clear_object(&(priv->info));
      priv->info = g_value_dup_object(value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
  }
}

static void
_golem_function_get_property(GObject        *object,
                             guint           property_id,
                             GValue	    *value,
                             GParamSpec     *pspec)
{
  GolemFunctionPrivate * priv = golem_function_get_instance_private(GOLEM_FUNCTION(object));
  switch(property_id)
  {
    case GOLEM_FUNCTION_PROP_INSTANCE:
      g_value_set_object(value,priv->instance);
      break;
    case GOLEM_FUNCTION_PROP_NATIVE:
      g_value_set_pointer(value,priv->native);
      break;
    case GOLEM_FUNCTION_PROP_INFO:
      g_value_set_object(value,priv->info);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
  }
}

static void
golem_function_class_init(GolemFunctionClass * klass)
{
  klass->invoke = golem_function_real_invoke;

  _golem_function_properties[GOLEM_FUNCTION_PROP_INSTANCE] =
      g_param_spec_object("instance","instance","Instance",G_TYPE_OBJECT,G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  _golem_function_properties[GOLEM_FUNCTION_PROP_NATIVE] =
      g_param_spec_pointer("native","native","Native function",G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  _golem_function_properties[GOLEM_FUNCTION_PROP_INFO] =
      g_param_spec_object("function-info","Function Info","Function Info",GOLEM_TYPE_FUNCTION_INFO,G_PARAM_CONSTRUCT_ONLY|G_PARAM_READWRITE);

  G_OBJECT_CLASS(klass)->set_property = _golem_function_set_property;
  G_OBJECT_CLASS(klass)->get_property = _golem_function_get_property;
}

GolemFunctionInfo *
golem_function_get_info(GolemFunction * func)
{
  GolemFunctionPrivate * priv = golem_function_get_instance_private(func);
  return priv->info;
}

gpointer
golem_function_get_instance(GolemFunction * func)
{
  GolemFunctionPrivate * priv = golem_function_get_instance_private(func);
  return priv->instance;
}

gpointer
golem_function_get_symbol(GolemFunction * func)
{
  GolemFunctionPrivate * priv = golem_function_get_instance_private(func);
  return priv->native;
}

gboolean
golem_function_invoke(GolemFunction * func,
		      guint16 argc,
		      GolemVMData * argv,
		      GolemVMData * ret,
		      GError ** error)
{
  GolemFunctionClass * klass = GOLEM_FUNCTION_GET_CLASS(func);
  return klass->invoke(func,argc,argv,ret,error);
}

GClosure *
golem_function_create_closure(GolemFunction * func)
{
  return NULL;
}
