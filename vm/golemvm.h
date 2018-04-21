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
#include <gio/gio.h>
#include <glib-object.h>

typedef enum
{
  /* OP */
  GOLEM_OP_PH, //PUSH VARIABLE
  GOLEM_OP_PP, //POP VARIABLE
  GOLEM_OP_DP, //DUPLICATE
  GOLEM_OP_DC, //DISCARD
  GOLEM_OP_DT, //DATA
  GOLEM_OP_RT, //RETURN
  GOLEM_OP_SE, //SCOPE ENTER
  GOLEM_OP_GC, //GARBAGE COLLECTOR
  GOLEM_OP_SX, //SCOPE EXIT

  /* ARITMETICAL OP */
  GOLEM_OP_AI32, //ADD INTEGER 32BIT
  GOLEM_OP_AI64, //ADD INTEGER 64BIT
  GOLEM_OP_AF32, //ADD FLOAT 32BIT
  GOLEM_OP_AD64, //ADD DOUBLE 64BIT
  GOLEM_OP_SI32, //SUBSTRACT INTEGER 32BIT
  GOLEM_OP_SI64, //SUBSTRACT INTEGER 64BIT
  GOLEM_OP_SF32, //SUBSTRACT FLOAT 32BIT
  GOLEM_OP_SD64, //SUBSTRACT DOUBLE 64BIT
  GOLEM_OP_MI32, //MULTIPLICATE INTEGER 32BIT
  GOLEM_OP_MI64, //MULTIPLICATE INTEGER 64BIT
  GOLEM_OP_MF32, //MULTIPLICATE FLOAT 32BIT
  GOLEM_OP_MD64, //MULTIPLICATE DOUBLE 64BIT
  GOLEM_OP_DI32, //DIVIDE INTEGER 32BIT
  GOLEM_OP_DI64, //DIVIDE INTEGER 64BIT
  GOLEM_OP_DF32, //DIVIDE FLOAT 32BIT
  GOLEM_OP_DD64, //DIVIDE DOUBLE 64BIT
  GOLEM_OP_NI32, //NEGATIVE INTEGER 32BIT
  GOLEM_OP_NI64, //NEGATIVE INTEGER 64BIT
  GOLEM_OP_NF32, //NEGATIVE FLOAT 32BIT
  GOLEM_OP_ND64, //NEGATIVE DOUBLE 64BIT
  GOLEM_OP_RI32, //MODULE INTEGER 32BIT
  GOLEM_OP_RI64, //MODULE INTEGER 64BIT
  GOLEM_OP_RF32, //MODULE FLOAT 32BIT
  GOLEM_OP_RD64, //MODULE DOUBLE 64BIT
  GOLEM_OP_PD64, //POW DOUBLE 64BIT

  /* COMPARATION OP */
  GOLEM_OP_LI32,  //LESS INTEGER 32BIT
  GOLEM_OP_LI64,  //LESS INTEGER 64BIT
  GOLEM_OP_LF32,  //LESS FLOAT 32BIT
  GOLEM_OP_LD64,  //LESS DOUBLE 64BIT
  GOLEM_OP_LP,  //LESS POINTER
  GOLEM_OP_LII32,  //LESS IQUAL INTEGER 32BIT
  GOLEM_OP_LII64,  //LESS IQUAL INTEGER 64BIT
  GOLEM_OP_LIF32,  //LESS IQUAL FLOAT 32BIT
  GOLEM_OP_LID64,  //LESS IQUAL DOUBLE 64BIT
  GOLEM_OP_LIP,  //LESS IQUAL POINTER
  GOLEM_OP_GI32,  //GREATER INTEGER 32BIT
  GOLEM_OP_GI64,  //GREATER INTEGER 64BIT
  GOLEM_OP_GF32,  //GREATER FLOAT 32BIT
  GOLEM_OP_GD64,  //GREATER DOUBLE 64BIT
  GOLEM_OP_GP,  //GREATER POINTER
  GOLEM_OP_GII32,  //GREATER IQUAL INTEGER 32BIT
  GOLEM_OP_GII64,  //GREATER IQUAL INTEGER 64BIT
  GOLEM_OP_GIF32,  //GREATER IQUAL FLOAT 32BIT
  GOLEM_OP_GID64,  //GREATER IQUAL DOUBLE 64BIT
  GOLEM_OP_GIP,  //GREATER IQUAL POINTER
  GOLEM_OP_II32, //IQUAL INTEGER 32BIT
  GOLEM_OP_II64, //IQUAL INTEGER 64BIT
  GOLEM_OP_IF32, //IQUAL FLOAT 32BIT
  GOLEM_OP_ID64, //IQUAL DOUBLE 64BIT
  GOLEM_OP_IP, //IQUAL POINTER

  /* JUMP */
  GOLEM_OP_JP, //JUMP
  GOLEM_OP_IF, //IF

  /* HANDLE EXCEPTION */
  GOLEM_OP_AHE, //ADD HANDLE EXCEPTION
  GOLEM_OP_THW, //THROW EXCEPTION
  GOLEM_OP_EHE, //EXTERNAL HANDLE EXCEPTION
  GOLEM_OP_RHE, //REMOVE HANDLE EXCEPTION
  /* MEMORY */
  GOLEM_OP_MA, //MEMORY ALLOC
  GOLEM_OP_MF, //MEMORY FREE
  GOLEM_OP_PO, //POINTER OF
  GOLEM_OP_PW, //WRITE POINTER
  GOLEM_OP_PR, //READ POINTER
  /* FUNCTION */
  GOLEM_OP_RA, //READ ARGUMENT
  GOLEM_OP_WA, //WRITE ARGUMENT
  GOLEM_OP_CL, //CALL FUNCTION

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
  /* DATA OP */
  GOLEM_OP_TRUE, //TRUE
  GOLEM_OP_NULL //NULL

} GolemVMOpCode;

