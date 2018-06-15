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

typedef struct _GolemFunctionInfoPrivate GolemFunctionInfoPrivate;
struct _GolemFunctionInfoPrivate
{
  GolemArgument ** m_arguments;
  guint16 n_arguments;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemFunctionInfo,golem_function_info,GOLEM_TYPE_METADATA)

static void
golem_function_info_init(GolemFunctionInfo * self)
{

}

static void
golem_function_info_class_init(GolemFunctionInfoClass * klass)
{

}
