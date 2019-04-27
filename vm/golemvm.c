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

#include "golemvm.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef void (*GolemVMOpFunc) (GolemVMOp * op,
                               GolemVMStack * stack);


typedef struct
{
  gpointer data;
  GDestroyNotify free_fn;
} GolemVMDataFree;

#define golem_vm_stack_v0(stack)   (&(stack->m_stack[stack->n_stack]))
#define golem_vm_stack_v1(stack)   (&(stack->m_stack[stack->n_stack - 1]))
#define golem_vm_stack_v2(stack)   (&(stack->m_stack[stack->n_stack - 2]))
#define golem_vm_stack_v0c(stack,c) GOLEM_##c(&(stack->m_stack[stack->n_stack]))
#define golem_vm_stack_v1c(stack,c) GOLEM_##c(&(stack->m_stack[stack->n_stack - 1]))
#define golem_vm_stack_v2c(stack,c) GOLEM_##c(&(stack->m_stack[stack->n_stack - 2]))
#define golem_vm_stack_pop(stack,c)   stack->n_stack -= c
#define golem_vm_stack_push(stack,c)  stack->n_stack += c
#define golem_vm_stack_vpush(stack,v) stack->m_stack[stack->n_stack] = *(v);\
                                      stack->n_stack ++

#define golem_vm_stack_next(stack)   stack->n_op ++
#define golem_vm_stack_goto(stack,n) stack->n_op = n

/*
  VM Operation Functions
*/

static inline void
_golem_vm_op_put (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_scope_put(stack->scope,
                    op->data.vscope.index,
                    glength_get(op->data.vscope.offset),
                    glength_get(op->data.vscope.size),
                    golem_vm_stack_v1(stack));

  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_get (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_scope_get(stack->scope,
                    op->data.vscope.index,
                    glength_get(op->data.vscope.offset),
                    glength_get(op->data.vscope.size),
                    golem_vm_stack_v0(stack));

  golem_vm_stack_push(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_dup (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_stack_vpush(stack,golem_vm_stack_v1(stack));
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_drp (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_dat (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_stack_vpush(stack,&(stack->body->m_data[op->data.v16].data));
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ret (GolemVMOp * op,
                  GolemVMStack * stack)
{
  stack->ret = *(golem_vm_stack_v1(stack));
  golem_vm_stack_goto(stack,stack->body->n_op);
}

static inline void
_golem_vm_op_ent (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_scope_enter(stack->scope,glength_get(op->data.vlength));
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_qff (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_scope_queue_free(
      stack->scope,
      GOLEM_POINTER(golem_vm_stack_v2(stack)),
      (GDestroyNotify)GOLEM_POINTER(golem_vm_stack_v1(stack))
  );
  golem_vm_stack_pop(stack,2);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ext (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_scope_exit(stack->scope,op->data.v16);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ai32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) + golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ai64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT64) =
  golem_vm_stack_v2c(stack,INT64) + golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ai128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT128) =
  golem_vm_stack_v2c(stack,INT128) + golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_af32 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT32) =
  golem_vm_stack_v2c(stack,FLOAT32) + golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_af64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT64) =
  golem_vm_stack_v2c(stack,FLOAT64) + golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_af128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT128) =
  golem_vm_stack_v2c(stack,FLOAT128) + golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_si32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) - golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_si64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT64) =
  golem_vm_stack_v2c(stack,INT64) - golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_si128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT128) =
  golem_vm_stack_v2c(stack,INT128) - golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_sf32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT32) =
  golem_vm_stack_v2c(stack,FLOAT32) - golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_sf64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT64) =
  golem_vm_stack_v2c(stack,FLOAT64) - golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_sf128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT128) =
  golem_vm_stack_v2c(stack,FLOAT128) - golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}