typedef enum
{
  GOLEM_TYPE_CODE_UNDEFINED,
  GOLEM_TYPE_CODE_INT8,
  GOLEM_TYPE_CODE_INT16,
  GOLEM_TYPE_CODE_INT32,
  GOLEM_TYPE_CODE_INT64,
  GOLEM_TYPE_CODE_UINT8,
  GOLEM_TYPE_CODE_UINT16,
  GOLEM_TYPE_CODE_UINT32,
  GOLEM_TYPE_CODE_UINT64,
  GOLEM_TYPE_CODE_FLOAT,
  GOLEM_TYPE_CODE_DOUBLE,
  GOLEM_TYPE_CODE_POINTER,
  GOLEM_TYPE_CODE_SYMBOL
} GolemTypeCode;

typedef struct
{
  union {
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
  } data[2];
}GolemVMData;


typedef	gboolean (*GolemCallableCall)(gpointer invoke,
				       guint8 argc,
				       GolemVMData * argv,
				       GolemVMData * ret,
				       GError ** error);

typedef void	 (*GolemCallableFinalize)(gpointer invoke);


typedef struct
{
  GolemVMOpCode code: 8;
  union {
    struct {
      guint16 index;
      guint16 offset;
      guint8 size;
    } scope_v;
    guint16 int16_v;
    guint32 int32_v;
  } data;
}GolemVMOp;


typedef struct
{
  volatile guint32 n_ref;
  guint16	   n_size;
  GolemVMData *    m_data;
  GList * 	   m_gc;
}GolemVMScopeData;

typedef struct
{
  GolemVMScopeData ** m_data;
  guint16 	      n_data;
}GolemVMScope;

typedef struct
{
  GolemVMData * m_data;
  GolemTypeCode * m_data_type;
  guint16 * m_data_size;
  guint16 n_data;
  GolemVMOp * m_op;
  guint32 n_op;
} GolemVMBody;

typedef struct
{
  volatile guint32 refcount;
  GType type;
  gpointer data;
  GFreeFunc free_func;
} GolemRefPtr;

typedef struct
{
  GolemCallableCall call;
  GolemCallableFinalize finalize;
} GolemCallable;

G_BEGIN_DECLS

GLIB_AVAILABLE_IN_ALL
GolemRefPtr* 	golem_refptr_new(gpointer ptr,
				 GType type,
				 GFreeFunc free_func);

GLIB_AVAILABLE_IN_ALL
GolemRefPtr*	golem_refptr_ref(GolemRefPtr * refptr);

GLIB_AVAILABLE_IN_ALL
void		golem_refptr_unref(GolemRefPtr * refptr);

GLIB_AVAILABLE_IN_ALL
GolemVMScope* 	golem_vm_scope_new(void);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_enter(GolemVMScope * scope,
				     guint16 size);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_gc(GolemVMScope * scope,
				  GolemRefPtr * data);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_get(GolemVMScope * scope,
				     guint16 index,
				     guint16 offset,
				     guint8  size,
				     GolemVMData * dest);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_set(GolemVMScope * scope,
				     guint16 index,
				     guint16 offset,
				     guint8  size,
				     const GolemVMData * src);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_ptr(GolemVMScope * scope,
				     guint16 index,
				     guint16 offset,
				     GolemVMData * dest);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_exit(GolemVMScope * scope,
				    guint16 index);

GLIB_AVAILABLE_IN_ALL
GolemVMScope* 	golem_vm_scope_copy(GolemVMScope * scope);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_free(GolemVMScope * scope);

GLIB_AVAILABLE_IN_ALL
GolemCallable * golem_callable_new(gsize callable_size);

GLIB_AVAILABLE_IN_ALL
GolemCallable *	golem_callable_ref(GolemCallable * callable);

GLIB_AVAILABLE_IN_ALL
void		golem_callable_unref(GolemCallable * callable);

GLIB_AVAILABLE_IN_ALL
GolemVMBody *	golem_vm_body_new(void);

GLIB_AVAILABLE_IN_ALL
guint32		golem_vm_body_get_offset(GolemVMBody * body);

GLIB_AVAILABLE_IN_ALL
gsize		golem_vm_body_get_length(GolemVMBody * body);

GLIB_AVAILABLE_IN_ALL
guint16		golem_vm_body_write_data(GolemVMBody * body,
					 GolemVMData * reg,
					 GolemTypeCode reg_type,
					 guint16 reg_size);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_op(GolemVMBody * body,
				       GolemVMOpCode code);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_op16(GolemVMBody * body,
					 GolemVMOpCode code,
					 guint16 arg0);
GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_op32(GolemVMBody * body,
					 GolemVMOpCode code,
					 guint32 arg0);
GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_update_op16(GolemVMBody * body,
					 guint32 opindex,
					 guint16 arg0);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_update_op32(GolemVMBody * body,
					 guint32 opindex,
					 guint32 arg0);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_ops(GolemVMBody * body,
					GolemVMOpCode code,
					guint16 index,
					guint16 offset,
					guint8 size);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_vm_body_run(GolemVMBody * body,
				  GolemVMScope * scope,
				  guint16 	argc,
				  GolemVMData * argv,
				  GolemVMData * ret,
				  GError ** error);

GLIB_AVAILABLE_IN_ALL
GolemVMBody *	golem_vm_body_copy(GolemVMBody * body);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_free(GolemVMBody * body);

G_END_DECLS

#endif /* GOLEM_VM_H_ */
