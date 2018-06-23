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

#ifndef GOLEMFUNCTIONTYPE_H_
#define GOLEMFUNCTIONTYPE_H_

#define GOLEM_TYPE_FUNCTION_TYPE	(golem_function_type_get_type())

G_DECLARE_DERIVABLE_TYPE(GolemFunctionType,golem_function_type,GOLEM,FUNCTION_TYPE,GolemMetadata)

struct _GolemFunctionTypeClass
{
  GolemMetadataClass parent_class;

};

GolemFunctionType*	golem_function_type_new(GolemType * ret_type,guint16 argc,GolemType ** argv,gint throw_error);

GolemType		golem_function_type_

gboolean		golem_function_type_get_throw_error(GolemFunctionType * func_type);

GolemType**		golem_function_type_get_arguments(GolemFunctionType * func_type,
							  gsize * length);


#endif /* GOLEMFUNCTIONTYPE_H_ */
