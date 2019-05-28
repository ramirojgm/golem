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
#include <gobject/gvaluecollector.h>
#include <stdint.h>
#include <stdbool.h>

typedef int32_t		      	gbool_t;
typedef signed char		gchar_t;
typedef unsigned char	    	guchar_t;
typedef int8_t			gint8_t;
typedef uint8_t			guint8_t;
typedef int16_t			gint16_t;
typedef uint16_t		guint16_t;
typedef int32_t			gint32_t;
typedef uint32_t		guint32_t;
typedef int64_t			gint64_t;
typedef uint64_t		guint64_t;
typedef __int128_t		gint128_t;
typedef __uint128_t	      	guint128_t;
typedef float			gfloat32_t;
typedef double			gfloat64_t;
typedef long double		gfloat128_t;
typedef void *			gpointer_t;
typedef char *			gstring_t;

typedef struct {
	guint32_t v32;
	guint32_t v64;
} glength32_t;

typedef struct {
	guint16_t v32;
	guint16_t v64;
} glength16_t;

typedef struct {
	guint8_t v32;
	guint8_t v64;
} glength8_t;

typedef gboolean (*GolemVMSymbolFunc)(gpointer data,
				      const gchar * name,
				      gpointer * dest,
				      GError ** error);

#define glength_set(l,v) ((l).v32 = (l).v64 = (v))
#define glength_add(l,v) {(l).v32 += (v).v32; (l).v64 += (v).v64;}

#if UINTPTR_MAX == UINT64_MAX
  #define glength_get(l) (l).v64
#elif UINTPTR_MAX == UINT32_MAX
  #define glength_get(l) (l).v32
#endif

union _GolemValue {
	gbool_t		bool_v;
	gchar_t		char_v;
	guchar_t	uchar_v;
	gint8_t		int8_v;
	guint8_t	uint8_v;
	gint16_t	int16_v;
	guint16_t	uint16_v;
	gint32_t	int32_v;
	guint32_t	uint32_v;
	gint64_t	int64_v;
	guint64_t	uint64_v;
	gint128_t	int128_v;
	guint128_t	uint128_v;
	gfloat32_t	float32_v;
	gfloat64_t	float64_v;
	gfloat128_t	float128_v;
	gpointer_t	pointer_v;
	gstring_t	string_v;
};

typedef gint128_t 			GolemValue;

#define GOLEM_BOOL(v)		((union _GolemValue*)(v))->bool_v
#define GOLEM_CHAR(v)		((union _GolemValue*)(v))->char_v
#define GOLEM_UCHAR(v)		((union _GolemValue*)(v))->uchar_v
#define GOLEM_INT8(v)		((union _GolemValue*)(v))->int8_v
#define GOLEM_UINT8(v)		((union _GolemValue*)(v))->uint8_v
#define GOLEM_INT16(v)		((union _GolemValue*)(v))->int16_v
#define GOLEM_UINT16(v)		((union _GolemValue*)(v))->uint16_v
#define GOLEM_INT32(v)		((union _GolemValue*)(v))->int32_v
#define GOLEM_UINT32(v)		((union _GolemValue*)(v))->uint32_v
#define GOLEM_INT64(v)		((union _GolemValue*)(v))->int64_v
#define GOLEM_UINT64(v)		((union _GolemValue*)(v))->uint64_v
#define GOLEM_INT128(v)		((union _GolemValue*)(v))->int128_v
#define GOLEM_UINT128(v)	((union _GolemValue*)(v))->uint128_v
#define GOLEM_FLOAT32(v)	((union _GolemValue*)(v))->float32_v
#define GOLEM_FLOAT64(v)	((union _GolemValue*)(v))->float64_v
#define GOLEM_FLOAT128(v)	((union _GolemValue*)(v))->float128_v
#define GOLEM_POINTER(v)	((union _GolemValue*)(v))->pointer_v
#define GOLEM_STRING(v)		((union _GolemValue*)(v))->string_v