static inline void
_golem_vm_op_mi32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) * golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_mi64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT64) =
  golem_vm_stack_v2c(stack,INT64) * golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_mi128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT128) =
  golem_vm_stack_v2c(stack,INT128) * golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_mf32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT32) =
  golem_vm_stack_v2c(stack,FLOAT32) * golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_mf64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT64) =
  golem_vm_stack_v2c(stack,FLOAT64) * golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_mf128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT128) =
  golem_vm_stack_v2c(stack,FLOAT128) * golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}


static inline void
_golem_vm_op_di32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) / golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_di64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT64) =
  golem_vm_stack_v2c(stack,INT64) / golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_di128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT128) =
  golem_vm_stack_v2c(stack,INT128) / golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_df32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT32) =
  golem_vm_stack_v2c(stack,FLOAT32) / golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_df64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT64) =
  golem_vm_stack_v2c(stack,FLOAT64) / golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_df128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,FLOAT128) =
  golem_vm_stack_v2c(stack,FLOAT128) / golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ni32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,INT32) = golem_vm_stack_v1c(stack,INT32) * -1;
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ni64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,INT64) = golem_vm_stack_v1c(stack,INT64) * -1l;
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ni128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,INT128) = golem_vm_stack_v1c(stack,INT128) * -1;
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_nf32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,FLOAT32) = golem_vm_stack_v1c(stack,INT32) * -1.0f;
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_nf64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,FLOAT64) = golem_vm_stack_v1c(stack,FLOAT64) * -1.0;
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_nf128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,FLOAT128) = golem_vm_stack_v1c(stack,FLOAT128) * -1.0;
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_li32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT32) < golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_li64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT64) < golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_li128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT128) < golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lf32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT32) < golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lf64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT64) < golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lf128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT128) < golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lp    (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,POINTER) < golem_vm_stack_v1c(stack,POINTER);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lii32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT32) <= golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lii64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT64) <= golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lii128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT128) <= golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lif32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT32) <= golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lif64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT64) <= golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lif128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT128) <= golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_lip    (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,POINTER) <= golem_vm_stack_v1c(stack,POINTER);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gi32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT32) > golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gi64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT64) > golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gi128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT128) > golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gf32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT32) > golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gf64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT64) > golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gf128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT128) > golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gp    (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,POINTER) > golem_vm_stack_v1c(stack,POINTER);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gii32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT32) >= golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gii64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT64) >= golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gii128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT128) >= golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gif32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT32) >= golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gif64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT64) >= golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gif128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT128) >= golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_gip    (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,POINTER) >= golem_vm_stack_v1c(stack,POINTER);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ii32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT32) == golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ii64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT64) == golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ii128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,INT128) == golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_if32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT32) == golem_vm_stack_v1c(stack,FLOAT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_if64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT64) == golem_vm_stack_v1c(stack,FLOAT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_if128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,FLOAT128) == golem_vm_stack_v1c(stack,FLOAT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ip    (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,BOOL) =
  golem_vm_stack_v2c(stack,POINTER) == golem_vm_stack_v1c(stack,POINTER);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_goto  (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_goto(stack,op->data.v32);
}

static inline void
_golem_vm_op_if  (GolemVMOp * op,
                    GolemVMStack * stack)
{
  gbool_t v = golem_vm_stack_v1c(stack,BOOL);
  golem_vm_stack_pop(stack,1);
  if (v)
    golem_vm_stack_goto(stack,op->data.v32);
  else
    golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_addr  (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_scope_get_address(stack->scope,
                             op->data.vscope.index,
                             glength_get(op->data.vscope.offset),
                             golem_vm_stack_v0(stack));
  golem_vm_stack_push(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_pmov  (GolemVMOp * op,
                    GolemVMStack * stack)
{
  uintptr_t dest = (uintptr_t)golem_vm_stack_v1c(stack,POINTER);
  golem_vm_stack_v1c(stack,POINTER)
  =  (gpointer_t)(dest + ((uintptr_t)glength_get(op->data.vlength)));
  golem_vm_stack_next(stack);
}


static inline void
_golem_vm_op_pset  (GolemVMOp * op,
                    GolemVMStack * stack)
{
  gpointer_t dest = golem_vm_stack_v2c(stack,POINTER);
  gpointer_t src = (gpointer_t)golem_vm_stack_v1(stack);
  memcpy(dest,src,glength_get(op->data.vlength));
  golem_vm_stack_pop(stack,2);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_pget  (GolemVMOp * op,
                    GolemVMStack * stack)
{
  gpointer_t src = golem_vm_stack_v1c(stack,POINTER);
  gpointer_t dest = (gpointer_t)golem_vm_stack_v1(stack);
  memcpy(dest,src,glength_get(op->data.vlength));
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_ld  (GolemVMOp * op,
                  GolemVMStack * stack)
{
  GOLEM_POINTER(golem_vm_stack_v0(stack))
  = stack->body->m_symbols[op->data.v16];
  golem_vm_stack_push(stack,1);
  golem_vm_stack_next(stack);
}


static inline void
_golem_vm_op_frt  (GolemVMOp * op,
                  GolemVMStack * stack)
{
  //TODO: Implement
}

static inline void
_golem_vm_op_apt  (GolemVMOp * op,
                  GolemVMStack * stack)
{
  //TODO: Implement
}

static inline void
_golem_vm_op_agt  (GolemVMOp * op,
                  GolemVMStack * stack)
{
  golem_vm_stack_vpush(stack,&(stack->v_arg[stack->n_arg]));
  stack->n_arg ++;
}

static inline void
_golem_vm_op_cal  (GolemVMOp * op,
                  GolemVMStack * stack)
{
  //TODO: Implement
}

static inline void
_golem_vm_op_an32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) & golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_an64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT64) =
  golem_vm_stack_v2c(stack,INT64) & golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_an128 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT128) =
  golem_vm_stack_v2c(stack,INT128) & golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_or32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) | golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_or64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT64) =
  golem_vm_stack_v2c(stack,INT64) | golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_or128 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT128) =
  golem_vm_stack_v2c(stack,INT128) | golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_nt32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,INT32) = !golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_nt64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,INT64) = !golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_nt128 (GolemVMOp * op,
                    GolemVMStack * stack)
{
  golem_vm_stack_v1c(stack,INT128) = !golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_xor32 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) ^ golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_xor64 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT64) =
  golem_vm_stack_v2c(stack,INT64) ^ golem_vm_stack_v1c(stack,INT64);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_xor128 (GolemVMOp * op,
                   GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT128) =
  golem_vm_stack_v2c(stack,INT128) ^ golem_vm_stack_v1c(stack,INT128);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_bl (GolemVMOp * op,
                 GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) << golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_br (GolemVMOp * op,
                 GolemVMStack * stack)
{
  golem_vm_stack_v2c(stack,INT32) =
  golem_vm_stack_v2c(stack,INT32) >> golem_vm_stack_v1c(stack,INT32);
  golem_vm_stack_pop(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_true (GolemVMOp * op,
                   GolemVMStack * stack)
{
  GOLEM_BOOL(golem_vm_stack_v0(stack)) = TRUE;
  golem_vm_stack_push(stack,1);
  golem_vm_stack_next(stack);
}

static inline void
_golem_vm_op_zero (GolemVMOp * op,
                   GolemVMStack * stack)
{
  GOLEM_INT32(golem_vm_stack_v0(stack)) = 0;
  golem_vm_stack_push(stack,1);
  golem_vm_stack_next(stack);
}

static volatile const
GolemVMOpFunc _golem_vm_op_[GOLEM_OP_N] = {
  _golem_vm_op_put, 	//SCOPE PUT
  _golem_vm_op_get, 	//SCOPE GET
  _golem_vm_op_dup, 	//DUPLICATE ONE REGISTER
  _golem_vm_op_drp, 	//DROP ONE REGISTER
  _golem_vm_op_dat, 	//DATA
  _golem_vm_op_ret, 	//RETURN
  _golem_vm_op_ent, 	//SCOPE ENTER
  _golem_vm_op_qff, 	//QUEUE FOR FREE
  _golem_vm_op_ext, 	//SCOPE EXIT

  /* ARITMETICAL OP */
  _golem_vm_op_ai32,	//ADD INTEGER 32BIT
  _golem_vm_op_ai64, 	//ADD INTEGER 64BIT
  _golem_vm_op_ai128,	//ADD INTEGER 128BIT
  _golem_vm_op_af32, 	//ADD FLOAT 32BIT
  _golem_vm_op_af64, 	//ADD FLOAT 64BIT
  _golem_vm_op_af128, 	//ADD FLOAT 128BIT
  _golem_vm_op_si32, 	//SUBSTRACT INTEGER 32BIT
  _golem_vm_op_si64, 	//SUBSTRACT INTEGER 64BIT
  _golem_vm_op_si128, 	//SUBSTRACT INTEGER 128BIT
  _golem_vm_op_sf32, 	//SUBSTRACT FLOAT 32BIT
  _golem_vm_op_sf64, 	//SUBSTRACT FLOAT 64BIT
  _golem_vm_op_sf128, 	//SUBSTRACT FLOAT 128BIT
  _golem_vm_op_mi32, 	//MULTIPLICATE INTEGER 32BIT
  _golem_vm_op_mi64, 	//MULTIPLICATE INTEGER 64BIT
  _golem_vm_op_mi128, 	//MULTIPLICATE INTEGER 128BIT
  _golem_vm_op_mf32, 	//MULTIPLICATE FLOAT 32BIT
  _golem_vm_op_mf64, 	//MULTIPLICATE FLOAT 64BIT
  _golem_vm_op_mf128, 	//MULTIPLICATE FLOAT 128BIT
  _golem_vm_op_di32, 	//DIVIDE INTEGER 32BIT
  _golem_vm_op_di64, 	//DIVIDE INTEGER 64BIT
  _golem_vm_op_di128, 	//DIVIDE INTEGER 128BIT
  _golem_vm_op_df32, 	//DIVIDE FLOAT 32BIT
  _golem_vm_op_df64, 	//DIVIDE FLOAT 64BIT
  _golem_vm_op_df128, 	//DIVIDE FLOAT 128BIT
  _golem_vm_op_ni32, 	//NEGATIVE INTEGER 32BIT
  _golem_vm_op_ni64, 	//NEGATIVE INTEGER 64BIT
  _golem_vm_op_ni128, 	//NEGATIVE INTEGER 128BIT
  _golem_vm_op_nf32, 	//NEGATIVE FLOAT 32BIT
  _golem_vm_op_nf64, 	//NEGATIVE FLOAT 64BIT
  _golem_vm_op_nf128, 	//NEGATIVE FLOAT 128BIT
  _golem_vm_op_li32,  	//LESS INTEGER 32BIT
  _golem_vm_op_li64,  	//LESS INTEGER 64BIT
  _golem_vm_op_li128,  	//LESS INTEGER 128BIT
  _golem_vm_op_lf32,  	//LESS FLOAT 32BIT
  _golem_vm_op_lf64,  	//LESS FLOAT 64BIT
  _golem_vm_op_lf128,  	//LESS FLOAT 128BIT
  _golem_vm_op_lp,    	//LESS POINTER
  _golem_vm_op_lii32,  	//LESS IQUAL INTEGER 32BIT
  _golem_vm_op_lii64,  	//LESS IQUAL INTEGER 64BIT
  _golem_vm_op_lii128, 	//LESS IQUAL INTEGER 128BIT
  _golem_vm_op_lif32,  	//LESS IQUAL FLOAT 32BIT
  _golem_vm_op_lif64,  	//LESS IQUAL FLOAT 64BIT
  _golem_vm_op_lif128, 	//LESS IQUAL FLOAT 128BIT
  _golem_vm_op_lip,    	//LESS IQUAL POINTER
  _golem_vm_op_gi32,  	//GREATER INTEGER 32BIT
  _golem_vm_op_gi64,  	//GREATER INTEGER 64BIT
  _golem_vm_op_gi128,  	//GREATER INTEGER 128BIT
  _golem_vm_op_gf32,  	//GREATER FLOAT 32BIT
  _golem_vm_op_gf64,  	//GREATER FLOAT 64BIT
  _golem_vm_op_gf128,  	//GREATER FLOAT 128BIT
  _golem_vm_op_gp,    	//GREATER POINTER
  _golem_vm_op_gii32,  	//GREATER IQUAL INTEGER 32BIT
  _golem_vm_op_gii64,  	//GREATER IQUAL INTEGER 64BIT
  _golem_vm_op_gii128, 	//GREATER IQUAL INTEGER 128BIT
  _golem_vm_op_gif32,  	//GREATER IQUAL FLOAT 32BIT
  _golem_vm_op_gif64,  	//GREATER IQUAL FLOAT 64BIT
  _golem_vm_op_gif128, 	//GREATER IQUAL FLOAT 128BIT
  _golem_vm_op_gip,    	//GREATER IQUAL POINTER
  _golem_vm_op_ii32,  	//IQUAL INTEGER 32BIT
  _golem_vm_op_ii64,  	//IQUAL INTEGER 64BIT
  _golem_vm_op_ii128,  	//IQUAL INTEGER 128BIT
  _golem_vm_op_if32,  	//IQUAL FLOAT 32BIT
  _golem_vm_op_if64,  	//IQUAL FLOAT 64BIT
  _golem_vm_op_if128,  	//IQUAL FLOAT 128BIT
  _golem_vm_op_ip,    	//IQUAL POINTER

  /* SEQUENCE CONTROL */
  _golem_vm_op_goto,   	//GOTO
  _golem_vm_op_if,   	//IF

  /* MEMORY */
  _golem_vm_op_addr, 	//ADDRESS OF
  _golem_vm_op_pmov,  //POINTER MOVE
  _golem_vm_op_pset, 	//POINTER SET
  _golem_vm_op_pget, 	//POINTER GET

  /* FUNCTION */
  _golem_vm_op_ld, 		//FUNCTION LOAD
  _golem_vm_op_frt, 	//FUNCTION RETURN
  _golem_vm_op_apt, 	//FUNCTION PUT ARGUMENT
  _golem_vm_op_agt, 	//FUNCTION GET ARGUMENT
  _golem_vm_op_cal, 	//CALL FUNCTION

  /* BINARY OP */
  _golem_vm_op_an32,	//AND AT 32BIT
  _golem_vm_op_an64,	//AND AT 64BIT
  _golem_vm_op_an128,	//AND AT 128BIT
  _golem_vm_op_or32, 	//OR AT 32BIT
  _golem_vm_op_or64, 	//OR AT 64BIT
  _golem_vm_op_or128, 	//OR AT 128BIT
  _golem_vm_op_nt32,	//NOT AT 32BIT
  _golem_vm_op_nt64,	//NOT AT 64BIT
  _golem_vm_op_nt128,	//NOT AT 128BIT
  _golem_vm_op_xor32,	//XOR AT 32BIT
  _golem_vm_op_xor64,	//XOR AT 32BIT
  _golem_vm_op_xor128,	//XOR AT 128BIT
  _golem_vm_op_bl, 		//BITS TO LEFT
  _golem_vm_op_br, 		//BITS TO RIGHT

  /* CONSTANTS OP */
  _golem_vm_op_true,	//TRUE
  _golem_vm_op_zero	//ZERO
};


/*
  VMBody
*/

GolemVMBody *
golem_vm_body_new(void)
{
  return g_new0(GolemVMBody,1);
}

guint32_t
golem_vm_body_get_offset(GolemVMBody * body)
{
  return body->n_op;
}

guint32_t
golem_vm_body_get_length(GolemVMBody * body)
{
  return body->n_op;
}

guint16_t
golem_vm_body_write_value (GolemVMBody * body,
			               GolemValue * data)
{
  for(guint16 data_index = 0; data_index < body->n_data; data_index ++)
    {
      GolemVMData * m_data = &(body->m_data[data_index]);
      if(GOLEM_INT128(&(m_data->data)) == GOLEM_INT128(data))
	    return data_index;
    }

  guint16 offset = body->n_data;
  body->m_data = g_realloc(body->m_data,sizeof(GolemVMData) * (body->n_data + 1));
  body->n_data += 1;

  body->m_data[offset].data = *data;
  body->m_data[offset].length = 0;
  body->m_data[offset].byte_array = FALSE;

  return offset;
}


guint16_t
golem_vm_body_write_string (GolemVMBody * body,
                            gstring_t str,
			                      gint16_t length)
{
  if (str && length < 0)
    length = g_utf8_strlen(str,G_MAXINT16);

  for(guint16 data_index = 0; data_index < body->n_data; data_index ++)
  {
      GolemVMData * m_data = &(body->m_data[data_index]);
      if(m_data->length == length && strncmp(GOLEM_STRING(&(m_data->data)),str,length) == 0)
        return data_index;
  }

  guint16 offset = body->n_data;
  body->m_data = g_realloc(body->m_data,sizeof(GolemVMData) * (body->n_data + 1));
  body->n_data += 1;

  GOLEM_STRING(&(body->m_data[offset].data)) = g_strndup(str,length);
  body->m_data[offset].length = length + 1;
  body->m_data[offset].byte_array = TRUE;

  return offset;
}


guint16_t
golem_vm_body_write_data   (GolemVMBody * body,
                            gpointer_t data,
			                      guint16_t length)
{
  for(guint16 data_index = 0; data_index < body->n_data; data_index ++)
  {
      GolemVMData * m_data = &(body->m_data[data_index]);
      if(m_data->length == length && memcmp(GOLEM_POINTER(&(m_data->data)),data,length) == 0)
        return data_index;
  }

  guint16 offset = body->n_data;
  body->m_data = g_realloc(body->m_data,sizeof(GolemVMData) * (body->n_data + 1));
  body->n_data += 1;

  GOLEM_POINTER(&(body->m_data[offset].data)) = g_memdup(data,length);
  body->m_data[offset].length = length;
  body->m_data[offset].byte_array = TRUE;

  return offset;
}


void
golem_vm_body_write_op(GolemVMBody * body,
		                   GolemVMOpCode code)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOpLD) * (body->n_op + 1));
  body->m_op[offset].op.code = code;
  body->m_op[offset].op.data.v32 = 0;
  body->m_op[offset].op_func = _golem_vm_op_[code];
  body->n_op += 1;
}

