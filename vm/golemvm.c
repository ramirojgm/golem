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

#define GOLEM_VM_REG_COUNT 4
#define GOLEM_VM_ARG_COUNT 32

G_DEFINE_POINTER_TYPE(GolemSymbol,golem_symbol)

/*static void __attribute__((constructor))
g_type_int16_init()
{
  static GTypeInfo gint16_info;
  static GTypeFundamentalInfo gint16_fund;
  gint16_info.instance_size = sizeof(gint16);
  gint16_fund.type_flags = G_TYPE_FLA;

  g_type_register_fundamental(G_TYPE_INT16,"gint16",&gint16_info,&gint16_fund,G_TYPE_FLAG_VALUE_ABSTRACT);
  g_type_register_fundamental(G_TYPE_UINT16,"guint16",&gint16_info,&gint16_fund,G_TYPE_FLAG_VALUE_ABSTRACT);
}*/

typedef struct
{
  guint16 n_jump;
  guint16 n_scope;
} GolemVM_EH;

typedef struct
{
  GParameter * m_parameter;
  guint32      n_parameter;
} GolemVM_NO;

GolemVMBody *
golem_vm_body_new(void)
{
  return g_new0(GolemVMBody,1);
}

guint32
golem_vm_body_get_offset(GolemVMBody * body)
{
  return body->n_op;
}

gsize
golem_vm_body_get_length(GolemVMBody * body)
{
  return body->n_op;
}

guint16
golem_vm_body_write_data(GolemVMBody * body,
			 GolemVMData * reg,
			 GType	reg_type,
			 guint16 reg_size)
{
  for(guint16 data_index = 0; data_index < body->n_data; data_index ++)
    {
      GolemVMData * m_data = &(body->m_data[data_index]);
      GType m_data_type = body->m_data_type[data_index];
      guint16 m_data_size = body->m_data_size[data_index];
      if(m_data_type == reg_type && m_data_size == reg_size)
	{
	  if(m_data_type == G_TYPE_STRING
	      && strncmp(m_data->data->pointer_v,reg->data->pointer_v,reg_size) == 0)
	    {
	      return data_index;
	    }
	  else if(m_data->data->int64_v == reg->data->int64_v)
	    {
	      return data_index;
	    }
	}
    }

  guint16 offset = body->n_data;
  body->m_data = g_realloc(body->m_data,sizeof(GolemVMData) * (body->n_data + 1));
  body->m_data_type = g_realloc(body->m_data_type,sizeof(GType) * (body->n_data + 1));
  body->m_data_size = g_realloc(body->m_data_size,sizeof(guint16) * (body->n_data + 1));
  body->n_data += 1;

  if(reg_type == G_TYPE_STRING)
    body->m_data[offset].data->pointer_v = g_strndup(reg->data->pointer_v,reg_size);
  else if(reg_type == G_TYPE_POINTER)
    body->m_data[offset].data->pointer_v = g_memdup(reg->data->pointer_v,reg_size);
  else
    body->m_data[offset] = *reg;

  body->m_data_type[offset] = reg_type;
  body->m_data_size[offset] = reg_size;
  return offset;
}

void
golem_vm_body_write_op(GolemVMBody * body,
		       GolemVMOpCode code)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOp) * (body->n_op + 1));
  body->m_op[offset].code = code;
  body->m_op[offset].data.int32_v = 0;
  body->n_op += 1;
}

void
golem_vm_body_write_op16(GolemVMBody * body,
		       GolemVMOpCode code,
		       guint16 arg0)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOp) * (body->n_op + 1));
  body->m_op[offset].code = code;
  body->m_op[offset].data.int16_v = arg0;
  body->n_op += 1;
}

void
golem_vm_body_write_op32(GolemVMBody * body,
		       GolemVMOpCode code,
		       guint32 arg0)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOp) * (body->n_op + 1));
  body->m_op[offset].code = code;
  body->m_op[offset].data.int32_v = arg0;
  body->n_op += 1;
}