typedef enum
{
  /* OP */
  GOLEM_OP_PUT, 	//SCOPE PUT
  GOLEM_OP_GET, 	//SCOPE GET
  GOLEM_OP_DUP, 	//DUPLICATE ONE REGISTER
  GOLEM_OP_DRP, 	//DROP ONE REGISTER
  GOLEM_OP_DAT, 	//DATA
  GOLEM_OP_RET, 	//RETURN
  GOLEM_OP_ENT, 	//SCOPE ENTER
  GOLEM_OP_QFF, 	//QUEUE FOR FREE
  GOLEM_OP_EXT, 	//SCOPE EXIT

  /* ARITMETICAL OP */
  GOLEM_OP_AI32,	//ADD INTEGER 32BIT
  GOLEM_OP_AI64, 	//ADD INTEGER 64BIT
  GOLEM_OP_AI128,	//ADD INTEGER 128BIT
  GOLEM_OP_AF32, 	//ADD FLOAT 32BIT
  GOLEM_OP_AF64, 	//ADD FLOAT 64BIT
  GOLEM_OP_AF128, 	//ADD FLOAT 128BIT
  GOLEM_OP_SI32, 	//SUBSTRACT INTEGER 32BIT
  GOLEM_OP_SI64, 	//SUBSTRACT INTEGER 64BIT
  GOLEM_OP_SI128, 	//SUBSTRACT INTEGER 128BIT
  GOLEM_OP_SF32, 	//SUBSTRACT FLOAT 32BIT
  GOLEM_OP_SF64, 	//SUBSTRACT FLOAT 64BIT
  GOLEM_OP_SF128, 	//SUBSTRACT FLOAT 128BIT
  GOLEM_OP_MI32, 	//MULTIPLICATE INTEGER 32BIT
  GOLEM_OP_MI64, 	//MULTIPLICATE INTEGER 64BIT
  GOLEM_OP_MI128, 	//MULTIPLICATE INTEGER 128BIT
  GOLEM_OP_MF32, 	//MULTIPLICATE FLOAT 32BIT
  GOLEM_OP_MF64, 	//MULTIPLICATE FLOAT 64BIT
  GOLEM_OP_MF128, 	//MULTIPLICATE FLOAT 128BIT
  GOLEM_OP_DI32, 	//DIVIDE INTEGER 32BIT
  GOLEM_OP_DI64, 	//DIVIDE INTEGER 64BIT
  GOLEM_OP_DI128, 	//DIVIDE INTEGER 128BIT
  GOLEM_OP_DF32, 	//DIVIDE FLOAT 32BIT
  GOLEM_OP_DF64, 	//DIVIDE FLOAT 64BIT
  GOLEM_OP_DF128, 	//DIVIDE FLOAT 128BIT
  GOLEM_OP_NI32, 	//NEGATIVE INTEGER 32BIT
  GOLEM_OP_NI64, 	//NEGATIVE INTEGER 64BIT
  GOLEM_OP_NI128, 	//NEGATIVE INTEGER 128BIT
  GOLEM_OP_NF32, 	//NEGATIVE FLOAT 32BIT
  GOLEM_OP_NF64, 	//NEGATIVE FLOAT 64BIT
  GOLEM_OP_NF128, 	//NEGATIVE FLOAT 128BIT

  /* COMPARATION OP */
  GOLEM_OP_LI32,  	//LESS INTEGER 32BIT
  GOLEM_OP_LI64,  	//LESS INTEGER 64BIT
  GOLEM_OP_LI128,  	//LESS INTEGER 128BIT
  GOLEM_OP_LF32,  	//LESS FLOAT 32BIT
  GOLEM_OP_LF64,  	//LESS FLOAT 64BIT
  GOLEM_OP_LF128,  	//LESS FLOAT 128BIT
  GOLEM_OP_LP,    	//LESS POINTER
  GOLEM_OP_LII32,  	//LESS IQUAL INTEGER 32BIT
  GOLEM_OP_LII64,  	//LESS IQUAL INTEGER 64BIT
  GOLEM_OP_LII128, 	//LESS IQUAL INTEGER 128BIT
  GOLEM_OP_LIF32,  	//LESS IQUAL FLOAT 32BIT
  GOLEM_OP_LIF64,  	//LESS IQUAL FLOAT 64BIT
  GOLEM_OP_LIF128, 	//LESS IQUAL FLOAT 128BIT
  GOLEM_OP_LIP,    	//LESS IQUAL POINTER
  GOLEM_OP_GI32,  	//GREATER INTEGER 32BIT
  GOLEM_OP_GI64,  	//GREATER INTEGER 64BIT
  GOLEM_OP_GI128,  	//GREATER INTEGER 128BIT
  GOLEM_OP_GF32,  	//GREATER FLOAT 32BIT
  GOLEM_OP_GF64,  	//GREATER FLOAT 64BIT
  GOLEM_OP_GF128,  	//GREATER FLOAT 128BIT
  GOLEM_OP_GP,    	//GREATER POINTER
  GOLEM_OP_GII32,  	//GREATER IQUAL INTEGER 32BIT
  GOLEM_OP_GII64,  	//GREATER IQUAL INTEGER 64BIT
  GOLEM_OP_GII128, 	//GREATER IQUAL INTEGER 128BIT
  GOLEM_OP_GIF32,  	//GREATER IQUAL FLOAT 32BIT
  GOLEM_OP_GIF64,  	//GREATER IQUAL FLOAT 64BIT
  GOLEM_OP_GIF128, 	//GREATER IQUAL FLOAT 128BIT
  GOLEM_OP_GIP,    	//GREATER IQUAL POINTER
  GOLEM_OP_II32,  	//IQUAL INTEGER 32BIT
  GOLEM_OP_II64,  	//IQUAL INTEGER 64BIT
  GOLEM_OP_II128,  	//IQUAL INTEGER 128BIT
  GOLEM_OP_IF32,  	//IQUAL FLOAT 32BIT
  GOLEM_OP_IF64,  	//IQUAL FLOAT 64BIT
  GOLEM_OP_IF128,  	//IQUAL FLOAT 128BIT
  GOLEM_OP_IP,    	//IQUAL POINTER

  /* SEQUENCE CONTROL */
  GOLEM_OP_GOTO,   	//GOTO
  GOLEM_OP_IF,   	//IF

  /* MEMORY */
  GOLEM_OP_ADDR, 	//ADDRESS OF
  GOLEM_OP_PMOV,  //POINTER MOVE
  GOLEM_OP_PSET, 	//POINTER SET
  GOLEM_OP_PGET, 	//POINTER GET

  /* FUNCTION */
  GOLEM_OP_LD, 		//FUNCTION LOAD
  GOLEM_OP_FRT, 	//FUNCTION RETURN
  GOLEM_OP_APT, 	//FUNCTION PUT ARGUMENT
  GOLEM_OP_AGT, 	//FUNCTION GET ARGUMENT
  GOLEM_OP_CAL, 	//CALL FUNCTION

  /* BINARY OP */
  GOLEM_OP_AN32,	//AND AT 32BIT
  GOLEM_OP_AN64,	//AND AT 64BIT
  GOLEM_OP_AN128,	//AND AT 128BIT
  GOLEM_OP_OR32, 	//OR AT 32BIT
  GOLEM_OP_OR64, 	//OR AT 64BIT
  GOLEM_OP_OR128, 	//OR AT 128BIT
  GOLEM_OP_NT32,	//NOT AT 32BIT
  GOLEM_OP_NT64,	//NOT AT 64BIT
  GOLEM_OP_NT128,	//NOT AT 128BIT
  GOLEM_OP_XOR32,	//XOR AT 32BIT
  GOLEM_OP_XOR64,	//XOR AT 32BIT
  GOLEM_OP_XOR128,	//XOR AT 128BIT
  GOLEM_OP_BL, 		//BITS TO LEFT
  GOLEM_OP_BR, 		//BITS TO RIGHT

  /* TRY */
  GOLEM_OP_TRY,		//TRY

  /* CONVERT */
  GOLEM_OP_I32TF32, 	//CONVERT I32 TO F32
  GOLEM_OP_I64TF64, 	//CONVERT I64 TO F64
  GOLEM_OP_I128TF128, 	//CONVERT I128 TO F128
  /* CONSTANTS OP */
  GOLEM_OP_TRUE,	//TRUE
  GOLEM_OP_ZERO,	//0
  GOLEM_OP_NULL,	//NULL

  /* FUNCTIONS */
  GOLEM_OP_STRDUP,	//STRDUP FUNCTION


  GOLEM_OP_N
} GolemVMOpCode;

