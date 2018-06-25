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

struct _GolemFunctionWrapPrivate
{
  gpointer padding[5];
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemFunctionWrap,golem_function_wrap,GOLEM_TYPE_FUNCTION)

static void
golem_function_wrap_init(GolemFunctionWrap * self)
{

}

static gboolean
golem_function_wrap_invoke_real(GolemFunction * func,
				guint16 argc,
				GolemVMData * argv,
				GolemVMData * ret,
				GError ** error)
{
  /* function_info */
  gpointer symbol = golem_function_get_symbol(func);
  GolemFunctionType * func_type = golem_function_get_function_type(func);
  guint16 arg_c = 0;
  GolemType ** arg_v = golem_function_type_get_arguments(func_type,&arg_c);

  /* FFI */
  ffi_cif 	cif;
  ffi_type 	**arg_types = g_new0(ffi_type,arg_c);
  void 		**arg_values = g_new0(gpointer,arg_c);

  ffi_status 	status;
  ffi_arg 	result;


  arg_types[0] = &ffi_type_uint;
  arg_types[1] = &ffi_type_float;


     g_free(arg_types);
     g_free(arg_values);

    // Prepare the ffi_cif structure.
     if ((status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI,
         2, &ffi_type_uint8, arg_types)) != FFI_OK)
     {
         // Handle the ffi_status error.
     }

    // Specify the values of each argument.
     unsigned int arg1 = 42;
     float arg2 = 5.1;

    arg_values[0] = &arg1;
     arg_values[1] = &arg2;

    // Invoke the function.
     //ffi_call(&cif, FFI_FN(foo), &result, arg_values);

    // The ffi_arg 'result' now contains the unsigned char returned from foo(),
     // which can be accessed by a typecast.
     //printf("result is %hhu", (unsigned char)result);

    return 0;

  return TRUE;
}

static void
golem_function_wrap_class_init(GolemFunctionWrapClass * klass)
{
  GOLEM_FUNCTION_CLASS(klass)->invoke = golem_function_wrap_invoke_real;
}


GolemFunction *
golem_function_wrap_new(GolemFunctionType * func_type,
			gpointer instance,
			gpointer native)
{
  return GOLEM_FUNCTION(
      g_object_new(GOLEM_TYPE_FUNCTION_WRAP,
		   "function-type",func_type,
		   "instance",instance,
		   "native",native));
}