void
golem_vm_body_write_op16(GolemVMBody * body,
              		       GolemVMOpCode code,
		                     guint16_t arg0)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOpLD) * (body->n_op + 1));
  body->m_op[offset].op.code = code;
  body->m_op[offset].op.data.v32 = arg0;
  body->m_op[offset].op_func = _golem_vm_op_[code];
  body->n_op += 1;
}

void
golem_vm_body_write_op32(GolemVMBody * body,
		                     GolemVMOpCode code,
		                     guint32_t arg0)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOpLD) * (body->n_op + 1));
  body->m_op[offset].op.code = code;
  body->m_op[offset].op.data.v32 = arg0;
  body->m_op[offset].op_func = _golem_vm_op_[code];
  body->n_op += 1;
}

void
golem_vm_body_write_opl (GolemVMBody * body,
		                     GolemVMOpCode code,
		                     glength16_t arg0)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOpLD) * (body->n_op + 1));
  body->m_op[offset].op.code = code;
  body->m_op[offset].op.data.vlength = arg0;
  body->m_op[offset].op_func = _golem_vm_op_[code];
  body->n_op += 1;
}


void
golem_vm_body_write_ops(GolemVMBody * body,
			                  GolemVMOpCode code,
			                  guint16_t vindex,
			                  glength16_t voffset,
			                  glength8_t vsize)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOpLD) * (body->n_op + 1));
  body->m_op[offset].op.code = code;
  body->m_op[offset].op.data.vscope.index = vindex;
  body->m_op[offset].op.data.vscope.offset = voffset;
  body->m_op[offset].op.data.vscope.size = vsize;
  body->m_op[offset].op_func = _golem_vm_op_[code];
  body->n_op += 1;
}

