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
#include <gmodule.h>
#include <ffi.h>

struct _GolemSymbolPrivate
{
  GolemMetadata * m_instance_type;
  gpointer 	  m_symbol;
  ffi_cif  	  n_cif;
  ffi_type ** 	  m_types;
};

enum {
  GOLEM_SYMBOL_PROP_INSTANCE_TYPE = 1,
  GOLEM_SYMBOL_N_PROP
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemSymbol,golem_symbol,GOLEM_TYPE_FUNCTION)

static void
golem_symbol_get_property(GObject * obj,
			  guint property_id,
			  GValue * dest,
			  GParamSpec * pspec)
{
  GolemSymbol * self = GOLEM_SYMBOL(obj);
  switch(property_id)
  {
    case GOLEM_SYMBOL_PROP_INSTANCE_TYPE:
      g_value_set_object(dest,self->priv->m_instance_type);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,pspec);
  }

}

static void
golem_symbol_set_property(GObject * obj,
			  guint property_id,
			  const GValue * src,
			  GParamSpec * pspec)
{
  GolemSymbol * self = GOLEM_SYMBOL(obj);
  switch(property_id)
  {
    case GOLEM_SYMBOL_PROP_INSTANCE_TYPE:
      g_clear_object(&self->priv->m_instance_type);
      self->priv->m_instance_type = g_value_dup_object(src);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(obj,property_id,pspec);
  }
}


static gboolean
golem_symbol_call(GolemFunction * function,
		  GolemValue * 	self,
		  guint32 	argc,
		  GolemValue * 	argv,
		  GolemValue * 	ret,
		  GError ** error)
{
    GolemSymbol * symbol = GOLEM_SYMBOL(function);
    ffi_arg result;

    gsize args_count = 0;
    golem_function_get_args(function,&args_count);

    g_assert_true(argc == args_count);

    if (symbol->priv->m_symbol == NULL)
      {
	GModule * global_mod = g_module_open(NULL,G_MODULE_BIND_LOCAL);
	if (!g_module_symbol(global_mod,
		      golem_function_get_link_name(function),
		      &symbol->priv->m_symbol))
	  {
	    g_set_error(error,
			GOLEM_ERROR,
			GOLEM_ERROR_NOT_IMPLEMENTED,
			"symbol not found");
	    return FALSE;
	  }
      }

    gpointer * args_values = NULL;
    guint index = 0;

    if (symbol->priv->m_instance_type)
      {
	argc += 1;
	index = 1;
	args_values = g_new(gpointer,argc);
	args_values[0] = self;
      }
    else
      {
	args_values = g_new(gpointer,argc);
      }

    for (; index < argc; index ++)
      args_values[index] = &(argv[index]);


    ffi_call(&symbol->priv->n_cif,
	     FFI_FN(symbol->priv->m_symbol),
	     &result,
	     args_values);

    GOLEM_INT128(ret) = result;
    return TRUE;
}

GolemMetadata *
golem_symbol_new(GolemMetadata * instance_type,
		 const gchar * name,
		 GolemMetadata * return_type,
		 GolemTransferMode transfer_mode,
		 const gchar * symbol_name,
		 const GolemParamSpec ** args)
{


  return GOLEM_METADATA(
      g_object_new(GOLEM_TYPE_SYMBOL,
		   "name",name,
		   "return-type",return_type,
		   "transfer-mode",transfer_mode,
		   "link-name",symbol_name,
		   "args",args,
		   "instance-type",instance_type,
		   NULL));
}

static void
golem_symbol_init(GolemSymbol * self)
{
  self->priv = golem_symbol_get_instance_private(self);
}

