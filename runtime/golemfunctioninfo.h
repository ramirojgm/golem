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

#ifndef GOLEMFUNCTIONINFO_H_
#define GOLEMFUNCTIONINFO_H_

#define GOLEM_TYPE_FUNCTION_INFO	(golem_function_info_get_type())

G_DECLARE_DERIVABLE_TYPE(GolemFunctionInfo,golem_function_info,GOLEM,FUNCTION_INFO,GolemMetadata)

typedef struct _GolemArgument GolemArgument;
typedef enum _GolemArgumentFlags GolemArgumentFlags;

enum _GolemArgumentFlags
{
  GOLEM_ARGUMENT_IN,
  GOLEM_ARGUMENT_OUT
};

struct _GolemArgument
{
  GolemTypeInfo * 	type;
  gchar * 	  	name;
  GolemArgumentFlags	flags;
};

struct _GolemFunctionInfoClass
{
  GolemMetadataClass parent_class;

  gboolean (*invoke)(GolemFunctionInfo * func,
		    GolemVMScope * scope,
		    gpointer instance,
		    guint8 argc,
		    GolemVMData * argv,
		    GolemVMData * ret,
		    GError ** error);
};

gboolean golem_function_info_invoke(GolemFunctionInfo * func,
				    GolemVMScope * scope,
				    gpointer instance,
				    guint8 argc,
				    GolemVMData * argv,
				    GolemVMData * ret,
				    GError ** error);


#endif /* GOLEMFUNCTIONINFO_H_ */