typedef struct
{
  guint16_t		index;
  glength16_t	offset;
  glength8_t 	size;
} GolemVMOpScope;

typedef struct
{
  GolemVMOpCode code;
  union {
    GolemVMOpScope vscope;
    glength16_t vlength; //16BIT LENGTH ARGUMENT
    guint16_t v16; //16BIT ARGUMENT
    guint32_t v32; //32BIT ARGUMENT
  } data;
} GolemVMOp;

typedef struct
{
  GolemVMOp     op;
  gpointer_t    op_func;
} GolemVMOpLD;

typedef struct
{
  volatile guint32_t n_ref;
  guint16_t	   n_size;
  GolemValue * m_data;
  GList * 	   m_queue_free;
} GolemVMScopeData;

typedef struct
{
  GolemVMScopeData **	m_data;
  guint16_t	      		n_data;
} GolemVMScope;

typedef struct
{
  GolemValue data;
  guint16_t  length;
  gbool_t    byte_array;
} GolemVMData;

typedef struct _GolemVMLink GolemVMLink;

typedef struct
{
  GolemVMData *	 m_data;
  guint16_t 	 n_data;
  GolemVMLink ** m_links;
  guint32_t      n_links;
  GolemVMOpLD *  m_op;
  guint32_t	 n_op;
} GolemVMBody;