void
golem_vm_body_update_op16(GolemVMBody * body,
			                     guint32_t opindex,
			                     guint16_t arg0)
{
  body->m_op[opindex].op.data.v16 = arg0;
}

void
golem_vm_body_update_op32(GolemVMBody * body,
			                     guint32_t opindex,
			                     guint32_t arg0)
{
  body->m_op[opindex].op.data.v32 = arg0;
}

void
golem_vm_body_update_opl(GolemVMBody * body,
			  guint32_t opindex,
			  glength16_t arg0)
{
  body->m_op[opindex].op.data.vlength = arg0;
}

gboolean
golem_vm_body_run(GolemVMBody * body,
		              GolemVMScope * scope,
		              guint16	argc,
		              GolemValue *	argv,
		              GolemValue * ret,
		              GError ** error)
{
  GolemVMStack stack = {0,};

  if(!scope)
    stack.scope = golem_vm_scope_new();
  else
    stack.scope = golem_vm_scope_copy(scope);

  stack.n_stack = 0;
  stack.body = body;
  stack.n_op = 0;
  stack.v_arg = argv;
  stack.c_arg = argc;
  stack.n_arg = 0;
  stack.error = NULL;

  GolemVMOpLD * op_ld = NULL;

  for (;;)
  {
    op_ld = &(body->m_op[stack.n_op]);
    ((GolemVMOpFunc)op_ld->op_func)(&(op_ld->op),&stack);

    if (stack.n_op >= body->n_op)
      break;
  }

  golem_vm_scope_free(stack.scope);

  if (stack.error)
  {
    g_propagate_error(error,stack.error);
    return FALSE;
  }
  else
  {
    *ret = stack.ret;
    return TRUE;
  }
}