void
golem_vm_body_write_ops(GolemVMBody * body,
			GolemVMOpCode code,
			guint16 vindex,
			guint16 voffset,
			guint8 vsize)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOp) * (body->n_op + 1));
  body->m_op[offset].code = code;
  body->m_op[offset].data.scope_v.index = vindex;
  body->m_op[offset].data.scope_v.offset = voffset;
  body->m_op[offset].data.scope_v.size = vsize;
  body->n_op += 1;
}

void
golem_vm_body_update_op16(GolemVMBody * body,
			 guint32 opindex,
			 guint16 arg0)
{
  body->m_op[opindex].data.int16_v = arg0;
}

void
golem_vm_body_update_op32(GolemVMBody * body,
			 guint32 opindex,
			 guint32 arg0)
{
  body->m_op[opindex].data.int32_v = arg0;
}

GolemRefPtr*
golem_refptr_new(gpointer ptr,
		 GType type,
		 GFreeFunc free_func)
{
  GolemRefPtr * refptr = g_new0(GolemRefPtr,1);
  refptr->refcount = 1;
  refptr->type = type;
  refptr->data = ptr;
  refptr->free_func = free_func;
  return refptr;
}

GolemRefPtr*
golem_refptr_ref(GolemRefPtr * refptr)
{
  refptr->refcount ++;
  return refptr;
}

void
golem_refptr_unref(GolemRefPtr * refptr)
{
  refptr->refcount --;
  if(refptr->refcount <= 0)
    {
      if(refptr->free_func)
	refptr->free_func(refptr);
      g_free(refptr);
    }
}


