/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

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

#ifndef GOLEMBUILTININFO_H_
#define GOLEMBUILTININFO_H_

#define GOLEM_TYPE_BUILTIN_INFO	(golem_builtin_info_get_type())
G_DECLARE_FINAL_TYPE(GolemBuiltinInfo,golem_builtin_info,GOLEM,BUILTIN_INFO,GolemTypeInfo)

typedef struct _GolemBuiltinInfoPrivate GolemBuiltinInfoPrivate;
typedef struct _GolemBuiltinSpec GolemBuiltinSpec;


struct _GolemBuiltinInfoClass
{
  GolemTypeInfoClass parent_class;
};

struct _GolemBuiltinInfo
{
  GolemTypeInfo parent_instance;
  GolemBuiltinInfoPrivate * priv;
};

struct _GolemBuiltinSpec
{

};



GType			golem_builtin_info_get_type(void);

GolemBuiltinInfo* 	golem_builtin_info_new(GType type,
					       const GolemBuiltinSpec * spec);


#endif
