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
#include <string.h>
#include <math.h>

#define GOLEM_VM_REG_COUNT 32
#define GOLEM_VM_ARG_COUNT 32

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

#define GOLEM_VM_OPA(op,vtype) m_reg[n_reg - 2].vtype = m_reg[n_reg - 2].vtype op m_reg[n_reg - 1].vtype;\
			       n_reg -= 1;

#define GOLEM_VM_OPC(op,vtype) m_reg[n_reg - 2].int32_v = m_reg[n_reg - 2].vtype op m_reg[n_reg - 1].vtype;\
			       n_reg -= 1;


#define GOLEM_VM_OPN(vop,reg_use)  {\
  switch(op->data.type)\
  {\
  case GOLEM_TYPE_CODE_DOUBLE:\
    reg_use(vop,double_v)\
    break;\
  case GOLEM_TYPE_CODE_FLOAT:\
    reg_use(vop,float_v)\
    break;\
  case GOLEM_TYPE_CODE_UINT8:\
    reg_use(vop,uint8_v)\
    break;\
  case GOLEM_TYPE_CODE_INT8:\
    reg_use(vop,int8_v)\
    break;\
  case GOLEM_TYPE_CODE_UINT16:\
    reg_use(vop,uint16_v)\
    break;\
  case GOLEM_TYPE_CODE_INT16:\
    reg_use(vop,int16_v)\
    break;\
  case GOLEM_TYPE_CODE_UINT32:\
    reg_use(vop,uint32_v)\
    break;\
  case GOLEM_TYPE_CODE_INT32:\
    reg_use(vop,int32_v)\
    break;\
  case GOLEM_TYPE_CODE_UINT64:\
    reg_use(vop,uint64_v)\
    break;\
  case GOLEM_TYPE_CODE_INT64:\
    reg_use(vop,int64_v)\
    break;\
  case GOLEM_TYPE_CODE_POINTER:\
  case GOLEM_TYPE_CODE_STRING:\
    reg_use(vop,int64_v)\
    break;\
  default:\
    reg_use(vop,int32_v)\
    break;\
  }\
}

#define GOLEM_VM_OPI(vop,reg_use)  {\
  switch(op->data.type)\
  {\
  case GOLEM_TYPE_CODE_UINT8:\
    reg_use(vop,uint8_v)\
    break;\
  case GOLEM_TYPE_CODE_INT8:\
    reg_use(vop,int8_v)\
    break;\
  case GOLEM_TYPE_CODE_UINT16:\
    reg_use(vop,uint16_v)\
    break;\
  case GOLEM_TYPE_CODE_INT16:\
    reg_use(vop,int16_v)\
    break;\
  case GOLEM_TYPE_CODE_UINT32:\
    reg_use(vop,uint32_v)\
    break;\
  case GOLEM_TYPE_CODE_INT32:\
    reg_use(vop,int32_v)\
    break;\
  case GOLEM_TYPE_CODE_UINT64:\
    reg_use(vop,uint64_v)\
    break;\
  case GOLEM_TYPE_CODE_INT64:\
    reg_use(vop,int64_v)\
    break;\
  default:\
    reg_use(vop,int32_v)\
    break;\
  }\
}


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

guint32
golem_vm_body_write_data(GolemVMBody * body,
			 GolemVMData * reg,
			 GolemTypeCode reg_type,
			 guint16 reg_size)
{
  guint32 offset = body->n_data;
  body->m_data = g_realloc(body->m_data,sizeof(GolemVMData) * (body->n_data + 1));
  body->m_data_type = g_realloc(body->m_data_type,sizeof(GolemTypeCode) * (body->n_data + 1));
  body->m_data_size = g_realloc(body->m_data_size,sizeof(guint16) * (body->n_data + 1));
  body->n_data += 1;

  if(reg_type == GOLEM_TYPE_CODE_STRING)
    body->m_data[offset].pointer_v = g_strndup((gchar*)reg->pointer_v,reg_size);
  else if(reg_type == GOLEM_TYPE_CODE_POINTER)
    body->m_data[offset].pointer_v = g_memdup(reg->pointer_v,reg_size);
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
golem_vm_body_write_opt(GolemVMBody * body,
			GolemVMOpCode code,
			GolemTypeCode type)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOp) * (body->n_op + 1));
  body->m_op[offset].code = code;
  body->m_op[offset].data.type = type;
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


