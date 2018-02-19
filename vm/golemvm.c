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

#define GOLEM_VM_REG_COUNT 32

typedef struct
{
  GObjectConstructParam * m_param;
  guint16 		  n_param;
}GolemVMConstruct;

#define GOLEM_VM_OP_NUMERIC_ART(op,vtype) m_reg[n_reg - 2].vtype = m_reg[n_reg - 2].vtype op m_reg[n_reg - 1].vtype;\
					  n_reg -= 1;

#define GOLEM_VM_OP_NUMERIC_CMP(op,vtype) m_reg[n_reg - 2].int32_v = m_reg[n_reg - 2].vtype op m_reg[n_reg - 1].vtype;\
					  n_reg -= 1;


#define GOLEM_VM_OP_NUMERIC(vop,reg_use)  {\
  switch(op->data.type)\
  {\
  case GOLEM_DATA_TYPE_DOUBLE:\
    reg_use(vop,double_v)\
    break;\
  case GOLEM_DATA_TYPE_FLOAT:\
    reg_use(vop,float_v)\
    break;\
  case GOLEM_DATA_TYPE_UINT8:\
    reg_use(vop,uint8_v)\
    break;\
  case GOLEM_DATA_TYPE_INT8:\
    reg_use(vop,int8_v)\
    break;\
  case GOLEM_DATA_TYPE_UINT16:\
    reg_use(vop,uint16_v)\
    break;\
  case GOLEM_DATA_TYPE_INT16:\
    reg_use(vop,int16_v)\
    break;\
  case GOLEM_DATA_TYPE_UINT32:\
    reg_use(vop,uint32_v)\
    break;\
  case GOLEM_DATA_TYPE_INT32:\
    reg_use(vop,int32_v)\
    break;\
  case GOLEM_DATA_TYPE_UINT64:\
    reg_use(vop,uint64_v)\
    break;\
  case GOLEM_DATA_TYPE_INT64:\
    reg_use(vop,int64_v)\
    break;\
  case GOLEM_DATA_TYPE_POINTER:\
  case GOLEM_DATA_TYPE_STRING:\
    reg_use(vop,int64_v)\
    break;\
  default:\
    reg_use(vop,int32_v)\
    break;\
  }\
}

#define GOLEM_VM_OP_INT(vop,reg_use)  {\
  switch(op->data.type)\
  {\
  case GOLEM_DATA_TYPE_UINT8:\
    reg_use(vop,uint8_v)\
    break;\
  case GOLEM_DATA_TYPE_INT8:\
    reg_use(vop,int8_v)\
    break;\
  case GOLEM_DATA_TYPE_UINT16:\
    reg_use(vop,uint16_v)\
    break;\
  case GOLEM_DATA_TYPE_INT16:\
    reg_use(vop,int16_v)\
    break;\
  case GOLEM_DATA_TYPE_UINT32:\
    reg_use(vop,uint32_v)\
    break;\
  case GOLEM_DATA_TYPE_INT32:\
    reg_use(vop,int32_v)\
    break;\
  case GOLEM_DATA_TYPE_UINT64:\
    reg_use(vop,uint64_v)\
    break;\
  case GOLEM_DATA_TYPE_INT64:\
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
			 GolemVMDataType reg_type,
			 guint16 reg_size)
{
  guint32 offset = body->n_data;
  body->m_data = g_realloc(body->m_data,sizeof(GolemVMData) * (body->n_data + 1));
  body->m_data_type = g_realloc(body->m_data_type,sizeof(GolemVMDataType) * (body->n_data + 1));
  body->m_data_size = g_realloc(body->m_data_size,sizeof(guint16) * (body->n_data + 1));
  body->n_data += 1;

  if(reg_type == GOLEM_DATA_TYPE_STRING)
    body->m_data[offset].pointer_v = g_strndup((gchar*)reg->pointer_v,reg_size);
  else if(reg_type == GOLEM_DATA_TYPE_POINTER)
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
  body->m_op[offset].data.arg0 = 0;
  body->n_op += 1;
}

