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

#ifndef GOLEM_FUNCTION_H_
#define GOLEM_FUNCTION_H_

#define GOLEM_TYPE_FUNCTION	(golem_function_get_type())
G_DECLARE_DERIVABLE_TYPE(GolemFunction,golem_function,GOLEM,FUNCTION,GolemMetadata)

typedef struct _GolemParamSpec GolemParamSpec;

struct _GolemParamSpec
{
  GolemMetadata * 	type;
  gchar * 		name;
};

struct _GolemFunctionClass
{
  GolemMetadataClass parent_class;

  gboolean	  (*call)(GolemFunction * function,
			  GolemValue * 	self,
			  guint32 	argc,
			  GolemValue * 	argv,
			  GolemValue * 	ret,
			  GError ** error);
};


G_BEGIN_DECLS

GolemMetadata	* golem_function_get_return_type(GolemFunction * function);

GolemTransferMode golem_function_get_transfer_mode(GolemFunction * function);

const gchar *	  golem_function_get_link_name(GolemFunction * function);

const GolemParamSpec **
		  golem_function_get_args(GolemFunction * function,
					  gsize * args_count);

gboolean	  golem_function_call(GolemFunction * function,
				      GolemValue *	self,
				      guint32 		argc,
				      GolemValue * 	argv,
				      GolemValue *	ret,
				      GError ** 	error);

G_END_DECLS

#endif /* GOLEM_FUNCTION_H_ */