typedef struct
{
  GolemValue m_stack[64];
  guint8_t   n_stack;

  GolemValue m_stack_va[64];
  guint8_t   n_stack_va;

  guint32_t  n_op;

  GolemValue * v_arg;
  guint8_t     c_arg;
  guint8_t     n_arg;

  GolemValue ret;
  GError *   error;

  GolemVMBody * body;
  GolemVMScope* scope;
} GolemVMStack;


G_BEGIN_DECLS


GLIB_AVAILABLE_IN_ALL
GolemVMScope* 	golem_vm_scope_new(void);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_enter(GolemVMScope * scope,
				     guint16_t size);


GLIB_AVAILABLE_IN_ALL
void    	golem_vm_scope_get(GolemVMScope * scope,
				    guint16_t index,
				    guint16_t offset,
				    guint8_t  size,
				    GolemValue * dest);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_put(GolemVMScope * scope,
				    guint16_t index,
				    guint16_t offset,
				    guint8_t  size,
				    GolemValue * src);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_queue_free (GolemVMScope * scope,
					   gpointer_t src,
					   GDestroyNotify free_fn);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_get_address (GolemVMScope * scope,
					    guint16_t index,
					    guint16_t offset,
					    GolemValue * dest);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_exit(GolemVMScope * scope,
				    guint16_t index);

GLIB_AVAILABLE_IN_ALL
GolemVMScope* 	golem_vm_scope_copy(GolemVMScope * scope);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_scope_free(GolemVMScope * scope);


GLIB_AVAILABLE_IN_ALL
GolemVMBody *	golem_vm_body_new(void);

GLIB_AVAILABLE_IN_ALL
guint32_t	golem_vm_body_link(GolemVMBody * body,
				   const gchar * link_name);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_vm_body_link_dynamic(GolemVMBody * body,
					   GolemVMSymbolFunc func,
					   gpointer data,
					   GError ** error);

GLIB_AVAILABLE_IN_ALL
guint32_t	golem_vm_body_get_offset(GolemVMBody * body);

GLIB_AVAILABLE_IN_ALL
guint32_t	golem_vm_body_get_length(GolemVMBody * body);

GLIB_AVAILABLE_IN_ALL
guint16_t	golem_vm_body_write_value(GolemVMBody * body,
                					          GolemValue * data);

GLIB_AVAILABLE_IN_ALL
guint16_t	golem_vm_body_write_string(GolemVMBody * body,
					   gstring_t str,
					   gint16_t length);

GLIB_AVAILABLE_IN_ALL
guint16_t	golem_vm_body_write_data (GolemVMBody * body,
					   gpointer_t data,
					   guint16_t length);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_op(GolemVMBody * body,
				                       GolemVMOpCode code);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_op16(GolemVMBody * body,
					                       GolemVMOpCode code,
					                       guint16_t arg0);
GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_op32(GolemVMBody * body,
					                       GolemVMOpCode code,
					                       guint32_t arg0);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_opl(GolemVMBody * body,
					GolemVMOpCode code,
					glength16_t arg0);
GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_update_op16(GolemVMBody * body,
					                        guint32_t opindex,
					                        guint16_t arg0);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_update_op32(GolemVMBody * body,
					                        guint32_t opindex,
					                        guint32_t arg0);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_update_opl(GolemVMBody * body,
					  guint32_t opindex,
					  glength16_t arg0);

GLIB_AVAILABLE_IN_ALL
void		golem_vm_body_write_ops(GolemVMBody * body,
					                      GolemVMOpCode code,
					                      guint16_t index,
					                      glength16_t offset,
					                      glength8_t size);

GLIB_AVAILABLE_IN_ALL
gboolean	golem_vm_body_run(GolemVMBody * body,
				  GolemVMScope * scope,
				  guint16_t 	argc,
				  GolemValue *  argv,
				  GolemValue *  ret,
				  GError ** error);

GLIB_AVAILABLE_IN_ALL
GolemVMBody *	golem_vm_body_copy(GolemVMBody * body);

GLIB_AVAILABLE_IN_ALL
void		    golem_vm_body_free(GolemVMBody * body);


G_END_DECLS

#endif /* GOLEM_VM_H_ */
