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

#ifndef GOLEM_VM_H_
#define GOLEM_VM_H_

#include <glib.h>
#include <glib-object.h>

typedef enum
{
  /* OP */
  GOLEM_OP_PSH = 1, //PUSH VARIABLE
  GOLEM_OP_POP, //POP VARIABLE
  GOLEM_OP_DUP, //DUPLICATE
  GOLEM_OP_DAT, //DATA
  GOLEM_OP_RET, //RETURN
  GOLEM_OP_SE, //SCOPE ENTER
  GOLEM_OP_GC, //GARBAGE COLLECTOR
  GOLEM_OP_SX, //SCOPE EXIT
  GOLEM_OP_JMP, //JUMP
  GOLEM_OP_CND, //CONDITION
  /* HANDLE EXCEPTION */
  GOLEM_OP_AHE, //ADD HANDLE EXCEPTION
  GOLEM_OP_THW, //THROW EXCEPTION
  GOLEM_OP_EHE, //EXTERNAL HANDLE EXCEPTION
  GOLEM_OP_RHE, //REMOVE HANDLE EXCEPTION
  /* MEMORY */
  GOLEM_OP_MAC, //ALLOC MEMORY
  GOLEM_OP_MAZ, //ALLOC MEMORY WITH ZERO
  GOLEM_OP_FRE, //FREE MEMORY
  GOLEM_OP_PTO, //POINTER OF
  GOLEM_OP_PTW, //WRITE POINTER
  GOLEM_OP_PTR, //READ POINTER
  /* OBJECT */
  GOLEM_OP_NEW, //NEW
  GOLEM_OP_CP, //CONSTRUCT PARAM
  GOLEM_OP_FF, //FUNCTION FIND
  GOLEM_OP_PW, //PROPERTY WRITE
  GOLEM_OP_PR, //PROPERTY READ
  GOLEM_OP_IR, //INCREASE REFERENCE
  GOLEM_OP_DR, //DECREASE REFERENCE
  /* FUNCTION */
  GOLEM_OP_ARG, //ARGUMENT
  GOLEM_OP_CAL, //CALL FUNCTION
  /* ARITMETICAL OP */
  GOLEM_OP_ADD, //ADD
  GOLEM_OP_SUB, //SUBSTRACT
  GOLEM_OP_MUL, //MULTIPLICATE
  GOLEM_OP_DIV, //DIVIDE
  GOLEM_OP_MOD, //MODULE
  GOLEM_OP_EXP, //EXPONENT
  GOLEM_OP_IDV, //INTEGER DIVIDE
  /* COMPARATION OP */
  GOLEM_OP_LT,  //LESS THAN
  GOLEM_OP_GT,	//GREATER THAN
  GOLEM_OP_IQT, //IQUAL THAN
  GOLEM_OP_DST, //DISTINCT THAN
  /* LOGICAL OP */
  GOLEM_OP_AND,	//AND
  GOLEM_OP_OR,  //OR
  GOLEM_OP_NOT, //NOT
  GOLEM_OP_XOR, //XOR
  /* BIT OP */
  GOLEM_OP_BTL, //BITS TO LEFT
  GOLEM_OP_BTR, //BITS TO RIGHT
  GOLEM_OP_BNA, //BINARY AND
  GOLEM_OP_BNO, //BINARY OR

} GolemVMOpCode;

typedef enum
{
  GOLEM_DATA_TYPE_UNDEFINED,
  GOLEM_DATA_TYPE_INT8,
  GOLEM_DATA_TYPE_INT16,
  GOLEM_DATA_TYPE_INT32,
  GOLEM_DATA_TYPE_INT64,
  GOLEM_DATA_TYPE_UINT8,
  GOLEM_DATA_TYPE_UINT16,
  GOLEM_DATA_TYPE_UINT32,
  GOLEM_DATA_TYPE_UINT64,
  GOLEM_DATA_TYPE_FLOAT,
  GOLEM_DATA_TYPE_DOUBLE,
  GOLEM_DATA_TYPE_STRING,
  GOLEM_DATA_TYPE_OBJECT,
  GOLEM_DATA_TYPE_POINTER
} GolemVMDataType;

