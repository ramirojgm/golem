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

#define GOLEM_VM_SYMBOL_SIZE 512

typedef enum
{
  /* OP */
  GOLEM_OP_PSH, //PUSH VARIABLE
  GOLEM_OP_POP, //POP VARIABLE
  GOLEM_OP_DAT, //POP DATA
  GOLEM_OP_RET, //RETURN
  GOLEM_OP_BCX, //BEGIN CONTEXT
  GOLEM_OP_ECX, //END CONTEXT
  GOLEM_OP_JMP, //JUMP
  GOLEM_OP_CAL, //CALL FUNCTION
  /* TRY CATCH */
  GOLEM_OP_BCE, //BEGIN CAPTURE EXCEPTION
  GOLEM_OP_ECE, //END CAPTURE EXCEPTION
  /* MEMORY */
  GOLEM_OP_ALC, //ALLOC MEMORY
  GOLEM_OP_FRE, //FREE MEMORY
  /* OBJECT OP */
  GOLEM_OP_NEW, //NEW OBJECT
  GOLEM_OP_IST, //INDEX SET
  GOLEM_OP_IGT, //INDEX GET
  GOLEM_OP_PST, //PROPERTY SET
  GOLEM_OP_PGT, //PROPERTY GET
  GOLEM_OP_IRF, //INCREASE REFERENCE
  GOLEM_OP_DRF, //DECREASE REFERENCE
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
  GOLEM_REG_TYPE_UNDEFINED,
  GOLEM_REG_TYPE_INT8,
  GOLEM_REG_TYPE_INT16,
  GOLEM_REG_TYPE_INT32,
  GOLEM_REG_TYPE_INT64,
  GOLEM_REG_TYPE_UINT8,
  GOLEM_REG_TYPE_UINT16,
  GOLEM_REG_TYPE_UINT32,
  GOLEM_REG_TYPE_UINT64,
  GOLEM_REG_TYPE_FLOAT,
  GOLEM_REG_TYPE_DOUBLE,
  GOLEM_REG_TYPE_STRING,
  GOLEM_REG_TYPE_OBJECT,
  GOLEM_REG_TYPE_POINTER
} GolemVMRegType;

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
}GolemVMReg;

typedef struct
{
  GolemVMOpCode code: 8;
}GolemVMOp;

typedef struct
{
  GolemVMOpCode code: 8;
  GolemVMRegType arg0: 8;
}GolemVMOpType;

typedef struct
{
  GolemVMOpCode code: 8;
  guint32 arg0;
}GolemVMOp1;


typedef struct
{
  volatile guint32 refcount;
  guint16	n_reg;
  GolemVMReg *  reg;
}GolemVMContextData;

typedef struct
{
  GolemVMContextData ** m_data;
  guint16 n_data;
}GolemVMContext;

typedef struct
{
  GolemVMReg * m_data;
  GolemVMRegType * t_data;
  guint16 n_data;
  GolemVMOp ** m_op;
  guint32 n_op;
}GolemVMBody;


typedef struct
{
  guint8 m_symbol[GOLEM_VM_SYMBOL_SIZE];
  GolemVMRegType m_arg[G_MAXUINT8];
  guint16 n_arg;
  GolemVMContext * m_context;
  GolemVMBody * m_body;
}GolemVMSymbol;

gboolean	golem_vm_body_run(GolemVMBody * body,
				  GolemVMContext * context,
				  GError ** error);

GolemVMBody *	golem_vm_body_copy(GolemVMBody * body);

void		golem_vm_body_free(GolemVMBody * body);



GolemVMSymbol * golem_vm_symbol_new(GolemVMBody * body,
				    GolemVMContext * context,
				    ...);

GolemVMSymbol * golem_vm_symbol_newv(GolemVMBody * body,
				     GolemVMContext * context,
				     GolemVMRegType * varguments,
				     guint16 narguments);

GolemVMReg	golem_vm_symbol_invoke(GolemVMSymbol * symbol,...);

gboolean	golem_vm_symbol_invokev(GolemVMSymbol * symbol,
					const GolemVMReg * reg,
					GolemVMReg * result,
					GError ** error);

void		golem_vm_symbol_free(GolemVMSymbol * symbol);

#endif /* GVM_H_ */