static ffi_type *
golem_symbol_type_to_native(GolemMetadata * type)
{
  if (type == NULL)
    return &ffi_type_void;

  if (GOLEM_IS_PRIMITIVE(type))
    {
      switch(golem_primitive_get_primitive_type(
	  GOLEM_PRIMITIVE(type)))
      {
	case GOLEM_PRIMITIVE_TYPE_CHAR:
	  return &ffi_type_schar;
	case GOLEM_PRIMITIVE_TYPE_UCHAR:
	  return &ffi_type_uchar;
	case GOLEM_PRIMITIVE_TYPE_INT8:
	  return &ffi_type_sint8;
	case GOLEM_PRIMITIVE_TYPE_UINT8:
	  return &ffi_type_uint8;
	case GOLEM_PRIMITIVE_TYPE_INT16:
	  return &ffi_type_sint16;
	case GOLEM_PRIMITIVE_TYPE_UINT16:
	  return &ffi_type_uint16;
	case GOLEM_PRIMITIVE_TYPE_BOOL:
	case GOLEM_PRIMITIVE_TYPE_INT32:
	  return &ffi_type_sint32;
	case GOLEM_PRIMITIVE_TYPE_UINT32:
	  return &ffi_type_uint32;
	case GOLEM_PRIMITIVE_TYPE_INT64:
	case GOLEM_PRIMITIVE_TYPE_INT128:
	  return &ffi_type_sint64;
	case GOLEM_PRIMITIVE_TYPE_UINT64:
	case GOLEM_PRIMITIVE_TYPE_UINT128:
	  return &ffi_type_uint64;
	case GOLEM_PRIMITIVE_TYPE_FLOAT32:
	  return &ffi_type_float;
	case GOLEM_PRIMITIVE_TYPE_FLOAT64:
	  return &ffi_type_double;
	case GOLEM_PRIMITIVE_TYPE_FLOAT128:
	  return &ffi_type_longdouble;
	case GOLEM_PRIMITIVE_TYPE_POINTER:
	case GOLEM_PRIMITIVE_TYPE_STRING:
	  return &ffi_type_pointer;
      }
    }
  else
    {
      //TODO: Equivalent native for object/struct
      return &ffi_type_pointer;
    }
  return &ffi_type_pointer;
}

static void
golem_symbol_constructed(GObject * object)
{
  GolemSymbol * symbol = (GolemSymbol*)object;

  gsize args_count = 0;
  const GolemParamSpec ** args =
      golem_function_get_args(GOLEM_FUNCTION(object),
			     &args_count);

  ffi_status status;
  ffi_type * rtype = golem_symbol_type_to_native(
      golem_function_get_return_type(GOLEM_FUNCTION(object))
  );
  guint index = 0;

  if (symbol->priv->m_instance_type)
    {
      args_count += 1;
      index = 1;
      symbol->priv->m_types = g_new0(ffi_type*,args_count);
      symbol->priv->m_types[0] =
	  golem_symbol_type_to_native(symbol->priv->m_instance_type);
    }
  else
    {
      symbol->priv->m_types = g_new0(ffi_type*,args_count);
    }


  for (;index < args_count; index ++)
    {
      symbol->priv->m_types[index] =
	  golem_symbol_type_to_native(args[index]->type);
    }


  if ((status = ffi_prep_cif(&symbol->priv->n_cif, FFI_DEFAULT_ABI,
        args_count, rtype, symbol->priv->m_types)) != FFI_OK)
     {
        g_abort();
     }

}

static void
golem_symbol_class_init(GolemSymbolClass * klass)
{
  static GParamSpec * properties[GOLEM_SYMBOL_N_PROP] = {0,};

  properties [GOLEM_SYMBOL_PROP_INSTANCE_TYPE] =
      g_param_spec_object("instance-type",
			  "Instance type",
			  "Instance type",
			  GOLEM_TYPE_METADATA,
			  G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

  G_OBJECT_CLASS(klass)->constructed = golem_symbol_constructed;
  G_OBJECT_CLASS(klass)->get_property = golem_symbol_get_property;
  G_OBJECT_CLASS(klass)->set_property = golem_symbol_set_property;
  GOLEM_FUNCTION_CLASS(klass)->call = golem_symbol_call;

  g_object_class_install_properties(G_OBJECT_CLASS(klass),
				    GOLEM_SYMBOL_N_PROP,
				    properties);
}

