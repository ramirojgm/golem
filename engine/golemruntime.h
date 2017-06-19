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

#ifndef ENGINE_GOLEMRUNTIME_H_
#define ENGINE_GOLEMRUNTIME_H_

typedef struct _GolemRuntime GolemRuntime;
typedef enum _GolemRuntimeType GolemRuntimeType;

enum _GolemRuntimeType
{
  GOLEM_RUNTIME_LOCAL,
  GOLEM_RUNTIME_LOOP,
  GOLEM_RUNTIME_FUNCTION
};

struct _GolemRuntime
{
  GList *	contexts;
  gint	 	stop;
  GValue 	return_val;
};

GolemRuntime * 	golem_runtime_new(GolemContext * context);

void		golem_runtime_enter(GolemRuntime * runtime,GolemRuntimeType type);

GolemContext *	golem_runtime_get_context(GolemRuntime * runtime);

gboolean	golem_runtime_get_return(GolemRuntime * runtime,GValue * dest);

gboolean	golem_runtime_running(GolemRuntime * runtime);

gboolean	golem_runtime_break(GolemRuntime * runtime);

gboolean	golem_runtime_continue(GolemRuntime * runtime);

void		golem_runtime_return(GolemRuntime * runtime,const GValue * value);

void		golem_runtime_exit(GolemRuntime * runtime);

#endif /* ENGINE_GOLEMRUNTIME_H_ */
