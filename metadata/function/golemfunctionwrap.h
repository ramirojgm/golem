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

#ifndef GOLEM_FUNCTION_WRAP_H_
#define GOLEM_FUNCTION_WRAP_H_

#define GOLEM_TYPE_FUNCTION_WRAP	(golem_function_wrap_get_type())
G_DECLARE_FINAL_TYPE(GolemFunctionWrap,golem_function_wrap,GOLEM,FUNCTION_WRAP,GolemFunction)

typedef struct _GolemFunctionWrapPrivate GolemFunctionWrapPrivate;

struct _GolemFunctionWrapClass
{
  GolemFunctionClass parent_class;
};

struct _GolemFunctionWrap
{
  GolemFunction	parent;

  GolemFunctionWrapPrivate * priv;
};

G_BEGIN_DECLS

GType		golem_function_wrap_get_type(void);

GolemFunction * golem_function_wrap_new(GolemMetadata * 	return_type,
					GolemTransferMode 	transfer_mode,
					const gchar * 		link_name,
					guint 	      		argument_count,
					const gchar ** 		argument_names,
					GolemMetadata ** 	argument_types);

GolemFunction * golem_function_wrap_new_static(GolemMetadata * 	return_type,
					GolemTransferMode 	transfer_mode,
					const gchar * 		link_name,
					guint 	      		argument_count,
					const gchar ** 		argument_names,
					GolemMetadata ** 	argument_types);

G_END_DECLS
#endif /* GOLEM_FUNCTION_WRAP_H_ */