gboolean
golem_vm_body_run(GolemVMBody * body,
		  GolemVMScope * scope,
		  guint16	argc,
		  GolemVMData *	argv,
		  GolemVMData * ret,
		  GError ** error)
{
  GolemVMData m_reg[GOLEM_VM_REG_COUNT];
  gint8       n_reg = 0;
  GolemVMData m_arg[GOLEM_VM_ARG_COUNT];
  gint8       n_arg = 0;
  gint8       c_arg = 0;
  GolemVMOp*  m_op = body->m_op;
  guint32     n_op = 0;

  GList *     m_eh_queue = NULL;
  GError *    m_eh_value = NULL;

  gboolean    m_done = TRUE;


  if(!scope)
    scope = golem_vm_scope_new();
  else
    scope = golem_vm_scope_copy(scope);

  for(;;)
    {
      GolemVMOp * op = &(m_op[n_op]);
      switch(op->code)
      {
	  /* OP */
	case GOLEM_OP_PH: //PUSH VARIABLE
	  golem_vm_scope_set(scope,
			     op->data.scope_v.index,
			     op->data.scope_v.offset,
			     op->data.scope_v.size,
			     &(m_reg[n_reg-1]));
	  n_reg --;
	  break;
	case GOLEM_OP_PP: //POP VARIABLE
	  golem_vm_scope_get(scope,
			     op->data.scope_v.index,
			     op->data.scope_v.offset,
			     op->data.scope_v.size,
			     &(m_reg[n_reg]));
	  n_reg ++;
	  break;
	case GOLEM_OP_DP: //DUPLICATE
	  m_reg[n_reg] = m_reg[n_reg - 1];
	  n_reg ++;
	  break;
	case GOLEM_OP_DC: //DISCARD
	  n_reg --;
	  break;
	case GOLEM_OP_DT: //DATA
	  m_reg[n_reg] = body->m_data[op->data.int16_v];
	  n_reg ++;
	  break;
	case GOLEM_OP_RT: //RETURN
	  *ret = m_reg[n_reg - 1];
	  n_reg --;
	  n_op = body->n_op;
	  break;
	case GOLEM_OP_SE: //SCOPE ENTER
	  golem_vm_scope_enter(scope,
			       op->data.int32_v);
	  break;
	case GOLEM_OP_GC: //GARBAGE COLLECTOR
	  golem_vm_scope_gc(scope,
			    (GolemRefPtr*)&(m_reg[n_reg-1]).data->pointer_v);
	  break;
	case GOLEM_OP_SX: //SCOPE EXIT
	  golem_vm_scope_exit(scope,
			      op->data.int32_v);
	  break;

	  /* ARITMETICAL OP */
	case GOLEM_OP_AI32: //ADD INTEGER 32BIT
	  m_reg[n_reg - 2].data->int32_v = m_reg[n_reg - 2].data->int32_v + m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_AI64: //ADD INTEGER 64BIT
	  m_reg[n_reg - 2].data->int64_v = m_reg[n_reg - 2].data->int64_v + m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_AF32: //ADD FLOAT 32BIT
	  m_reg[n_reg - 2].data->float_v = m_reg[n_reg - 2].data->float_v + m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_AD64: //ADD DOUBLE 64BIT
	  m_reg[n_reg - 2].data->double_v = m_reg[n_reg - 2].data->double_v + m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;

	case GOLEM_OP_SI32: //SUBSTRACT INTEGER 32BIT
	  m_reg[n_reg - 2].data->int32_v = m_reg[n_reg - 2].data->int32_v - m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_SI64: //SUBSTRACT INTEGER 64BIT
	  m_reg[n_reg - 2].data->int64_v = m_reg[n_reg - 2].data->int64_v - m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_SF32: //SUBSTRACT FLOAT 32BIT
	  m_reg[n_reg - 2].data->float_v = m_reg[n_reg - 2].data->float_v - m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_SD64: //SUBSTRACT DOUBLE 64BIT
	  m_reg[n_reg - 2].data->double_v = m_reg[n_reg - 2].data->double_v - m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;

	case GOLEM_OP_MI32: //MULTIPLICATE INTEGER 32BIT
	  m_reg[n_reg - 2].data->int32_v = m_reg[n_reg - 2].data->int32_v * m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_MI64: //MULTIPLICATE INTEGER 64BIT
	  m_reg[n_reg - 2].data->int64_v = m_reg[n_reg - 2].data->int64_v * m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_MF32: //MULTIPLICATE FLOAT 32BIT
	  m_reg[n_reg - 2].data->float_v = m_reg[n_reg - 2].data->float_v * m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_MD64: //MULTIPLICATE DOUBLE 64BIT
	  m_reg[n_reg - 2].data->double_v = m_reg[n_reg - 2].data->double_v * m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;

	case GOLEM_OP_DI32: //DIVIDE INTEGER 32BIT
	  m_reg[n_reg - 2].data->int32_v = m_reg[n_reg - 2].data->int32_v / m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_DI64: //DIVIDE INTEGER 64BIT
	  m_reg[n_reg - 2].data->int64_v = m_reg[n_reg - 2].data->int64_v / m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_DF32: //DIVIDE FLOAT 32BIT
	  m_reg[n_reg - 2].data->float_v = m_reg[n_reg - 2].data->float_v / m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_DD64: //DIVIDE DOUBLE 64BIT
	  m_reg[n_reg - 2].data->double_v = m_reg[n_reg - 2].data->double_v / m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;

	case GOLEM_OP_NI32: //NEGATIVE INTEGER 32BIT
	  m_reg[n_reg - 1].data->int32_v = abs(m_reg[n_reg - 1].data->int32_v) * -1;
	  n_reg --;
	  break;
	case GOLEM_OP_NI64: //NEGATIVE INTEGER 64BIT
	  m_reg[n_reg - 1].data->int64_v = labs(m_reg[n_reg - 1].data->int64_v) * -1;
	  n_reg --;
	  break;
	case GOLEM_OP_NF32: //NEGATIVE FLOAT 32BIT
	  m_reg[n_reg - 1].data->float_v = fabsf(m_reg[n_reg - 1].data->float_v) * -1;
	  n_reg --;
	  break;
	case GOLEM_OP_ND64: //NEGATIVE DOUBLE 64BIT
	  m_reg[n_reg - 1].data->double_v = fabs(m_reg[n_reg - 1].data->double_v) * -1;
	  n_reg --;
	  break;

	case GOLEM_OP_RI32: //MODULE INTEGER 32BIT
	  m_reg[n_reg - 2].data->int32_v = m_reg[n_reg - 2].data->int32_v % m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_RI64: //MODULE INTEGER 64BIT
	  m_reg[n_reg - 2].data->int64_v = m_reg[n_reg - 2].data->int64_v % m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_RF32: //MODULE FLOAT 32BIT
	  m_reg[n_reg - 2].data->float_v = fmodf(m_reg[n_reg - 2].data->float_v, m_reg[n_reg - 1].data->float_v);
	  n_reg --;
	  break;
	case GOLEM_OP_RD64: //MODULE DOUBLE 64BIT
	  m_reg[n_reg - 2].data->double_v = fmod(m_reg[n_reg - 2].data->double_v, m_reg[n_reg - 1].data->double_v);
	  n_reg --;
	  break;

	case GOLEM_OP_PD64: //POW DOUBLE 64BIT
	  m_reg[n_reg - 2].data->double_v = pow(m_reg[n_reg - 2].data->double_v, m_reg[n_reg - 1].data->double_v);
	  n_reg --;
	  break;

	  /* COMPARATION OP */
	case GOLEM_OP_LI32:  //LESS INTEGER 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int32_v < m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LI64:  //LESS INTEGER 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int64_v < m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LF32:  //LESS FLOAT 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->float_v < m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LD64:  //LESS DOUBLE 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->double_v < m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LP:  //LESS POINTER
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->pointer_v < m_reg[n_reg - 1].data->pointer_v;
	  n_reg --;
	  break;

	case GOLEM_OP_LII32:  //LESS IQUAL INTEGER 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int32_v <= m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LII64:  //LESS IQUAL INTEGER 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int64_v <= m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LIF32:  //LESS IQUAL FLOAT 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->float_v <= m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LID64:  //LESS IQUAL DOUBLE 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->double_v <= m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;
	case GOLEM_OP_LIP:  //LESS IQUAL POINTER
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->pointer_v <= m_reg[n_reg - 1].data->pointer_v;
	  n_reg --;
	  break;

	case GOLEM_OP_GI32:  //GREATER INTEGER 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int32_v > m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GI64:  //GREATER INTEGER 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int64_v > m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GF32:  //GREATER FLOAT 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->float_v > m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GD64:  //GREATER DOUBLE 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->double_v > m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GP:  //GREATER POINTER
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->pointer_v > m_reg[n_reg - 1].data->pointer_v;
	  n_reg --;
	  break;

	case GOLEM_OP_GII32:  //GREATER IQUAL INTEGER 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int32_v >= m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GII64:  //GREATER IQUAL INTEGER 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int64_v >= m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GIF32:  //GREATER IQUAL FLOAT 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->float_v >= m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GID64:  //GREATER IQUAL DOUBLE 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->double_v >= m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;
	case GOLEM_OP_GIP:  //GREATER IQUAL POINTER
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->pointer_v >= m_reg[n_reg - 1].data->pointer_v;
	  n_reg --;
	  break;

	case GOLEM_OP_II32: //IQUAL INTEGER 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int32_v == m_reg[n_reg - 1].data->int32_v;
	  n_reg --;
	  break;
	case GOLEM_OP_II64: //IQUAL INTEGER 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->int64_v == m_reg[n_reg - 1].data->int64_v;
	  n_reg --;
	  break;
	case GOLEM_OP_IF32: //IQUAL FLOAT 32BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->float_v == m_reg[n_reg - 1].data->float_v;
	  n_reg --;
	  break;
	case GOLEM_OP_ID64: //IQUAL DOUBLE 64BIT
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->double_v == m_reg[n_reg - 1].data->double_v;
	  n_reg --;
	  break;
	case GOLEM_OP_IP: //IQUAL POINTER
	  m_reg[n_reg - 2].data->int8_v = m_reg[n_reg - 2].data->pointer_v == m_reg[n_reg - 1].data->pointer_v;
	  n_reg --;
	  break;

	  /* JUMP */
	case GOLEM_OP_JP: //JUMP
	  n_op = op->data.int32_v;
	  break;
	case GOLEM_OP_IF: //IF
	  if(m_reg[n_reg - 1].data->int8_v)
	    n_op = op->data.int32_v - 1;
	  n_reg --;
	  break;

	/* TRY CATCH */
	case GOLEM_OP_AHE: //ADD HANDLE EXCEPTION
	  {
	    GolemVM_EH * eh = g_new(GolemVM_EH,1);
	    eh->n_jump = op->data.int32_v;
	    eh->n_scope = scope->n_data - 1;
	    m_eh_queue = g_list_append(m_eh_queue,eh);
	  }
	  break;
	case GOLEM_OP_THW: //THROW EXCEPTION
	  m_done = FALSE;
	  m_eh_value = (GError*)m_reg[n_reg - 1].data->pointer_v;
	  n_reg --;
	  break;
	case GOLEM_OP_RHE: //REMOVE HANDLE EXCEPTION
	  m_eh_queue = g_list_remove_link(g_list_first(m_eh_queue),g_list_last(m_eh_queue));
	  break;

	/* MEMORY */
	case GOLEM_OP_MA: //ALLOC MEMORY
	  m_reg[n_reg].data->pointer_v = g_malloc(op->data.int32_v);
	  n_reg ++;
	  break;
	case GOLEM_OP_MF: //FREE MEMORY
	  g_free(m_reg[n_reg-1].data->pointer_v);
	  n_reg --;
	  break;
	case GOLEM_OP_PO: //POINTER OF
	  golem_vm_scope_ptr(scope,
			     op->data.scope_v.index,
			     op->data.scope_v.offset,
			     &(m_reg[n_reg]));
	  n_reg ++;
	  break;
	case GOLEM_OP_PW: //WRITE POINTER
	  break;
	case GOLEM_OP_PR: //READ POINTER
	  break;

	 /* FUNCTION */
	case GOLEM_OP_RA: //READ ARGUMENT
	  if(c_arg < argc)
	    m_reg[n_reg] = argv[c_arg];
	  else
	    m_reg[n_reg].data->int64_v = 0;
	  c_arg ++;
	  n_reg ++;
	  break;
	case GOLEM_OP_WA: //WRITE ARGUMENT
	  m_arg[n_arg] = m_reg[n_reg -1];
	  n_reg --;
	  n_arg ++;
	  break;
	case GOLEM_OP_CL: //CALL FUNCTION
	  {
	    guint8 argc = op->data.int16_v;
	    GolemVMData * argv = g_memdup(&(m_arg[n_arg - argc]),sizeof(GolemVMData) * argc);
	    GolemCallable * callable = (GolemCallable *)m_reg[n_reg - 1].data->pointer_v;
	    GolemVMData ret = {};
	    if(callable->call(callable,argc,argv,&ret,&m_eh_value))
	      m_reg[n_reg - 1] = ret;
	    else
	      m_done = FALSE;
	    n_arg -= argc;
	    g_free(argv);
	  }
	  break;
	/* LOGICAL OP */
	case GOLEM_OP_AND:
	  //GOLEM_VM_OPI(&,GOLEM_VM_OPA)
	  break;
	case GOLEM_OP_OR:
	  //GOLEM_VM_OPI(|,GOLEM_VM_OPA)
	  break;
	case GOLEM_OP_NOT:
	  m_reg[n_reg - 1].data->int32_v = !m_reg[n_reg - 1].data->int32_v;
	  break;

	  /* DATA OP */
	case GOLEM_OP_TRUE: //TRUE
	  m_reg[n_reg].data->int32_v = TRUE;
	  n_reg ++;
	  break;
	case GOLEM_OP_NULL: //NULL
	  m_reg[n_reg].data->pointer_v = NULL;
	  n_reg ++;
	  break;
	default:
	  n_op = body->n_op;
      }
      //g_print("OP:%d,%d\n",op->code, n_reg);

      if(!m_done)
	{
	  if(m_eh_queue)
	    {
	      GolemVM_EH * eh = ((GolemVM_EH *)g_list_last(m_eh_queue)->data);
	      n_op = eh->n_jump;
	      golem_vm_scope_exit(scope,eh->n_scope);
	      m_reg[n_reg].data->pointer_v = m_eh_value;
	      n_reg ++;
	      m_eh_queue = g_list_remove(m_eh_queue,eh);
	      g_free(eh);
	      m_done = TRUE;
	    }
	  else
	    {
	      break;
	    }
	}

      if(n_op >= body->n_op)
	break;
      n_op ++;
    }
  golem_vm_scope_free(scope);
  /*if(m_eh_value)
      g_propagate_error(error,m_eh_value);*/
  return m_done;
}