GolemVMBody *
golem_vm_body_copy(GolemVMBody * body)
{
  GolemVMBody * copy_body = g_new(GolemVMBody,1);

  copy_body->m_data = g_new0(GolemVMData,body->n_data);
  copy_body->n_data = body->n_data;
  for (guint16_t i = 0; i < body->n_data; i++)
    {
      copy_body->m_data[i] = body->m_data[i];
      if (body->m_data[i].byte_array)
      {
        GOLEM_POINTER(&(copy_body->m_data[i].data)) = g_memdup(
          GOLEM_POINTER(&(body->m_data[i].data)),
          body->m_data[i].length);
      }
    }

  copy_body->m_symbols = g_memdup(
    body->m_symbols,
    sizeof(gpointer_t) * body->n_symbols);
  copy_body->n_symbols = body->n_symbols;

  copy_body->m_op = g_memdup(
    body->m_op,
    sizeof(GolemVMOpLD) * body->n_op);
  copy_body->n_op = body->n_op;

  return copy_body;
}

void
golem_vm_body_free(GolemVMBody * body)
{
  for (guint16_t i = 0; i < body->n_data; i++)
    {
      if (body->m_data[i].byte_array)
          g_free(GOLEM_POINTER(&(body->m_data[i].data)));
    }
  g_free(body->m_data);
  g_free(body->m_symbols);
  g_free(body->m_op);
  g_free(body);
}