void
golem_vm_body_write_opn(GolemVMBody * body,
		       GolemVMOpCode code,
		       guint32 arg0)
{
  guint32 offset = body->n_op;
  body->m_op = g_realloc(body->m_op,sizeof(GolemVMOp) * (body->n_op + 1));
  body->m_op[offset].code = code;
  body->m_op[offset].data.arg0 = arg0;
  body->n_op += 1;
}

void
golem_vm_body_write_opt(GolemVMBody * body,
			GolemVMOpCode code,
			GolemVMDataType type)
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
  body->m_op[offset].data.scope.index = vindex;
  body->m_op[offset].data.scope.offset = voffset;
  body->m_op[offset].data.scope.size = vsize;
  body->n_op += 1;
}


gboolean
golem_vm_body_run(GolemVMBody * body,
		  GolemVMScope * scope,
		  GolemVMData * ret,
		  GError ** error)
{
  GolemVMData m_reg[GOLEM_VM_REG_COUNT] = {0,};
  gint8       n_reg = 0;
  GolemVMOp*  m_op = body->m_op;
  guint32     n_op = 0;
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
			     op->data.scope.index,
			     op->data.scope.offset,
			     op->data.scope.size,
			     &(m_reg[n_reg-1]));
	  n_reg --;
	  break;
	case GOLEM_OP_POP: //POP VARIABLE
	  golem_vm_scope_get(scope,
			     op->data.scope.index,
			     op->data.scope.offset,
			     op->data.scope.size,
			     &(m_reg[n_reg]));
	  n_reg ++;
	  break;
	case GOLEM_OP_DUP: //DUPLICATE
	  m_reg[n_reg] = m_reg[n_reg - 1];
	  n_reg ++;
	  break;
	case GOLEM_OP_DAT: //DATA
	  m_reg[n_reg] = body->m_data[op->data.arg0];
	  n_reg ++;
	  break;
	case GOLEM_OP_RET: //RETURN
	  *ret = m_reg[n_reg - 1];
	  n_reg --;
	  n_op = body->n_op;
	  break;
	case GOLEM_OP_SE: //SCOPE ENTER
	  golem_vm_scope_enter(scope,
			       op->data.arg0);
	  break;
	case GOLEM_OP_GC: //GARBAGE COLLECTOR
	  golem_vm_scope_gc(scope,
			    &(m_reg[n_reg-1]).pointer_v);
	  break;
	case GOLEM_OP_SX: //SCOPE EXIT
	  golem_vm_scope_exit(scope,
			      op->data.arg0);
	  break;
	case GOLEM_OP_JMP: //JUMP
	  n_op = op->data.arg0;
	  break;
	case GOLEM_OP_CND: //CONDITION
	  if(m_reg[n_reg - 1].int32_v)
	    n_op = op->data.arg0 - 1;
	  n_reg --;
	  break;

	/* TRY CATCH */
	case GOLEM_OP_AHE: //ADD HANDLE EXCEPTION
	  //TODO: implement
	  break;
	case GOLEM_OP_THW: //THROW EXCEPTION
	  //TODO: implement
	  break;
	case GOLEM_OP_RHE: //REMOVE HANDLE EXCEPTION
	  //TODO: implement
	  break;

	/* MEMORY */
	case GOLEM_OP_ALM: //ALLOC MEMORY
	  m_reg[n_reg].pointer_v = g_malloc(op->data.arg0);
	  n_reg ++;
	  break;
	case GOLEM_OP_ALZ: //ALLOC MEMORY WITH ZERO
	  m_reg[n_reg].pointer_v = g_malloc0(op->data.arg0);
	  n_reg ++;
	  break;
	case GOLEM_OP_FRE: //FREE MEMORY
	  g_free(m_reg[n_reg-1].pointer_v);
	  n_reg --;
	  break;
	case GOLEM_OP_PTO: //POINTER OF
	  golem_vm_scope_ptr(scope,
			     op->data.scope.index,
			     op->data.scope.offset,
			     &(m_reg[n_reg]));
	  n_reg ++;
	  break;
	case GOLEM_OP_PTW: //WRITE POINTER
	  break;
	case GOLEM_OP_PTR: //READ POINTER
	  break;

	/* OBJECT */
	case GOLEM_OP_NEW: //NEW
	case GOLEM_OP_CP: //CONSTRUCT PARAM
	case GOLEM_OP_FF: //FUNCTION FIND
	case GOLEM_OP_PW: //PROPERTY WRITE
	case GOLEM_OP_PR: //PROPERTY READ
	case GOLEM_OP_IR: //INCREASE REFERENCE
	case GOLEM_OP_DR: //DECREASE REFERENCE

        /* FUNCTION */
	case GOLEM_OP_ARG: //ARGUMENT
	case GOLEM_OP_CAL: //CALL FUNCTION

	case GOLEM_OP_ADD:
	 GOLEM_VM_OP_NUMERIC(+,GOLEM_VM_OP_NUMERIC_ART)
	 break;
	case GOLEM_OP_MUL:
	  GOLEM_VM_OP_NUMERIC(*,GOLEM_VM_OP_NUMERIC_ART)
	  break;
	case GOLEM_OP_DIV:
	  GOLEM_VM_OP_NUMERIC(/,GOLEM_VM_OP_NUMERIC_ART)
	  break;
	case GOLEM_OP_SUB:
	  GOLEM_VM_OP_NUMERIC(-,GOLEM_VM_OP_NUMERIC_ART)
	  break;
	case GOLEM_OP_LT:
	  GOLEM_VM_OP_NUMERIC(<,GOLEM_VM_OP_NUMERIC_CMP);
	  break;
	case GOLEM_OP_GT:
	  GOLEM_VM_OP_NUMERIC(>,GOLEM_VM_OP_NUMERIC_CMP)
	  break;
	case GOLEM_OP_IQT:
	  GOLEM_VM_OP_NUMERIC(==,GOLEM_VM_OP_NUMERIC_CMP)
	  break;
	case GOLEM_OP_DST:
	  GOLEM_VM_OP_NUMERIC(!=,GOLEM_VM_OP_NUMERIC_CMP)
	  break;
	case GOLEM_OP_MOD:
	  GOLEM_VM_OP_INT(%,GOLEM_VM_OP_NUMERIC_ART)
	  break;
	case GOLEM_OP_AND:
	  GOLEM_VM_OP_INT(&,GOLEM_VM_OP_NUMERIC_ART)
	  break;
	case GOLEM_OP_OR:
	  GOLEM_VM_OP_INT(|,GOLEM_VM_OP_NUMERIC_ART)
	  break;








	default:
	  n_op = body->n_op;
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
				   sizeof(GolemVMDataType) * body->n_data);
  new_body->n_data = body->n_data;
  new_body->m_op = g_memdup(body->m_op,
			    sizeof(GolemVMOp) * body->n_op);
  new_body->n_op = body->n_op;

  GolemVMData * reg;
  GolemVMDataType reg_type;
  guint16 reg_size;

  for(guint16 index = body->n_data;index < body->n_data; index ++)
    {
      reg = &(body->m_data[index]);
      reg_type = body->m_data_type[index];
      reg_size = body->m_data_size[index];

      if(reg_type == GOLEM_DATA_TYPE_STRING)
         new_body->m_data[index].pointer_v = g_strndup((gchar*)reg->pointer_v,
						       reg_size);
      else if(reg_type == GOLEM_DATA_TYPE_POINTER)
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
  scope->m_data[scope->n_data]->m_garbage = NULL;
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
            g_list_free_full(scope->m_data[index]->m_garbage,g_object_unref);
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

  scope->m_data[scope->n_data - 1]->m_garbage =
      g_list_append(scope->m_data[scope->n_data - 1]->m_garbage,data);
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
