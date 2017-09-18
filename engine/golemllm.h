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

#ifndef GOLEMLLM_H_
#define GOLEMLLM_H_

typedef struct _GolemLLMInvoke GolemLLMInvoke;

typedef void (*GolemLLMVFunc)(gpointer instance,GolemLLMInvoke * invoke,gpointer data);

struct _GolemLLMInvoke
{
  va_list * 	va_args;
  union _gresult result;
};

gpointer	golem_llm_new_vfunction(GolemLLMVFunc func,gpointer data);
void		golem_llm_dispose_vfunction(gpointer vfunc);

guint8		golem_llm_invoke_get_guint8(GolemLLMInvoke * invoke);
guint		golem_llm_invoke_get_guint(GolemLLMInvoke * invoke);
guint64		golem_llm_invoke_get_guint64(GolemLLMInvoke * invoke);
gulong		golem_llm_invoke_get_gulong(GolemLLMInvoke * invoke);
gint8		golem_llm_invoke_get_gint8(GolemLLMInvoke * invoke);
gint		golem_llm_invoke_get_gint(GolemLLMInvoke * invoke);
gint64		golem_llm_invoke_get_gint64(GolemLLMInvoke * invoke);
glong		golem_llm_invoke_get_glong(GolemLLMInvoke * invoke);
gfloat		golem_llm_invoke_get_gfloat(GolemLLMInvoke * invoke);
gdouble		golem_llm_invoke_get_gdouble(GolemLLMInvoke * invoke);
gpointer	golem_llm_invoke_get_gpointer(GolemLLMInvoke * invoke);
const va_list *	golem_llm_invoke_get_va_list(GolemLLMInvoke * invoke);

void		golem_llm_invoke_set_result(GolemLLMInvoke * invoke,gresult * result);

#endif /* GOLEMLLM_H_ */
