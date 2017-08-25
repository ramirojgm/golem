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

#include "golem.h"

typedef struct _GolemRuntimeContext GolemRuntimeContext;
typedef enum _GolemRuntimeStop GolemRuntimeStop;

enum _GolemRuntimeStop
{
  GOLEM_RUNTIME_STOP_NONE,
  GOLEM_RUNTIME_STOP_BREAK,
  GOLEM_RUNTIME_STOP_CONTINUE,
  GOLEM_RUNTIME_STOP_RETURN,
};

struct _GolemRuntimeContext
{
  GolemRuntimeType type;
  GolemContext *   context;
};


GolemRuntime *
golem_runtime_new(GolemContext * context)
{
  GolemRuntime * self = g_new0(GolemRuntime,1);
  GolemRuntimeContext * init = g_new0(GolemRuntimeContext,1);
  init->context = GOLEM_CONTEXT(g_object_ref(context));
  init->type = GOLEM_RUNTIME_FUNCTION;
  self->stop = GOLEM_RUNTIME_STOP_NONE;
  self->contexts = g_list_append(NULL,init);
  return self;
}

void
golem_runtime_enter(GolemRuntime * runtime,GolemRuntimeType type)
{
  g_return_if_fail(type != GOLEM_RUNTIME_FUNCTION);
  GolemRuntimeContext * context = g_new0(GolemRuntimeContext,1);
  context->context = golem_context_new(golem_runtime_get_context(runtime));
  context->type = type;
  runtime->contexts = g_list_append(runtime->contexts,context);

}

GolemContext *
golem_runtime_get_context(GolemRuntime * runtime)
{
  g_return_val_if_fail(runtime->contexts != NULL,NULL);
  return ((GolemRuntimeContext *)(g_list_last(runtime->contexts)->data))->context;
}

gboolean
golem_runtime_get_return(GolemRuntime * runtime,GValue * dest)
{
  if(runtime->return_val.g_type)
    {
      g_value_init(dest,runtime->return_val.g_type);
      g_value_copy(&(runtime->return_val),dest);
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

gboolean
golem_runtime_running(GolemRuntime * runtime)
{
  g_return_val_if_fail(runtime->contexts != NULL,FALSE);
  GolemRuntimeContext * context = ((GolemRuntimeContext *)(g_list_last(runtime->contexts)->data));
  switch(context->type)
  {
  case GOLEM_RUNTIME_FUNCTION:
  case GOLEM_RUNTIME_LOCAL:
      return runtime->stop == GOLEM_RUNTIME_STOP_NONE;
  case GOLEM_RUNTIME_LOOP:
      if(runtime->stop == GOLEM_RUNTIME_STOP_BREAK || runtime->stop == GOLEM_RUNTIME_STOP_RETURN)
	{
	  return FALSE;
	}
      else if(runtime->stop == GOLEM_RUNTIME_STOP_CONTINUE)
	{
	  runtime->stop = GOLEM_RUNTIME_STOP_NONE;
	  return TRUE;
	}
      else
	{
	  return TRUE;
	}
  }
}

gboolean
_golem_runtime_check(GolemRuntime * runtime, GolemRuntimeType type)
{
  g_return_val_if_fail(runtime->contexts != NULL,FALSE);
  for(GList * iter = g_list_last(runtime->contexts);iter;iter = g_list_previous(iter))
    {
      if(((GolemRuntimeContext *)iter->data)->type == type)
	return TRUE;
    }
  return FALSE;
}

gboolean
golem_runtime_break(GolemRuntime * runtime)
{
  g_return_val_if_fail(runtime->contexts != NULL,FALSE);
  if(_golem_runtime_check(runtime,GOLEM_RUNTIME_LOOP))
    {
      runtime->stop = GOLEM_RUNTIME_STOP_BREAK;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

gboolean
golem_runtime_continue(GolemRuntime * runtime)
{
  g_return_val_if_fail(runtime->contexts != NULL,FALSE);
  if(_golem_runtime_check(runtime,GOLEM_RUNTIME_LOOP))
    {
      runtime->stop = GOLEM_RUNTIME_STOP_CONTINUE;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

void
golem_runtime_return(GolemRuntime * runtime,const GValue * value)
{
  g_return_if_fail(runtime->contexts != NULL);
  runtime->stop = GOLEM_RUNTIME_STOP_RETURN;
  if(value)
    {
      g_value_init(&(runtime->return_val),G_VALUE_TYPE(value));
      g_value_copy(value,&(runtime->return_val));
    }
}

static void
_golem_runtime_context_free(gpointer context_item)
{
  GolemRuntimeContext * context = (GolemRuntimeContext *)context_item;
  g_object_unref(context->context);
  g_free(context);
}

void
golem_runtime_exit(GolemRuntime * runtime)
{
  g_return_if_fail(runtime->contexts != NULL);
  GList * iter = g_list_last(runtime->contexts);
  GolemRuntimeContext * context = (GolemRuntimeContext *)(iter->data);
  runtime->contexts = g_list_remove_link(runtime->contexts,iter);
  if(runtime->contexts)
    {
      if(context->type == GOLEM_RUNTIME_LOOP)
      {
	if(runtime->stop == GOLEM_RUNTIME_STOP_BREAK || runtime->stop == GOLEM_RUNTIME_STOP_CONTINUE)
	  runtime->stop = GOLEM_RUNTIME_STOP_NONE;
      }
    }
  _golem_runtime_context_free(context);
}

void
golem_runtime_destroy(GolemRuntime * runtime)
{
  g_list_free_full(runtime->contexts,_golem_runtime_context_free);
  g_value_unset(&(runtime->return_val));
  g_free(runtime);
}