inline GolemVMScope *
golem_vm_scope_new(void)
{
  GolemVMScope * instance = g_new(GolemVMScope,1);
  instance->m_data = NULL;
  instance->n_data = 0;
  return instance;
}

inline void
golem_vm_scope_enter(GolemVMScope * scope,
		                 guint16_t size)
{
  scope->m_data = g_realloc(
      scope->m_data,
			sizeof(GolemVMScopeData*) * scope->n_data + 1);

  scope->m_data[scope->n_data] = g_new0(GolemVMScopeData,1);
  scope->m_data[scope->n_data]->n_ref = 1;
  scope->m_data[scope->n_data]->m_data = (GolemValue*)g_malloc(size);
  scope->m_data[scope->n_data]->m_queue_free = NULL;
  scope->m_data[scope->n_data]->n_size = size;
  scope->n_data ++;
}

inline void
golem_vm_scope_get(GolemVMScope * scope,
		               guint16_t index,
		               guint16_t offset,
		               guint8_t size,
		               GolemValue * dest)
{
  memcpy(dest,scope->m_data[index]->m_data + offset,size);
}

inline void
golem_vm_scope_put(GolemVMScope * scope,
		               guint16_t index,
		               guint16_t offset,
		               guint8_t size,
		               GolemValue * src)
{
  memcpy(scope->m_data[index]->m_data + offset,src,size);
}