GolemVMBody *
golem_vm_body_copy(GolemVMBody * body)
{
  GolemVMBody * new_body = g_new(GolemVMBody,1);
  new_body->m_data = g_memdup(body->m_data,
			      sizeof(GolemVMData) * body->n_data);
  new_body->m_data_type = g_memdup(body->m_data_type,
				   sizeof(GType) * body->n_data);
  new_body->n_data = body->n_data;
  new_body->m_op = g_memdup(body->m_op,
			    sizeof(GolemVMOp) * body->n_op);
  new_body->n_op = body->n_op;

  GolemVMData * reg;
  GType 	reg_type;
  guint16 	reg_size;

  for(guint16 index = body->n_data;index < body->n_data; index ++)
    {
      reg = &(body->m_data[index]);
      reg_type = body->m_data_type[index];
      reg_size = body->m_data_size[index];

      if(reg_type == G_TYPE_STRING)
	new_body->m_data[index].data->pointer_v = g_strndup((gchar*)
							    reg->data->pointer_v,
							    reg_size);
      else if(reg_type == G_TYPE_POINTER)
	 new_body->m_data[index].data->pointer_v = g_memdup(reg->data->pointer_v,
						      reg_size);

    }
  return new_body;
}

void
golem_vm_body_free(GolemVMBody * body)
{

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
		     guint16 size)
{
  scope->m_data = g_realloc(
			scope->m_data,
			sizeof(GolemVMScopeData*) * scope->n_data + 1);
  scope->m_data[scope->n_data] = g_new0(GolemVMScopeData,1);
  scope->m_data[scope->n_data]->n_ref = 1;
  scope->m_data[scope->n_data]->m_data = (GolemVMData*)g_malloc(size);
  scope->m_data[scope->n_data]->m_gc = NULL;
  scope->m_data[scope->n_data]->n_size = size;
  scope->n_data ++;
}

