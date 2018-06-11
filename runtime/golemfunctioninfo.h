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

struct _GolemArgument GolemArgument;

struct _GolemArgument
{
  GolemTypeInfo * type;
  gchar * 	  name;
};

struct _GolemFunctionInfoClass
{
  GolemMetadataClass parent_class;

  guint		(*get_argument_count)(GolemFunctionInfo * function_info);
  gchar **	(*get_argument_names)(GolemFunctionInfo * function_info);

};




#endif /* GOLEMFUNCTIONINFO_H_ */
