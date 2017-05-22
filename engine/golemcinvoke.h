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

#ifndef ENGINE_GOLEMCINVOKE_H_
#define ENGINE_GOLEMCINVOKE_H_

typedef struct _GolemCInvoke GolemCInvoke;
typedef union _GolemCArgument GolemCArgument;

union _GolemCArgument
{
  gint32 value_gint32;
  gint64 value_gint64;
  guint32 value_guint32;
  guint64 value_guint64;
  gfloat value_gfloat;
  gdouble value_gdouble;
  gpointer value_gpointer;
};

struct _GolemCInvoke
{
  guint8 indexes[8];
  guint8 count;
  GType return_type;
  gboolean return_const;
  GolemCArgument arg0;
  GolemCArgument arg1;
  GolemCArgument arg2;
  GolemCArgument arg3;
  GolemCArgument arg4;
  GolemCArgument arg5;
  GolemCArgument arg6;
  GolemCArgument arg7;
};


GolemCInvoke * 	golem_cinvoke_new(GType return_type,gboolean return_const);

void		golem_cinvoke_push_int(GolemCInvoke * invoke,gint32 value);

void		golem_cinvoke_push_int64(GolemCInvoke * invoke,gint64 value);

void		golem_cinvoke_push_uint(GolemCInvoke * invoke,guint32 value);

void		golem_cinvoke_push_uint64(GolemCInvoke * invoke,guint64 value);

void		golem_cinvoke_push_float(GolemCInvoke * invoke,gfloat value);

void		golem_cinvoke_push_double(GolemCInvoke * invoke,gdouble value);

void		golem_cinvoke_push_pointer(GolemCInvoke * invoke,gpointer value);

void		golem_cinvoke_push_value(GolemCInvoke * invoke,const GValue * value);

void		golem_cinvoke_invoke(GolemCInvoke * invoke,gpointer address,GValue * result);

void		golem_cinvoke_free(GolemCInvoke * invoke);

#endif /* ENGINE_GOLEMCINVOKE_H_ */