gboolean
golem_vm_body_run(GolemVMBody * body,
		  GolemVMScope * scope,
		  GolemVMData * ret,
		  GError ** error)
{
  GolemVMData m_reg[GOLEM_VM_REG_COUNT] = {0,};
  gint8       n_reg = 0;
  GolemVMData m_arg[GOLEM_VM_ARG_COUNT] = {0,};
  gint8       n_arg = 0;
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
	case GOLEM_OP_PSH: //PUSH VARIABLE
	  golem_vm_scope_set(scope,
			     op->data.scope_v.index,
			     op->data.scope_v.offset,
			     op->data.scope_v.size,
			     &(m_reg[n_reg-1]));
	  n_reg --;
	  break;
	case GOLEM_OP_POP: //POP VARIABLE
	  golem_vm_scope_get(scope,
			     op->data.scope_v.index,
			     op->data.scope_v.offset,
			     op->data.scope_v.size,
			     &(m_reg[n_reg]));
	  n_reg ++;
	  break;
	case GOLEM_OP_DUP: //DUPLICATE
	  m_reg[n_reg] = m_reg[n_reg - 1];
	  n_reg ++;
	  break;
	case GOLEM_OP_DAT: //DATA
	  m_reg[n_reg] = body->m_data[op->data.int16_v];
	  n_reg ++;
	  break;
	case GOLEM_OP_RET: //RETURN
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
			    &(m_reg[n_reg-1]).pointer_v);
	  break;
	case GOLEM_OP_SX: //SCOPE EXIT
	  golem_vm_scope_exit(scope,
			      op->data.int32_v);
	  break;
	case GOLEM_OP_JMP: //JUMP
	  n_op = op->data.int32_v;
	  break;
	case GOLEM_OP_CND: //CONDITION
	  if(m_reg[n_reg - 1].int32_v)
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
	  m_eh_value = (GError*)m_reg[n_reg - 1].pointer_v;
	  n_reg --;
	  break;
	case GOLEM_OP_RHE: //REMOVE HANDLE EXCEPTION
	  m_eh_queue = g_list_remove_link(g_list_first(m_eh_queue),g_list_last(m_eh_queue));
	  break;

	/* MEMORY */
	case GOLEM_OP_MAC: //ALLOC MEMORY
	  m_reg[n_reg].pointer_v = g_malloc(op->data.int32_v);
	  n_reg ++;
	  break;
	case GOLEM_OP_MAZ: //ALLOC MEMORY WITH ZERO
	  m_reg[n_reg].pointer_v = g_malloc0(op->data.int32_v);
	  n_reg ++;
	  break;
	case GOLEM_OP_FRE: //FREE MEMORY
	  g_free(m_reg[n_reg-1].pointer_v);
	  n_reg --;
	  break;
	case GOLEM_OP_PTO: //POINTER OF
	  golem_vm_scope_ptr(scope,
			     op->data.scope_v.index,
			     op->data.scope_v.offset,
			     &(m_reg[n_reg]));
	  n_reg ++;
	  break;
	case GOLEM_OP_PTW: //WRITE POINTER
	  break;
	case GOLEM_OP_PTR: //READ POINTER
	  break;

	/* OBJECT */
	case GOLEM_OP_SOD: //OBJECT DEFINITION
	//case GOLEM_OP_POD: //CONSTRUCT PARAM
	case GOLEM_OP_NEW: //NEW OBJECT
	case GOLEM_OP_DCT: //NEW DICTIONATY
	case GOLEM_OP_FF: //FUNCTION FIND
	case GOLEM_OP_PW: //PROPERTY WRITE
	case GOLEM_OP_PR: //PROPERTY READ
	case GOLEM_OP_IR: //INCREASE REFERENCE
	case GOLEM_OP_DR: //DECREASE REFERENCE
	  break;

        /* FUNCTION */
	case GOLEM_OP_ARG: //ARGUMENT
	  m_arg[n_arg] = m_reg[n_reg -1];
	  n_reg --;
	  n_arg ++;
	  break;
	case GOLEM_OP_CAL: //CALL FUNCTION
	  {
	    guint8 argc = op->data.int16_v;
	    GolemVMData * argv = g_memdup(&(m_arg[n_arg - argc]),sizeof(GolemVMData) * argc);
	    GolemVMInvocable * inv = (GolemVMInvocable *)m_reg[n_reg - 1].pointer_v;
	    GolemVMData ret = {0,};
	    if(inv->invoke(inv,argc,argv,&ret,&m_eh_value))
	      m_reg[n_reg - 1] = ret;
	    else
	      m_done = FALSE;
	    n_arg -= argc;
	    g_free(argv);
	  }
	  break;

	/* ARITMETICAL OP */
	case GOLEM_OP_ADD: //ADD
	 GOLEM_VM_OPN(+,GOLEM_VM_OPA)
	 break;
	case GOLEM_OP_MUL: //MULTIPLICATE
	  GOLEM_VM_OPN(*,GOLEM_VM_OPA)
	  break;
	case GOLEM_OP_DIV: //DIVIDE
	  GOLEM_VM_OPN(/,GOLEM_VM_OPA)
	  break;
	case GOLEM_OP_SUB: //SUBSTRACT
	  GOLEM_VM_OPN(-,GOLEM_VM_OPA)
	  break;
	case GOLEM_OP_MOD: //MODULE
	  GOLEM_VM_OPI(%,GOLEM_VM_OPA)
	  break;
	case GOLEM_OP_EXP: //EXPONENT
	  break;
	case GOLEM_OP_IDV: //INTEGER DIVIDE
	  break;

	/* COMPARATION OP */
	case GOLEM_OP_LT:
	  GOLEM_VM_OPN(<,GOLEM_VM_OPC);
	  break;
	case GOLEM_OP_GT:
	  GOLEM_VM_OPN(>,GOLEM_VM_OPC)
	  break;
	case GOLEM_OP_IQT:
	  GOLEM_VM_OPN(==,GOLEM_VM_OPC)
	  break;
	case GOLEM_OP_DST:
	  GOLEM_VM_OPN(!=,GOLEM_VM_OPC)
	  break;

	/* LOGICAL OP */
	case GOLEM_OP_AND:
	  GOLEM_VM_OPI(&,GOLEM_VM_OPA)
	  break;
	case GOLEM_OP_OR:
	  GOLEM_VM_OPI(|,GOLEM_VM_OPA)
	  break;
	default:
	  n_op = body->n_op;
      }

      if(!m_done)
	{
	  if(m_eh_queue)
	    {
	      GolemVM_EH * eh = ((GolemVM_EH *)g_list_last(m_eh_queue)->data);
	      n_op = eh->n_jump;
	      golem_vm_scope_exit(scope,eh->n_scope);
	      m_reg[n_reg].pointer_v = m_eh_value;
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
  return m_done;
}

GolemVMBody *
golem_vm_body_copy(GolemVMBody * body)
{
  GolemVMBody * new_body = g_new(GolemVMBody,1);
  new_body->m_data = g_memdup(body->m_data,
			      sizeof(GolemVMData) * body->n_data);
  new_body->m_data_type = g_memdup(body->m_data_type,
				   sizeof(GolemTypeCode) * body->n_data);
  new_body->n_data = body->n_data;
  new_body->m_op = g_memdup(body->m_op,
			    sizeof(GolemVMOp) * body->n_op);
  new_body->n_op = body->n_op;

  GolemVMData * reg;
  GolemTypeCode reg_type;
  guint16 reg_size;

  for(guint16 index = body->n_data;index < body->n_data; index ++)
    {
      reg = &(body->m_data[index]);
      reg_type = body->m_data_type[index];
      reg_size = body->m_data_size[index];

      if(reg_type == GOLEM_TYPE_CODE_STRING)
         new_body->m_data[index].pointer_v = g_strndup((gchar*)reg->pointer_v,
						       reg_size);
      else if(reg_type == GOLEM_TYPE_CODE_POINTER)
	 new_body->m_data[index].pointer_v = g_memdup(reg->pointer_v,
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
  scope->m_data[scope->n_data]->m_gcobj = NULL;
  scope->m_data[scope->n_data]->m_gcmem = NULL;
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
  dest->pointer_v = (scope->m_data[index]->m_data + offset);
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
            g_list_free_full(scope->m_data[index]->m_gcobj,g_object_unref);
            g_free(scope->m_data[index]);
          }
      scope->m_data = g_realloc(
		  scope->m_data,
		  sizeof(GolemVMScopeData*) * index);
      scope->n_data --;
    }
}

inline void
golem_vm_scope_gc(GolemVMScope * scope,gpointer data)
{

  scope->m_data[scope->n_data - 1]->m_gcobj =
      g_list_append(scope->m_data[scope->n_data - 1]->m_gcobj,data);
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