typedef union
{
  gint8 int8_v;
  gint16 int16_v;
  gint32 int32_v;
  gint64 int64_v;
  guint8 uint8_v;
  guint16 uint16_v;
  guint32 uint32_v;
  guint64 uint64_v;
  gfloat float_v;
  gdouble double_v;
  gpointer pointer_v;
}GolemVMData;

typedef struct
{
  GParameter *	m_parameter;
  guint 	n_parameter;
} GolemVMContruct;


typedef struct
{
  GolemVMOpCode code;
  union {
    GolemVMDataType type;
    struct {
      guint16 index;
      guint16 offset;
      guint8 size;
    } scope;
    guint32 arg0;
  } data;
}GolemVMOp;


typedef struct
{
  volatile guint32 n_ref;
  guint16	   n_size;
  GolemVMData *    m_data;
  GList * 	   m_garbage;
}GolemVMScopeData;

typedef struct
{
  GolemVMScopeData ** m_data;
  guint16 	      n_data;
}GolemVMScope;

typedef struct
{
  GolemVMData * m_data;
  GolemVMDataType * m_data_type;
  guint16 * m_data_size;
  guint16 n_data;
  GolemVMOp * m_op;
  guint32 n_op;
} GolemVMBody;

typedef struct
{
  gboolean (*invoke)(gpointer invoke,
		     guint8 argc,
		     GolemVMData * argv,
		     GolemVMData * ret,
		     GolemVMData * error);
} GolemVMInvocable;


GolemVMScope* 	golem_vm_scope_new(void);

void		golem_vm_scope_enter(GolemVMScope * scope,guint16 size);

void		golem_vm_scope_gc(GolemVMScope * scope,gpointer data);

void		golem_vm_scope_get(GolemVMScope * scope,
				     guint16 index,
				     guint16 offset,
				     guint8  size,
				     GolemVMData * dest);

void		golem_vm_scope_set(GolemVMScope * scope,
				     guint16 index,
				     guint16 offset,
				     guint8  size,
				     const GolemVMData * src);

void		golem_vm_scope_ptr(GolemVMScope * scope,
				     guint16 index,
				     guint16 offset,
				     GolemVMData * dest);

void		golem_vm_scope_exit(GolemVMScope * scope,
				    guint16 index);

GolemVMScope* 	golem_vm_scope_copy(GolemVMScope * scope);

void		golem_vm_scope_free(GolemVMScope * scope);


GolemVMBody *	golem_vm_body_new(void);

guint32		golem_vm_body_get_offset(GolemVMBody * body);

gsize		golem_vm_body_get_length(GolemVMBody * body);

guint32		golem_vm_body_write_data(GolemVMBody * body,
					 GolemVMData * reg,
					 GolemVMDataType reg_type,
					 guint16 reg_size);

void		golem_vm_body_write_op(GolemVMBody * body,
				       GolemVMOpCode code);

void		golem_vm_body_write_opn(GolemVMBody * body,
					 GolemVMOpCode code,
					 guint32 arg0);

void		golem_vm_body_update_opn(GolemVMBody * body,
					 guint32 opindex,
					 guint32 arg0);

void		golem_vm_body_write_opt(GolemVMBody * body,
					GolemVMOpCode code,
					GolemVMDataType type);

void		golem_vm_body_write_ops(GolemVMBody * body,
					GolemVMOpCode code,
					guint16 index,
					guint16 offset,
					guint8 size);

gboolean	golem_vm_body_run(GolemVMBody * body,
				  GolemVMScope * scope,
				  GolemVMData * ret,
				  GError ** error);

GolemVMBody *	golem_vm_body_copy(GolemVMBody * body);

void		golem_vm_body_free(GolemVMBody * body);

#endif /* GVM_H_ */
