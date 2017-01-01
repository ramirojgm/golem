/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef ENGINE_GOLEMINVOKE_H_
#define ENGINE_GOLEMINVOKE_H_

typedef struct _GolemInvokePrivate GolemInvokePrivate;

#define GOLEM_TYPE_INVOKE (golem_invoke_get_type())
G_DECLARE_FINAL_TYPE(GolemInvoke,golem_invoke,GOLEM,INVOKE,GolemExpression)

struct _GolemInvokeClass
{
  GolemExpressionClass parent_class;
};

struct _GolemInvoke
{
  GolemExpression parent_instance;
  GolemInvokePrivate * priv;
};

GType			golem_invoke_get_type(void);

gboolean		golem_invoke_check(GolemParser * parser);

GolemExpression * 	golem_invoke_parse(GolemParser * parser,GolemExpression * expression,GError ** error);

#endif /* ENGINE_GOLEMIDENTIFICATOR_H_ */