inline void
golem_vm_scope_get_address(GolemVMScope * scope,
		                       guint16 index,
		                       guint16 offset,
		                       GolemValue * dest)
{
  GOLEM_POINTER(dest) = (scope->m_data[index]->m_data + offset);
}

static void
golem_vm_scope_data_free(GolemVMDataFree * data_free)
{
  data_free->free_fn(data_free->data);
  g_free(data_free);
}

inline void
golem_vm_scope_exit(GolemVMScope * scope,
		                guint16_t eindex)
{
  guint16 bindex = scope->n_data - 1;
  for(guint16 index = bindex;index <= eindex;index --)
    {
      scope->m_data[index]->n_ref--;
      if(scope->m_data[index]->n_ref <= 0)
      {
        g_free(scope->m_data[index]->m_data);
        g_list_free_full(scope->m_data[index]->m_queue_free,(GDestroyNotify)golem_vm_scope_data_free);
        g_free(scope->m_data[index]);
      }
      scope->m_data = g_realloc(
		  scope->m_data,
		  sizeof(GolemVMScopeData*) * index);
      scope->n_data --;
    }
}

inline void
golem_vm_scope_queue_free (GolemVMScope * scope,gpointer value,GDestroyNotify free_fn)
{
  GolemVMDataFree * data_free = g_new(GolemVMDataFree,1);
  data_free->data = value;
  data_free->free_fn = free_fn;
  scope->m_data[scope->n_data - 1]->m_queue_free =
      g_list_append(scope->m_data[scope->n_data - 1]->m_queue_free,data_free);
}

inline GolemVMScope *
golem_vm_scope_copy(GolemVMScope * scope)
{
  GolemVMScope * instance = g_new(GolemVMScope,1);
  instance->m_data = g_malloc(sizeof(GolemVMScopeData*) * scope->n_data);
  instance->n_data = scope->n_data;
  for(guint16 index = 0;index < scope->n_data; index ++)
    {
      instance->m_data[index] = scope->m_data[index];
      instance->m_data[index]->n_ref += 1;
    }
  return instance;
}

inline void
golem_vm_scope_free(GolemVMScope * scope)
{
  for(guint16 index = 0;index < scope->n_data; index ++)
    {
      scope->m_data[index]->n_ref -= 1;
      if(scope->m_data[index]->n_ref <= 0)
	    {
	      g_free(scope->m_data[index]->m_data);
	      g_free(scope->m_data[index]);
	    }
    }
  g_free(scope->m_data);
  g_free(scope);
}