inline void
golem_vm_scope_get(GolemVMScope * scope,
		   guint16 index,
		   guint16 offset,
		   guint8 size,
		   GolemVMData * dest)
{
  memcpy(dest,scope->m_data[index]->m_data + offset,size);
}

inline void
golem_vm_scope_set(GolemVMScope * scope,
		   guint16 index,
		   guint16 offset,
		   guint8 size,
		   const GolemVMData * src)
{
  memcpy(scope->m_data[index]->m_data + offset,src,size);
}

inline void
golem_vm_scope_ptr(GolemVMScope * scope,
		   guint16 index,
		   guint16 offset,
		   GolemVMData * dest)
{
  dest->data->pointer_v = (scope->m_data[index]->m_data + offset);
}


inline void
golem_vm_scope_exit(GolemVMScope * scope,
		    guint16 eindex)
{
  guint16 bindex = scope->n_data - 1;
  for(guint16 index = bindex;index <= eindex;index --)
    {
      scope->m_data[index]->n_ref--;
        if(scope->m_data[index]->n_ref <= 0)
          {
            g_free(scope->m_data[index]->m_data);
            g_list_free_full(scope->m_data[index]->m_gc,(GDestroyNotify)golem_refptr_unref);
            g_free(scope->m_data[index]);
          }
      scope->m_data = g_realloc(
		  scope->m_data,
		  sizeof(GolemVMScopeData*) * index);
      scope->n_data --;
    }
}

inline void
golem_vm_scope_gc(GolemVMScope * scope,GolemRefPtr * data)
{
  scope->m_data[scope->n_data - 1]->m_gc =
      g_list_append(scope->m_data[scope->n_data - 1]->m_gc,golem_refptr_ref(data));
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
