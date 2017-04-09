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

#include "golem.h"
#include <sys/mman.h>
#include <errno.h>
#include <memory.h>

typedef union
{
  guint8 uint8;
  gint8 int8;
  guint32 uint32;
  gint32 int32;
  guint64 uint64;
  gint64 int64;
  gulong ulong64;
  glong long64;
  gfloat float32;
  gdouble double64;
  gpointer pointer;
}_InvokeReturn;

typedef union
{
  GType type;
  gboolean boolean;
  guint8 uint8;
  gint8 int8;
  guint32 uint32;
  gint32 int32;
  guint64 uint64;
  gint64 int64;
  gulong ulong64;
  glong long64;
  gfloat float32;
  gdouble double64;
  gpointer pointer;
}_InvokeArg;

typedef _InvokeReturn (*_GolemLLMInvoke)(gpointer,GolemStructBuilder*);

static _InvokeReturn
_golem_llm_invoke_0(gpointer address,GolemStructBuilder * args)
{
  typedef gint64 (*_InvokeSymbol_0)();
  return (_InvokeReturn)((_InvokeSymbol_0) address)();
}

static _InvokeReturn
_golem_llm_invoke_1(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[1]; } _InvokeArgs_1;
  typedef gint64 (*_InvokeSymbol_1)(_InvokeArgs_1);
  return (_InvokeReturn)((_InvokeSymbol_1) address)(*((_InvokeArgs_1*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_2(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[2]; } _InvokeArgs_2;
  typedef gint64 (*_InvokeSymbol_2)(_InvokeArgs_2);
  return (_InvokeReturn)((_InvokeSymbol_2) address)(*((_InvokeArgs_2*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_3(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[3]; } _InvokeArgs_3;
  typedef gint64 (*_InvokeSymbol_3)(_InvokeArgs_3);
  return (_InvokeReturn)((_InvokeSymbol_3) address)(*((_InvokeArgs_3*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_4(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[4]; } _InvokeArgs_4;
  typedef gint64 (*_InvokeSymbol_4)(_InvokeArgs_4);
  return (_InvokeReturn)((_InvokeSymbol_4) address)(*((_InvokeArgs_4*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_5(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[5]; } _InvokeArgs_5;
  typedef gint64 (*_InvokeSymbol_5)(_InvokeArgs_5);
  return (_InvokeReturn)((_InvokeSymbol_5) address)(*((_InvokeArgs_5*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_6(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[6]; } _InvokeArgs_6;
  typedef gint64 (*_InvokeSymbol_6)(_InvokeArgs_6);
  return (_InvokeReturn)((_InvokeSymbol_6) address)(*((_InvokeArgs_6*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_7(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[7]; } _InvokeArgs_7;
  typedef gint64 (*_InvokeSymbol_7)(_InvokeArgs_7);
  return (_InvokeReturn)((_InvokeSymbol_7) address)(*((_InvokeArgs_7*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_8(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[8]; } _InvokeArgs_8;
  typedef gint64 (*_InvokeSymbol_8)(_InvokeArgs_8);
  return (_InvokeReturn)((_InvokeSymbol_8) address)(*((_InvokeArgs_8*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_9(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[9]; } _InvokeArgs_9;
  typedef gint64 (*_InvokeSymbol_9)(_InvokeArgs_9);
  return (_InvokeReturn)((_InvokeSymbol_9) address)(*((_InvokeArgs_9*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_10(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[10]; } _InvokeArgs_10;
  typedef gint64 (*_InvokeSymbol_10)(_InvokeArgs_10);
  return (_InvokeReturn)((_InvokeSymbol_10) address)(*((_InvokeArgs_10*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_11(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[11]; } _InvokeArgs_11;
  typedef gint64 (*_InvokeSymbol_11)(_InvokeArgs_11);
  return (_InvokeReturn)((_InvokeSymbol_11) address)(*((_InvokeArgs_11*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_12(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[12]; } _InvokeArgs_12;
  typedef gint64 (*_InvokeSymbol_12)(_InvokeArgs_12);
  return (_InvokeReturn)((_InvokeSymbol_12) address)(*((_InvokeArgs_12*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_13(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[13]; } _InvokeArgs_13;
  typedef gint64 (*_InvokeSymbol_13)(_InvokeArgs_13);
  return (_InvokeReturn)((_InvokeSymbol_13) address)(*((_InvokeArgs_13*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_14(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[14]; } _InvokeArgs_14;
  typedef gint64 (*_InvokeSymbol_14)(_InvokeArgs_14);
  return (_InvokeReturn)((_InvokeSymbol_14) address)(*((_InvokeArgs_14*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_15(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[15]; } _InvokeArgs_15;
  typedef gint64 (*_InvokeSymbol_15)(_InvokeArgs_15);
  return (_InvokeReturn)((_InvokeSymbol_15) address)(*((_InvokeArgs_15*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_16(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[16]; } _InvokeArgs_16;
  typedef gint64 (*_InvokeSymbol_16)(_InvokeArgs_16);
  return (_InvokeReturn)((_InvokeSymbol_16) address)(*((_InvokeArgs_16*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_17(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[17]; } _InvokeArgs_17;
  typedef gint64 (*_InvokeSymbol_17)(_InvokeArgs_17);
  return (_InvokeReturn)((_InvokeSymbol_17) address)(*((_InvokeArgs_17*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_18(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[18]; } _InvokeArgs_18;
  typedef gint64 (*_InvokeSymbol_18)(_InvokeArgs_18);
  return (_InvokeReturn)((_InvokeSymbol_18) address)(*((_InvokeArgs_18*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_19(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[19]; } _InvokeArgs_19;
  typedef gint64 (*_InvokeSymbol_19)(_InvokeArgs_19);
  return (_InvokeReturn)((_InvokeSymbol_19) address)(*((_InvokeArgs_19*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_20(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[20]; } _InvokeArgs_20;
  typedef gint64 (*_InvokeSymbol_20)(_InvokeArgs_20);
  return (_InvokeReturn)((_InvokeSymbol_20) address)(*((_InvokeArgs_20*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_21(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[21]; } _InvokeArgs_21;
  typedef gint64 (*_InvokeSymbol_21)(_InvokeArgs_21);
  return (_InvokeReturn)((_InvokeSymbol_21) address)(*((_InvokeArgs_21*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_22(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[22]; } _InvokeArgs_22;
  typedef gint64 (*_InvokeSymbol_22)(_InvokeArgs_22);
  return (_InvokeReturn)((_InvokeSymbol_22) address)(*((_InvokeArgs_22*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_23(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[23]; } _InvokeArgs_23;
  typedef gint64 (*_InvokeSymbol_23)(_InvokeArgs_23);
  return (_InvokeReturn)((_InvokeSymbol_23) address)(*((_InvokeArgs_23*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_24(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[24]; } _InvokeArgs_24;
  typedef gint64 (*_InvokeSymbol_24)(_InvokeArgs_24);
  return (_InvokeReturn)((_InvokeSymbol_24) address)(*((_InvokeArgs_24*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_25(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[25]; } _InvokeArgs_25;
  typedef gint64 (*_InvokeSymbol_25)(_InvokeArgs_25);
  return (_InvokeReturn)((_InvokeSymbol_25) address)(*((_InvokeArgs_25*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_26(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[26]; } _InvokeArgs_26;
  typedef gint64 (*_InvokeSymbol_26)(_InvokeArgs_26);
  return (_InvokeReturn)((_InvokeSymbol_26) address)(*((_InvokeArgs_26*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_27(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[27]; } _InvokeArgs_27;
  typedef gint64 (*_InvokeSymbol_27)(_InvokeArgs_27);
  return (_InvokeReturn)((_InvokeSymbol_27) address)(*((_InvokeArgs_27*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_28(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[28]; } _InvokeArgs_28;
  typedef gint64 (*_InvokeSymbol_28)(_InvokeArgs_28);
  return (_InvokeReturn)((_InvokeSymbol_28) address)(*((_InvokeArgs_28*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_29(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[29]; } _InvokeArgs_29;
  typedef gint64 (*_InvokeSymbol_29)(_InvokeArgs_29);
  return (_InvokeReturn)((_InvokeSymbol_29) address)(*((_InvokeArgs_29*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_30(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[30]; } _InvokeArgs_30;
  typedef gint64 (*_InvokeSymbol_30)(_InvokeArgs_30);
  return (_InvokeReturn)((_InvokeSymbol_30) address)(*((_InvokeArgs_30*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_31(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[31]; } _InvokeArgs_31;
  typedef gint64 (*_InvokeSymbol_31)(_InvokeArgs_31);
  return (_InvokeReturn)((_InvokeSymbol_31) address)(*((_InvokeArgs_31*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_32(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[32]; } _InvokeArgs_32;
  typedef gint64 (*_InvokeSymbol_32)(_InvokeArgs_32);
  return (_InvokeReturn)((_InvokeSymbol_32) address)(*((_InvokeArgs_32*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_33(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[33]; } _InvokeArgs_33;
  typedef gint64 (*_InvokeSymbol_33)(_InvokeArgs_33);
  return (_InvokeReturn)((_InvokeSymbol_33) address)(*((_InvokeArgs_33*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_34(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[34]; } _InvokeArgs_34;
  typedef gint64 (*_InvokeSymbol_34)(_InvokeArgs_34);
  return (_InvokeReturn)((_InvokeSymbol_34) address)(*((_InvokeArgs_34*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_35(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[35]; } _InvokeArgs_35;
  typedef gint64 (*_InvokeSymbol_35)(_InvokeArgs_35);
  return (_InvokeReturn)((_InvokeSymbol_35) address)(*((_InvokeArgs_35*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_36(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[36]; } _InvokeArgs_36;
  typedef gint64 (*_InvokeSymbol_36)(_InvokeArgs_36);
  return (_InvokeReturn)((_InvokeSymbol_36) address)(*((_InvokeArgs_36*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_37(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[37]; } _InvokeArgs_37;
  typedef gint64 (*_InvokeSymbol_37)(_InvokeArgs_37);
  return (_InvokeReturn)((_InvokeSymbol_37) address)(*((_InvokeArgs_37*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_38(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[38]; } _InvokeArgs_38;
  typedef gint64 (*_InvokeSymbol_38)(_InvokeArgs_38);
  return (_InvokeReturn)((_InvokeSymbol_38) address)(*((_InvokeArgs_38*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_39(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[39]; } _InvokeArgs_39;
  typedef gint64 (*_InvokeSymbol_39)(_InvokeArgs_39);
  return (_InvokeReturn)((_InvokeSymbol_39) address)(*((_InvokeArgs_39*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_40(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[40]; } _InvokeArgs_40;
  typedef gint64 (*_InvokeSymbol_40)(_InvokeArgs_40);
  return (_InvokeReturn)((_InvokeSymbol_40) address)(*((_InvokeArgs_40*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_41(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[41]; } _InvokeArgs_41;
  typedef gint64 (*_InvokeSymbol_41)(_InvokeArgs_41);
  return (_InvokeReturn)((_InvokeSymbol_41) address)(*((_InvokeArgs_41*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_42(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[42]; } _InvokeArgs_42;
  typedef gint64 (*_InvokeSymbol_42)(_InvokeArgs_42);
  return (_InvokeReturn)((_InvokeSymbol_42) address)(*((_InvokeArgs_42*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_43(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[43]; } _InvokeArgs_43;
  typedef gint64 (*_InvokeSymbol_43)(_InvokeArgs_43);
  return (_InvokeReturn)((_InvokeSymbol_43) address)(*((_InvokeArgs_43*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_44(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[44]; } _InvokeArgs_44;
  typedef gint64 (*_InvokeSymbol_44)(_InvokeArgs_44);
  return (_InvokeReturn)((_InvokeSymbol_44) address)(*((_InvokeArgs_44*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_45(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[45]; } _InvokeArgs_45;
  typedef gint64 (*_InvokeSymbol_45)(_InvokeArgs_45);
  return (_InvokeReturn)((_InvokeSymbol_45) address)(*((_InvokeArgs_45*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_46(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[46]; } _InvokeArgs_46;
  typedef gint64 (*_InvokeSymbol_46)(_InvokeArgs_46);
  return (_InvokeReturn)((_InvokeSymbol_46) address)(*((_InvokeArgs_46*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_47(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[47]; } _InvokeArgs_47;
  typedef gint64 (*_InvokeSymbol_47)(_InvokeArgs_47);
  return (_InvokeReturn)((_InvokeSymbol_47) address)(*((_InvokeArgs_47*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_48(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[48]; } _InvokeArgs_48;
  typedef gint64 (*_InvokeSymbol_48)(_InvokeArgs_48);
  return (_InvokeReturn)((_InvokeSymbol_48) address)(*((_InvokeArgs_48*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_49(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[49]; } _InvokeArgs_49;
  typedef gint64 (*_InvokeSymbol_49)(_InvokeArgs_49);
  return (_InvokeReturn)((_InvokeSymbol_49) address)(*((_InvokeArgs_49*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_50(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[50]; } _InvokeArgs_50;
  typedef gint64 (*_InvokeSymbol_50)(_InvokeArgs_50);
  return (_InvokeReturn)((_InvokeSymbol_50) address)(*((_InvokeArgs_50*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_51(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[51]; } _InvokeArgs_51;
  typedef gint64 (*_InvokeSymbol_51)(_InvokeArgs_51);
  return (_InvokeReturn)((_InvokeSymbol_51) address)(*((_InvokeArgs_51*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_52(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[52]; } _InvokeArgs_52;
  typedef gint64 (*_InvokeSymbol_52)(_InvokeArgs_52);
  return (_InvokeReturn)((_InvokeSymbol_52) address)(*((_InvokeArgs_52*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_53(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[53]; } _InvokeArgs_53;
  typedef gint64 (*_InvokeSymbol_53)(_InvokeArgs_53);
  return (_InvokeReturn)((_InvokeSymbol_53) address)(*((_InvokeArgs_53*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_54(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[54]; } _InvokeArgs_54;
  typedef gint64 (*_InvokeSymbol_54)(_InvokeArgs_54);
  return (_InvokeReturn)((_InvokeSymbol_54) address)(*((_InvokeArgs_54*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_55(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[55]; } _InvokeArgs_55;
  typedef gint64 (*_InvokeSymbol_55)(_InvokeArgs_55);
  return (_InvokeReturn)((_InvokeSymbol_55) address)(*((_InvokeArgs_55*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_56(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[56]; } _InvokeArgs_56;
  typedef gint64 (*_InvokeSymbol_56)(_InvokeArgs_56);
  return (_InvokeReturn)((_InvokeSymbol_56) address)(*((_InvokeArgs_56*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_57(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[57]; } _InvokeArgs_57;
  typedef gint64 (*_InvokeSymbol_57)(_InvokeArgs_57);
  return (_InvokeReturn)((_InvokeSymbol_57) address)(*((_InvokeArgs_57*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_58(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[58]; } _InvokeArgs_58;
  typedef gint64 (*_InvokeSymbol_58)(_InvokeArgs_58);
  return (_InvokeReturn)((_InvokeSymbol_58) address)(*((_InvokeArgs_58*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_59(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[59]; } _InvokeArgs_59;
  typedef gint64 (*_InvokeSymbol_59)(_InvokeArgs_59);
  return (_InvokeReturn)((_InvokeSymbol_59) address)(*((_InvokeArgs_59*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_60(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[60]; } _InvokeArgs_60;
  typedef gint64 (*_InvokeSymbol_60)(_InvokeArgs_60);
  return (_InvokeReturn)((_InvokeSymbol_60) address)(*((_InvokeArgs_60*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_61(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[61]; } _InvokeArgs_61;
  typedef gint64 (*_InvokeSymbol_61)(_InvokeArgs_61);
  return (_InvokeReturn)((_InvokeSymbol_61) address)(*((_InvokeArgs_61*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_62(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[62]; } _InvokeArgs_62;
  typedef gint64 (*_InvokeSymbol_62)(_InvokeArgs_62);
  return (_InvokeReturn)((_InvokeSymbol_62) address)(*((_InvokeArgs_62*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_63(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[63]; } _InvokeArgs_63;
  typedef gint64 (*_InvokeSymbol_63)(_InvokeArgs_63);
  return (_InvokeReturn)((_InvokeSymbol_63) address)(*((_InvokeArgs_63*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_64(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[64]; } _InvokeArgs_64;
  typedef gint64 (*_InvokeSymbol_64)(_InvokeArgs_64);
  return (_InvokeReturn)((_InvokeSymbol_64) address)(*((_InvokeArgs_64*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_65(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[65]; } _InvokeArgs_65;
  typedef gint64 (*_InvokeSymbol_65)(_InvokeArgs_65);
  return (_InvokeReturn)((_InvokeSymbol_65) address)(*((_InvokeArgs_65*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_66(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[66]; } _InvokeArgs_66;
  typedef gint64 (*_InvokeSymbol_66)(_InvokeArgs_66);
  return (_InvokeReturn)((_InvokeSymbol_66) address)(*((_InvokeArgs_66*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_67(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[67]; } _InvokeArgs_67;
  typedef gint64 (*_InvokeSymbol_67)(_InvokeArgs_67);
  return (_InvokeReturn)((_InvokeSymbol_67) address)(*((_InvokeArgs_67*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_68(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[68]; } _InvokeArgs_68;
  typedef gint64 (*_InvokeSymbol_68)(_InvokeArgs_68);
  return (_InvokeReturn)((_InvokeSymbol_68) address)(*((_InvokeArgs_68*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_69(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[69]; } _InvokeArgs_69;
  typedef gint64 (*_InvokeSymbol_69)(_InvokeArgs_69);
  return (_InvokeReturn)((_InvokeSymbol_69) address)(*((_InvokeArgs_69*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_70(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[70]; } _InvokeArgs_70;
  typedef gint64 (*_InvokeSymbol_70)(_InvokeArgs_70);
  return (_InvokeReturn)((_InvokeSymbol_70) address)(*((_InvokeArgs_70*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_71(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[71]; } _InvokeArgs_71;
  typedef gint64 (*_InvokeSymbol_71)(_InvokeArgs_71);
  return (_InvokeReturn)((_InvokeSymbol_71) address)(*((_InvokeArgs_71*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_72(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[72]; } _InvokeArgs_72;
  typedef gint64 (*_InvokeSymbol_72)(_InvokeArgs_72);
  return (_InvokeReturn)((_InvokeSymbol_72) address)(*((_InvokeArgs_72*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_73(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[73]; } _InvokeArgs_73;
  typedef gint64 (*_InvokeSymbol_73)(_InvokeArgs_73);
  return (_InvokeReturn)((_InvokeSymbol_73) address)(*((_InvokeArgs_73*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_74(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[74]; } _InvokeArgs_74;
  typedef gint64 (*_InvokeSymbol_74)(_InvokeArgs_74);
  return (_InvokeReturn)((_InvokeSymbol_74) address)(*((_InvokeArgs_74*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_75(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[75]; } _InvokeArgs_75;
  typedef gint64 (*_InvokeSymbol_75)(_InvokeArgs_75);
  return (_InvokeReturn)((_InvokeSymbol_75) address)(*((_InvokeArgs_75*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_76(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[76]; } _InvokeArgs_76;
  typedef gint64 (*_InvokeSymbol_76)(_InvokeArgs_76);
  return (_InvokeReturn)((_InvokeSymbol_76) address)(*((_InvokeArgs_76*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_77(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[77]; } _InvokeArgs_77;
  typedef gint64 (*_InvokeSymbol_77)(_InvokeArgs_77);
  return (_InvokeReturn)((_InvokeSymbol_77) address)(*((_InvokeArgs_77*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_78(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[78]; } _InvokeArgs_78;
  typedef gint64 (*_InvokeSymbol_78)(_InvokeArgs_78);
  return (_InvokeReturn)((_InvokeSymbol_78) address)(*((_InvokeArgs_78*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_79(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[79]; } _InvokeArgs_79;
  typedef gint64 (*_InvokeSymbol_79)(_InvokeArgs_79);
  return (_InvokeReturn)((_InvokeSymbol_79) address)(*((_InvokeArgs_79*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_80(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[80]; } _InvokeArgs_80;
  typedef gint64 (*_InvokeSymbol_80)(_InvokeArgs_80);
  return (_InvokeReturn)((_InvokeSymbol_80) address)(*((_InvokeArgs_80*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_81(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[81]; } _InvokeArgs_81;
  typedef gint64 (*_InvokeSymbol_81)(_InvokeArgs_81);
  return (_InvokeReturn)((_InvokeSymbol_81) address)(*((_InvokeArgs_81*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_82(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[82]; } _InvokeArgs_82;
  typedef gint64 (*_InvokeSymbol_82)(_InvokeArgs_82);
  return (_InvokeReturn)((_InvokeSymbol_82) address)(*((_InvokeArgs_82*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_83(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[83]; } _InvokeArgs_83;
  typedef gint64 (*_InvokeSymbol_83)(_InvokeArgs_83);
  return (_InvokeReturn)((_InvokeSymbol_83) address)(*((_InvokeArgs_83*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_84(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[84]; } _InvokeArgs_84;
  typedef gint64 (*_InvokeSymbol_84)(_InvokeArgs_84);
  return (_InvokeReturn)((_InvokeSymbol_84) address)(*((_InvokeArgs_84*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_85(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[85]; } _InvokeArgs_85;
  typedef gint64 (*_InvokeSymbol_85)(_InvokeArgs_85);
  return (_InvokeReturn)((_InvokeSymbol_85) address)(*((_InvokeArgs_85*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_86(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[86]; } _InvokeArgs_86;
  typedef gint64 (*_InvokeSymbol_86)(_InvokeArgs_86);
  return (_InvokeReturn)((_InvokeSymbol_86) address)(*((_InvokeArgs_86*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_87(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[87]; } _InvokeArgs_87;
  typedef gint64 (*_InvokeSymbol_87)(_InvokeArgs_87);
  return (_InvokeReturn)((_InvokeSymbol_87) address)(*((_InvokeArgs_87*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_88(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[88]; } _InvokeArgs_88;
  typedef gint64 (*_InvokeSymbol_88)(_InvokeArgs_88);
  return (_InvokeReturn)((_InvokeSymbol_88) address)(*((_InvokeArgs_88*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_89(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[89]; } _InvokeArgs_89;
  typedef gint64 (*_InvokeSymbol_89)(_InvokeArgs_89);
  return (_InvokeReturn)((_InvokeSymbol_89) address)(*((_InvokeArgs_89*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_90(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[90]; } _InvokeArgs_90;
  typedef gint64 (*_InvokeSymbol_90)(_InvokeArgs_90);
  return (_InvokeReturn)((_InvokeSymbol_90) address)(*((_InvokeArgs_90*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_91(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[91]; } _InvokeArgs_91;
  typedef gint64 (*_InvokeSymbol_91)(_InvokeArgs_91);
  return (_InvokeReturn)((_InvokeSymbol_91) address)(*((_InvokeArgs_91*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_92(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[92]; } _InvokeArgs_92;
  typedef gint64 (*_InvokeSymbol_92)(_InvokeArgs_92);
  return (_InvokeReturn)((_InvokeSymbol_92) address)(*((_InvokeArgs_92*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_93(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[93]; } _InvokeArgs_93;
  typedef gint64 (*_InvokeSymbol_93)(_InvokeArgs_93);
  return (_InvokeReturn)((_InvokeSymbol_93) address)(*((_InvokeArgs_93*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_94(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[94]; } _InvokeArgs_94;
  typedef gint64 (*_InvokeSymbol_94)(_InvokeArgs_94);
  return (_InvokeReturn)((_InvokeSymbol_94) address)(*((_InvokeArgs_94*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_95(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[95]; } _InvokeArgs_95;
  typedef gint64 (*_InvokeSymbol_95)(_InvokeArgs_95);
  return (_InvokeReturn)((_InvokeSymbol_95) address)(*((_InvokeArgs_95*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_96(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[96]; } _InvokeArgs_96;
  typedef gint64 (*_InvokeSymbol_96)(_InvokeArgs_96);
  return (_InvokeReturn)((_InvokeSymbol_96) address)(*((_InvokeArgs_96*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_97(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[97]; } _InvokeArgs_97;
  typedef gint64 (*_InvokeSymbol_97)(_InvokeArgs_97);
  return (_InvokeReturn)((_InvokeSymbol_97) address)(*((_InvokeArgs_97*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_98(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[98]; } _InvokeArgs_98;
  typedef gint64 (*_InvokeSymbol_98)(_InvokeArgs_98);
  return (_InvokeReturn)((_InvokeSymbol_98) address)(*((_InvokeArgs_98*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_99(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[99]; } _InvokeArgs_99;
  typedef gint64 (*_InvokeSymbol_99)(_InvokeArgs_99);
  return (_InvokeReturn)((_InvokeSymbol_99) address)(*((_InvokeArgs_99*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_100(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[100]; } _InvokeArgs_100;
  typedef gint64 (*_InvokeSymbol_100)(_InvokeArgs_100);
  return (_InvokeReturn)((_InvokeSymbol_100) address)(*((_InvokeArgs_100*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_101(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[101]; } _InvokeArgs_101;
  typedef gint64 (*_InvokeSymbol_101)(_InvokeArgs_101);
  return (_InvokeReturn)((_InvokeSymbol_101) address)(*((_InvokeArgs_101*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_102(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[102]; } _InvokeArgs_102;
  typedef gint64 (*_InvokeSymbol_102)(_InvokeArgs_102);
  return (_InvokeReturn)((_InvokeSymbol_102) address)(*((_InvokeArgs_102*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_103(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[103]; } _InvokeArgs_103;
  typedef gint64 (*_InvokeSymbol_103)(_InvokeArgs_103);
  return (_InvokeReturn)((_InvokeSymbol_103) address)(*((_InvokeArgs_103*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_104(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[104]; } _InvokeArgs_104;
  typedef gint64 (*_InvokeSymbol_104)(_InvokeArgs_104);
  return (_InvokeReturn)((_InvokeSymbol_104) address)(*((_InvokeArgs_104*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_105(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[105]; } _InvokeArgs_105;
  typedef gint64 (*_InvokeSymbol_105)(_InvokeArgs_105);
  return (_InvokeReturn)((_InvokeSymbol_105) address)(*((_InvokeArgs_105*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_106(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[106]; } _InvokeArgs_106;
  typedef gint64 (*_InvokeSymbol_106)(_InvokeArgs_106);
  return (_InvokeReturn)((_InvokeSymbol_106) address)(*((_InvokeArgs_106*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_107(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[107]; } _InvokeArgs_107;
  typedef gint64 (*_InvokeSymbol_107)(_InvokeArgs_107);
  return (_InvokeReturn)((_InvokeSymbol_107) address)(*((_InvokeArgs_107*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_108(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[108]; } _InvokeArgs_108;
  typedef gint64 (*_InvokeSymbol_108)(_InvokeArgs_108);
  return (_InvokeReturn)((_InvokeSymbol_108) address)(*((_InvokeArgs_108*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_109(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[109]; } _InvokeArgs_109;
  typedef gint64 (*_InvokeSymbol_109)(_InvokeArgs_109);
  return (_InvokeReturn)((_InvokeSymbol_109) address)(*((_InvokeArgs_109*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_110(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[110]; } _InvokeArgs_110;
  typedef gint64 (*_InvokeSymbol_110)(_InvokeArgs_110);
  return (_InvokeReturn)((_InvokeSymbol_110) address)(*((_InvokeArgs_110*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_111(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[111]; } _InvokeArgs_111;
  typedef gint64 (*_InvokeSymbol_111)(_InvokeArgs_111);
  return (_InvokeReturn)((_InvokeSymbol_111) address)(*((_InvokeArgs_111*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_112(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[112]; } _InvokeArgs_112;
  typedef gint64 (*_InvokeSymbol_112)(_InvokeArgs_112);
  return (_InvokeReturn)((_InvokeSymbol_112) address)(*((_InvokeArgs_112*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_113(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[113]; } _InvokeArgs_113;
  typedef gint64 (*_InvokeSymbol_113)(_InvokeArgs_113);
  return (_InvokeReturn)((_InvokeSymbol_113) address)(*((_InvokeArgs_113*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_114(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[114]; } _InvokeArgs_114;
  typedef gint64 (*_InvokeSymbol_114)(_InvokeArgs_114);
  return (_InvokeReturn)((_InvokeSymbol_114) address)(*((_InvokeArgs_114*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_115(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[115]; } _InvokeArgs_115;
  typedef gint64 (*_InvokeSymbol_115)(_InvokeArgs_115);
  return (_InvokeReturn)((_InvokeSymbol_115) address)(*((_InvokeArgs_115*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_116(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[116]; } _InvokeArgs_116;
  typedef gint64 (*_InvokeSymbol_116)(_InvokeArgs_116);
  return (_InvokeReturn)((_InvokeSymbol_116) address)(*((_InvokeArgs_116*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_117(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[117]; } _InvokeArgs_117;
  typedef gint64 (*_InvokeSymbol_117)(_InvokeArgs_117);
  return (_InvokeReturn)((_InvokeSymbol_117) address)(*((_InvokeArgs_117*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_118(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[118]; } _InvokeArgs_118;
  typedef gint64 (*_InvokeSymbol_118)(_InvokeArgs_118);
  return (_InvokeReturn)((_InvokeSymbol_118) address)(*((_InvokeArgs_118*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_119(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[119]; } _InvokeArgs_119;
  typedef gint64 (*_InvokeSymbol_119)(_InvokeArgs_119);
  return (_InvokeReturn)((_InvokeSymbol_119) address)(*((_InvokeArgs_119*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_120(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[120]; } _InvokeArgs_120;
  typedef gint64 (*_InvokeSymbol_120)(_InvokeArgs_120);
  return (_InvokeReturn)((_InvokeSymbol_120) address)(*((_InvokeArgs_120*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_121(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[121]; } _InvokeArgs_121;
  typedef gint64 (*_InvokeSymbol_121)(_InvokeArgs_121);
  return (_InvokeReturn)((_InvokeSymbol_121) address)(*((_InvokeArgs_121*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_122(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[122]; } _InvokeArgs_122;
  typedef gint64 (*_InvokeSymbol_122)(_InvokeArgs_122);
  return (_InvokeReturn)((_InvokeSymbol_122) address)(*((_InvokeArgs_122*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_123(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[123]; } _InvokeArgs_123;
  typedef gint64 (*_InvokeSymbol_123)(_InvokeArgs_123);
  return (_InvokeReturn)((_InvokeSymbol_123) address)(*((_InvokeArgs_123*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_124(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[124]; } _InvokeArgs_124;
  typedef gint64 (*_InvokeSymbol_124)(_InvokeArgs_124);
  return (_InvokeReturn)((_InvokeSymbol_124) address)(*((_InvokeArgs_124*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_125(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[125]; } _InvokeArgs_125;
  typedef gint64 (*_InvokeSymbol_125)(_InvokeArgs_125);
  return (_InvokeReturn)((_InvokeSymbol_125) address)(*((_InvokeArgs_125*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_126(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[126]; } _InvokeArgs_126;
  typedef gint64 (*_InvokeSymbol_126)(_InvokeArgs_126);
  return (_InvokeReturn)((_InvokeSymbol_126) address)(*((_InvokeArgs_126*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_127(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[127]; } _InvokeArgs_127;
  typedef gint64 (*_InvokeSymbol_127)(_InvokeArgs_127);
  return (_InvokeReturn)((_InvokeSymbol_127) address)(*((_InvokeArgs_127*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_128(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[128]; } _InvokeArgs_128;
  typedef gint64 (*_InvokeSymbol_128)(_InvokeArgs_128);
  return (_InvokeReturn)((_InvokeSymbol_128) address)(*((_InvokeArgs_128*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_129(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[129]; } _InvokeArgs_129;
  typedef gint64 (*_InvokeSymbol_129)(_InvokeArgs_129);
  return (_InvokeReturn)((_InvokeSymbol_129) address)(*((_InvokeArgs_129*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_130(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[130]; } _InvokeArgs_130;
  typedef gint64 (*_InvokeSymbol_130)(_InvokeArgs_130);
  return (_InvokeReturn)((_InvokeSymbol_130) address)(*((_InvokeArgs_130*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_131(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[131]; } _InvokeArgs_131;
  typedef gint64 (*_InvokeSymbol_131)(_InvokeArgs_131);
  return (_InvokeReturn)((_InvokeSymbol_131) address)(*((_InvokeArgs_131*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_132(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[132]; } _InvokeArgs_132;
  typedef gint64 (*_InvokeSymbol_132)(_InvokeArgs_132);
  return (_InvokeReturn)((_InvokeSymbol_132) address)(*((_InvokeArgs_132*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_133(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[133]; } _InvokeArgs_133;
  typedef gint64 (*_InvokeSymbol_133)(_InvokeArgs_133);
  return (_InvokeReturn)((_InvokeSymbol_133) address)(*((_InvokeArgs_133*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_134(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[134]; } _InvokeArgs_134;
  typedef gint64 (*_InvokeSymbol_134)(_InvokeArgs_134);
  return (_InvokeReturn)((_InvokeSymbol_134) address)(*((_InvokeArgs_134*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_135(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[135]; } _InvokeArgs_135;
  typedef gint64 (*_InvokeSymbol_135)(_InvokeArgs_135);
  return (_InvokeReturn)((_InvokeSymbol_135) address)(*((_InvokeArgs_135*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_136(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[136]; } _InvokeArgs_136;
  typedef gint64 (*_InvokeSymbol_136)(_InvokeArgs_136);
  return (_InvokeReturn)((_InvokeSymbol_136) address)(*((_InvokeArgs_136*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_137(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[137]; } _InvokeArgs_137;
  typedef gint64 (*_InvokeSymbol_137)(_InvokeArgs_137);
  return (_InvokeReturn)((_InvokeSymbol_137) address)(*((_InvokeArgs_137*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_138(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[138]; } _InvokeArgs_138;
  typedef gint64 (*_InvokeSymbol_138)(_InvokeArgs_138);
  return (_InvokeReturn)((_InvokeSymbol_138) address)(*((_InvokeArgs_138*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_139(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[139]; } _InvokeArgs_139;
  typedef gint64 (*_InvokeSymbol_139)(_InvokeArgs_139);
  return (_InvokeReturn)((_InvokeSymbol_139) address)(*((_InvokeArgs_139*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_140(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[140]; } _InvokeArgs_140;
  typedef gint64 (*_InvokeSymbol_140)(_InvokeArgs_140);
  return (_InvokeReturn)((_InvokeSymbol_140) address)(*((_InvokeArgs_140*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_141(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[141]; } _InvokeArgs_141;
  typedef gint64 (*_InvokeSymbol_141)(_InvokeArgs_141);
  return (_InvokeReturn)((_InvokeSymbol_141) address)(*((_InvokeArgs_141*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_142(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[142]; } _InvokeArgs_142;
  typedef gint64 (*_InvokeSymbol_142)(_InvokeArgs_142);
  return (_InvokeReturn)((_InvokeSymbol_142) address)(*((_InvokeArgs_142*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_143(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[143]; } _InvokeArgs_143;
  typedef gint64 (*_InvokeSymbol_143)(_InvokeArgs_143);
  return (_InvokeReturn)((_InvokeSymbol_143) address)(*((_InvokeArgs_143*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_144(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[144]; } _InvokeArgs_144;
  typedef gint64 (*_InvokeSymbol_144)(_InvokeArgs_144);
  return (_InvokeReturn)((_InvokeSymbol_144) address)(*((_InvokeArgs_144*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_145(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[145]; } _InvokeArgs_145;
  typedef gint64 (*_InvokeSymbol_145)(_InvokeArgs_145);
  return (_InvokeReturn)((_InvokeSymbol_145) address)(*((_InvokeArgs_145*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_146(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[146]; } _InvokeArgs_146;
  typedef gint64 (*_InvokeSymbol_146)(_InvokeArgs_146);
  return (_InvokeReturn)((_InvokeSymbol_146) address)(*((_InvokeArgs_146*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_147(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[147]; } _InvokeArgs_147;
  typedef gint64 (*_InvokeSymbol_147)(_InvokeArgs_147);
  return (_InvokeReturn)((_InvokeSymbol_147) address)(*((_InvokeArgs_147*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_148(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[148]; } _InvokeArgs_148;
  typedef gint64 (*_InvokeSymbol_148)(_InvokeArgs_148);
  return (_InvokeReturn)((_InvokeSymbol_148) address)(*((_InvokeArgs_148*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_149(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[149]; } _InvokeArgs_149;
  typedef gint64 (*_InvokeSymbol_149)(_InvokeArgs_149);
  return (_InvokeReturn)((_InvokeSymbol_149) address)(*((_InvokeArgs_149*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_150(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[150]; } _InvokeArgs_150;
  typedef gint64 (*_InvokeSymbol_150)(_InvokeArgs_150);
  return (_InvokeReturn)((_InvokeSymbol_150) address)(*((_InvokeArgs_150*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_151(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[151]; } _InvokeArgs_151;
  typedef gint64 (*_InvokeSymbol_151)(_InvokeArgs_151);
  return (_InvokeReturn)((_InvokeSymbol_151) address)(*((_InvokeArgs_151*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_152(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[152]; } _InvokeArgs_152;
  typedef gint64 (*_InvokeSymbol_152)(_InvokeArgs_152);
  return (_InvokeReturn)((_InvokeSymbol_152) address)(*((_InvokeArgs_152*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_153(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[153]; } _InvokeArgs_153;
  typedef gint64 (*_InvokeSymbol_153)(_InvokeArgs_153);
  return (_InvokeReturn)((_InvokeSymbol_153) address)(*((_InvokeArgs_153*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_154(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[154]; } _InvokeArgs_154;
  typedef gint64 (*_InvokeSymbol_154)(_InvokeArgs_154);
  return (_InvokeReturn)((_InvokeSymbol_154) address)(*((_InvokeArgs_154*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_155(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[155]; } _InvokeArgs_155;
  typedef gint64 (*_InvokeSymbol_155)(_InvokeArgs_155);
  return (_InvokeReturn)((_InvokeSymbol_155) address)(*((_InvokeArgs_155*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_156(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[156]; } _InvokeArgs_156;
  typedef gint64 (*_InvokeSymbol_156)(_InvokeArgs_156);
  return (_InvokeReturn)((_InvokeSymbol_156) address)(*((_InvokeArgs_156*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_157(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[157]; } _InvokeArgs_157;
  typedef gint64 (*_InvokeSymbol_157)(_InvokeArgs_157);
  return (_InvokeReturn)((_InvokeSymbol_157) address)(*((_InvokeArgs_157*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_158(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[158]; } _InvokeArgs_158;
  typedef gint64 (*_InvokeSymbol_158)(_InvokeArgs_158);
  return (_InvokeReturn)((_InvokeSymbol_158) address)(*((_InvokeArgs_158*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_159(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[159]; } _InvokeArgs_159;
  typedef gint64 (*_InvokeSymbol_159)(_InvokeArgs_159);
  return (_InvokeReturn)((_InvokeSymbol_159) address)(*((_InvokeArgs_159*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_160(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[160]; } _InvokeArgs_160;
  typedef gint64 (*_InvokeSymbol_160)(_InvokeArgs_160);
  return (_InvokeReturn)((_InvokeSymbol_160) address)(*((_InvokeArgs_160*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_161(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[161]; } _InvokeArgs_161;
  typedef gint64 (*_InvokeSymbol_161)(_InvokeArgs_161);
  return (_InvokeReturn)((_InvokeSymbol_161) address)(*((_InvokeArgs_161*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_162(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[162]; } _InvokeArgs_162;
  typedef gint64 (*_InvokeSymbol_162)(_InvokeArgs_162);
  return (_InvokeReturn)((_InvokeSymbol_162) address)(*((_InvokeArgs_162*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_163(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[163]; } _InvokeArgs_163;
  typedef gint64 (*_InvokeSymbol_163)(_InvokeArgs_163);
  return (_InvokeReturn)((_InvokeSymbol_163) address)(*((_InvokeArgs_163*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_164(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[164]; } _InvokeArgs_164;
  typedef gint64 (*_InvokeSymbol_164)(_InvokeArgs_164);
  return (_InvokeReturn)((_InvokeSymbol_164) address)(*((_InvokeArgs_164*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_165(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[165]; } _InvokeArgs_165;
  typedef gint64 (*_InvokeSymbol_165)(_InvokeArgs_165);
  return (_InvokeReturn)((_InvokeSymbol_165) address)(*((_InvokeArgs_165*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_166(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[166]; } _InvokeArgs_166;
  typedef gint64 (*_InvokeSymbol_166)(_InvokeArgs_166);
  return (_InvokeReturn)((_InvokeSymbol_166) address)(*((_InvokeArgs_166*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_167(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[167]; } _InvokeArgs_167;
  typedef gint64 (*_InvokeSymbol_167)(_InvokeArgs_167);
  return (_InvokeReturn)((_InvokeSymbol_167) address)(*((_InvokeArgs_167*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_168(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[168]; } _InvokeArgs_168;
  typedef gint64 (*_InvokeSymbol_168)(_InvokeArgs_168);
  return (_InvokeReturn)((_InvokeSymbol_168) address)(*((_InvokeArgs_168*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_169(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[169]; } _InvokeArgs_169;
  typedef gint64 (*_InvokeSymbol_169)(_InvokeArgs_169);
  return (_InvokeReturn)((_InvokeSymbol_169) address)(*((_InvokeArgs_169*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_170(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[170]; } _InvokeArgs_170;
  typedef gint64 (*_InvokeSymbol_170)(_InvokeArgs_170);
  return (_InvokeReturn)((_InvokeSymbol_170) address)(*((_InvokeArgs_170*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_171(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[171]; } _InvokeArgs_171;
  typedef gint64 (*_InvokeSymbol_171)(_InvokeArgs_171);
  return (_InvokeReturn)((_InvokeSymbol_171) address)(*((_InvokeArgs_171*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_172(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[172]; } _InvokeArgs_172;
  typedef gint64 (*_InvokeSymbol_172)(_InvokeArgs_172);
  return (_InvokeReturn)((_InvokeSymbol_172) address)(*((_InvokeArgs_172*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_173(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[173]; } _InvokeArgs_173;
  typedef gint64 (*_InvokeSymbol_173)(_InvokeArgs_173);
  return (_InvokeReturn)((_InvokeSymbol_173) address)(*((_InvokeArgs_173*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_174(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[174]; } _InvokeArgs_174;
  typedef gint64 (*_InvokeSymbol_174)(_InvokeArgs_174);
  return (_InvokeReturn)((_InvokeSymbol_174) address)(*((_InvokeArgs_174*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_175(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[175]; } _InvokeArgs_175;
  typedef gint64 (*_InvokeSymbol_175)(_InvokeArgs_175);
  return (_InvokeReturn)((_InvokeSymbol_175) address)(*((_InvokeArgs_175*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_176(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[176]; } _InvokeArgs_176;
  typedef gint64 (*_InvokeSymbol_176)(_InvokeArgs_176);
  return (_InvokeReturn)((_InvokeSymbol_176) address)(*((_InvokeArgs_176*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_177(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[177]; } _InvokeArgs_177;
  typedef gint64 (*_InvokeSymbol_177)(_InvokeArgs_177);
  return (_InvokeReturn)((_InvokeSymbol_177) address)(*((_InvokeArgs_177*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_178(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[178]; } _InvokeArgs_178;
  typedef gint64 (*_InvokeSymbol_178)(_InvokeArgs_178);
  return (_InvokeReturn)((_InvokeSymbol_178) address)(*((_InvokeArgs_178*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_179(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[179]; } _InvokeArgs_179;
  typedef gint64 (*_InvokeSymbol_179)(_InvokeArgs_179);
  return (_InvokeReturn)((_InvokeSymbol_179) address)(*((_InvokeArgs_179*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_180(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[180]; } _InvokeArgs_180;
  typedef gint64 (*_InvokeSymbol_180)(_InvokeArgs_180);
  return (_InvokeReturn)((_InvokeSymbol_180) address)(*((_InvokeArgs_180*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_181(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[181]; } _InvokeArgs_181;
  typedef gint64 (*_InvokeSymbol_181)(_InvokeArgs_181);
  return (_InvokeReturn)((_InvokeSymbol_181) address)(*((_InvokeArgs_181*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_182(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[182]; } _InvokeArgs_182;
  typedef gint64 (*_InvokeSymbol_182)(_InvokeArgs_182);
  return (_InvokeReturn)((_InvokeSymbol_182) address)(*((_InvokeArgs_182*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_183(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[183]; } _InvokeArgs_183;
  typedef gint64 (*_InvokeSymbol_183)(_InvokeArgs_183);
  return (_InvokeReturn)((_InvokeSymbol_183) address)(*((_InvokeArgs_183*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_184(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[184]; } _InvokeArgs_184;
  typedef gint64 (*_InvokeSymbol_184)(_InvokeArgs_184);
  return (_InvokeReturn)((_InvokeSymbol_184) address)(*((_InvokeArgs_184*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_185(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[185]; } _InvokeArgs_185;
  typedef gint64 (*_InvokeSymbol_185)(_InvokeArgs_185);
  return (_InvokeReturn)((_InvokeSymbol_185) address)(*((_InvokeArgs_185*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_186(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[186]; } _InvokeArgs_186;
  typedef gint64 (*_InvokeSymbol_186)(_InvokeArgs_186);
  return (_InvokeReturn)((_InvokeSymbol_186) address)(*((_InvokeArgs_186*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_187(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[187]; } _InvokeArgs_187;
  typedef gint64 (*_InvokeSymbol_187)(_InvokeArgs_187);
  return (_InvokeReturn)((_InvokeSymbol_187) address)(*((_InvokeArgs_187*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_188(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[188]; } _InvokeArgs_188;
  typedef gint64 (*_InvokeSymbol_188)(_InvokeArgs_188);
  return (_InvokeReturn)((_InvokeSymbol_188) address)(*((_InvokeArgs_188*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_189(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[189]; } _InvokeArgs_189;
  typedef gint64 (*_InvokeSymbol_189)(_InvokeArgs_189);
  return (_InvokeReturn)((_InvokeSymbol_189) address)(*((_InvokeArgs_189*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_190(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[190]; } _InvokeArgs_190;
  typedef gint64 (*_InvokeSymbol_190)(_InvokeArgs_190);
  return (_InvokeReturn)((_InvokeSymbol_190) address)(*((_InvokeArgs_190*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_191(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[191]; } _InvokeArgs_191;
  typedef gint64 (*_InvokeSymbol_191)(_InvokeArgs_191);
  return (_InvokeReturn)((_InvokeSymbol_191) address)(*((_InvokeArgs_191*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_192(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[192]; } _InvokeArgs_192;
  typedef gint64 (*_InvokeSymbol_192)(_InvokeArgs_192);
  return (_InvokeReturn)((_InvokeSymbol_192) address)(*((_InvokeArgs_192*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_193(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[193]; } _InvokeArgs_193;
  typedef gint64 (*_InvokeSymbol_193)(_InvokeArgs_193);
  return (_InvokeReturn)((_InvokeSymbol_193) address)(*((_InvokeArgs_193*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_194(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[194]; } _InvokeArgs_194;
  typedef gint64 (*_InvokeSymbol_194)(_InvokeArgs_194);
  return (_InvokeReturn)((_InvokeSymbol_194) address)(*((_InvokeArgs_194*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_195(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[195]; } _InvokeArgs_195;
  typedef gint64 (*_InvokeSymbol_195)(_InvokeArgs_195);
  return (_InvokeReturn)((_InvokeSymbol_195) address)(*((_InvokeArgs_195*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_196(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[196]; } _InvokeArgs_196;
  typedef gint64 (*_InvokeSymbol_196)(_InvokeArgs_196);
  return (_InvokeReturn)((_InvokeSymbol_196) address)(*((_InvokeArgs_196*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_197(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[197]; } _InvokeArgs_197;
  typedef gint64 (*_InvokeSymbol_197)(_InvokeArgs_197);
  return (_InvokeReturn)((_InvokeSymbol_197) address)(*((_InvokeArgs_197*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_198(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[198]; } _InvokeArgs_198;
  typedef gint64 (*_InvokeSymbol_198)(_InvokeArgs_198);
  return (_InvokeReturn)((_InvokeSymbol_198) address)(*((_InvokeArgs_198*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_199(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[199]; } _InvokeArgs_199;
  typedef gint64 (*_InvokeSymbol_199)(_InvokeArgs_199);
  return (_InvokeReturn)((_InvokeSymbol_199) address)(*((_InvokeArgs_199*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_200(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[200]; } _InvokeArgs_200;
  typedef gint64 (*_InvokeSymbol_200)(_InvokeArgs_200);
  return (_InvokeReturn)((_InvokeSymbol_200) address)(*((_InvokeArgs_200*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_201(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[201]; } _InvokeArgs_201;
  typedef gint64 (*_InvokeSymbol_201)(_InvokeArgs_201);
  return (_InvokeReturn)((_InvokeSymbol_201) address)(*((_InvokeArgs_201*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_202(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[202]; } _InvokeArgs_202;
  typedef gint64 (*_InvokeSymbol_202)(_InvokeArgs_202);
  return (_InvokeReturn)((_InvokeSymbol_202) address)(*((_InvokeArgs_202*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_203(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[203]; } _InvokeArgs_203;
  typedef gint64 (*_InvokeSymbol_203)(_InvokeArgs_203);
  return (_InvokeReturn)((_InvokeSymbol_203) address)(*((_InvokeArgs_203*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_204(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[204]; } _InvokeArgs_204;
  typedef gint64 (*_InvokeSymbol_204)(_InvokeArgs_204);
  return (_InvokeReturn)((_InvokeSymbol_204) address)(*((_InvokeArgs_204*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_205(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[205]; } _InvokeArgs_205;
  typedef gint64 (*_InvokeSymbol_205)(_InvokeArgs_205);
  return (_InvokeReturn)((_InvokeSymbol_205) address)(*((_InvokeArgs_205*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_206(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[206]; } _InvokeArgs_206;
  typedef gint64 (*_InvokeSymbol_206)(_InvokeArgs_206);
  return (_InvokeReturn)((_InvokeSymbol_206) address)(*((_InvokeArgs_206*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_207(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[207]; } _InvokeArgs_207;
  typedef gint64 (*_InvokeSymbol_207)(_InvokeArgs_207);
  return (_InvokeReturn)((_InvokeSymbol_207) address)(*((_InvokeArgs_207*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_208(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[208]; } _InvokeArgs_208;
  typedef gint64 (*_InvokeSymbol_208)(_InvokeArgs_208);
  return (_InvokeReturn)((_InvokeSymbol_208) address)(*((_InvokeArgs_208*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_209(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[209]; } _InvokeArgs_209;
  typedef gint64 (*_InvokeSymbol_209)(_InvokeArgs_209);
  return (_InvokeReturn)((_InvokeSymbol_209) address)(*((_InvokeArgs_209*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_210(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[210]; } _InvokeArgs_210;
  typedef gint64 (*_InvokeSymbol_210)(_InvokeArgs_210);
  return (_InvokeReturn)((_InvokeSymbol_210) address)(*((_InvokeArgs_210*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_211(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[211]; } _InvokeArgs_211;
  typedef gint64 (*_InvokeSymbol_211)(_InvokeArgs_211);
  return (_InvokeReturn)((_InvokeSymbol_211) address)(*((_InvokeArgs_211*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_212(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[212]; } _InvokeArgs_212;
  typedef gint64 (*_InvokeSymbol_212)(_InvokeArgs_212);
  return (_InvokeReturn)((_InvokeSymbol_212) address)(*((_InvokeArgs_212*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_213(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[213]; } _InvokeArgs_213;
  typedef gint64 (*_InvokeSymbol_213)(_InvokeArgs_213);
  return (_InvokeReturn)((_InvokeSymbol_213) address)(*((_InvokeArgs_213*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_214(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[214]; } _InvokeArgs_214;
  typedef gint64 (*_InvokeSymbol_214)(_InvokeArgs_214);
  return (_InvokeReturn)((_InvokeSymbol_214) address)(*((_InvokeArgs_214*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_215(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[215]; } _InvokeArgs_215;
  typedef gint64 (*_InvokeSymbol_215)(_InvokeArgs_215);
  return (_InvokeReturn)((_InvokeSymbol_215) address)(*((_InvokeArgs_215*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_216(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[216]; } _InvokeArgs_216;
  typedef gint64 (*_InvokeSymbol_216)(_InvokeArgs_216);
  return (_InvokeReturn)((_InvokeSymbol_216) address)(*((_InvokeArgs_216*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_217(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[217]; } _InvokeArgs_217;
  typedef gint64 (*_InvokeSymbol_217)(_InvokeArgs_217);
  return (_InvokeReturn)((_InvokeSymbol_217) address)(*((_InvokeArgs_217*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_218(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[218]; } _InvokeArgs_218;
  typedef gint64 (*_InvokeSymbol_218)(_InvokeArgs_218);
  return (_InvokeReturn)((_InvokeSymbol_218) address)(*((_InvokeArgs_218*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_219(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[219]; } _InvokeArgs_219;
  typedef gint64 (*_InvokeSymbol_219)(_InvokeArgs_219);
  return (_InvokeReturn)((_InvokeSymbol_219) address)(*((_InvokeArgs_219*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_220(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[220]; } _InvokeArgs_220;
  typedef gint64 (*_InvokeSymbol_220)(_InvokeArgs_220);
  return (_InvokeReturn)((_InvokeSymbol_220) address)(*((_InvokeArgs_220*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_221(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[221]; } _InvokeArgs_221;
  typedef gint64 (*_InvokeSymbol_221)(_InvokeArgs_221);
  return (_InvokeReturn)((_InvokeSymbol_221) address)(*((_InvokeArgs_221*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_222(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[222]; } _InvokeArgs_222;
  typedef gint64 (*_InvokeSymbol_222)(_InvokeArgs_222);
  return (_InvokeReturn)((_InvokeSymbol_222) address)(*((_InvokeArgs_222*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_223(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[223]; } _InvokeArgs_223;
  typedef gint64 (*_InvokeSymbol_223)(_InvokeArgs_223);
  return (_InvokeReturn)((_InvokeSymbol_223) address)(*((_InvokeArgs_223*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_224(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[224]; } _InvokeArgs_224;
  typedef gint64 (*_InvokeSymbol_224)(_InvokeArgs_224);
  return (_InvokeReturn)((_InvokeSymbol_224) address)(*((_InvokeArgs_224*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_225(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[225]; } _InvokeArgs_225;
  typedef gint64 (*_InvokeSymbol_225)(_InvokeArgs_225);
  return (_InvokeReturn)((_InvokeSymbol_225) address)(*((_InvokeArgs_225*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_226(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[226]; } _InvokeArgs_226;
  typedef gint64 (*_InvokeSymbol_226)(_InvokeArgs_226);
  return (_InvokeReturn)((_InvokeSymbol_226) address)(*((_InvokeArgs_226*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_227(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[227]; } _InvokeArgs_227;
  typedef gint64 (*_InvokeSymbol_227)(_InvokeArgs_227);
  return (_InvokeReturn)((_InvokeSymbol_227) address)(*((_InvokeArgs_227*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_228(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[228]; } _InvokeArgs_228;
  typedef gint64 (*_InvokeSymbol_228)(_InvokeArgs_228);
  return (_InvokeReturn)((_InvokeSymbol_228) address)(*((_InvokeArgs_228*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_229(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[229]; } _InvokeArgs_229;
  typedef gint64 (*_InvokeSymbol_229)(_InvokeArgs_229);
  return (_InvokeReturn)((_InvokeSymbol_229) address)(*((_InvokeArgs_229*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_230(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[230]; } _InvokeArgs_230;
  typedef gint64 (*_InvokeSymbol_230)(_InvokeArgs_230);
  return (_InvokeReturn)((_InvokeSymbol_230) address)(*((_InvokeArgs_230*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_231(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[231]; } _InvokeArgs_231;
  typedef gint64 (*_InvokeSymbol_231)(_InvokeArgs_231);
  return (_InvokeReturn)((_InvokeSymbol_231) address)(*((_InvokeArgs_231*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_232(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[232]; } _InvokeArgs_232;
  typedef gint64 (*_InvokeSymbol_232)(_InvokeArgs_232);
  return (_InvokeReturn)((_InvokeSymbol_232) address)(*((_InvokeArgs_232*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_233(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[233]; } _InvokeArgs_233;
  typedef gint64 (*_InvokeSymbol_233)(_InvokeArgs_233);
  return (_InvokeReturn)((_InvokeSymbol_233) address)(*((_InvokeArgs_233*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_234(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[234]; } _InvokeArgs_234;
  typedef gint64 (*_InvokeSymbol_234)(_InvokeArgs_234);
  return (_InvokeReturn)((_InvokeSymbol_234) address)(*((_InvokeArgs_234*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_235(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[235]; } _InvokeArgs_235;
  typedef gint64 (*_InvokeSymbol_235)(_InvokeArgs_235);
  return (_InvokeReturn)((_InvokeSymbol_235) address)(*((_InvokeArgs_235*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_236(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[236]; } _InvokeArgs_236;
  typedef gint64 (*_InvokeSymbol_236)(_InvokeArgs_236);
  return (_InvokeReturn)((_InvokeSymbol_236) address)(*((_InvokeArgs_236*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_237(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[237]; } _InvokeArgs_237;
  typedef gint64 (*_InvokeSymbol_237)(_InvokeArgs_237);
  return (_InvokeReturn)((_InvokeSymbol_237) address)(*((_InvokeArgs_237*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_238(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[238]; } _InvokeArgs_238;
  typedef gint64 (*_InvokeSymbol_238)(_InvokeArgs_238);
  return (_InvokeReturn)((_InvokeSymbol_238) address)(*((_InvokeArgs_238*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_239(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[239]; } _InvokeArgs_239;
  typedef gint64 (*_InvokeSymbol_239)(_InvokeArgs_239);
  return (_InvokeReturn)((_InvokeSymbol_239) address)(*((_InvokeArgs_239*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_240(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[240]; } _InvokeArgs_240;
  typedef gint64 (*_InvokeSymbol_240)(_InvokeArgs_240);
  return (_InvokeReturn)((_InvokeSymbol_240) address)(*((_InvokeArgs_240*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_241(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[241]; } _InvokeArgs_241;
  typedef gint64 (*_InvokeSymbol_241)(_InvokeArgs_241);
  return (_InvokeReturn)((_InvokeSymbol_241) address)(*((_InvokeArgs_241*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_242(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[242]; } _InvokeArgs_242;
  typedef gint64 (*_InvokeSymbol_242)(_InvokeArgs_242);
  return (_InvokeReturn)((_InvokeSymbol_242) address)(*((_InvokeArgs_242*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_243(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[243]; } _InvokeArgs_243;
  typedef gint64 (*_InvokeSymbol_243)(_InvokeArgs_243);
  return (_InvokeReturn)((_InvokeSymbol_243) address)(*((_InvokeArgs_243*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_244(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[244]; } _InvokeArgs_244;
  typedef gint64 (*_InvokeSymbol_244)(_InvokeArgs_244);
  return (_InvokeReturn)((_InvokeSymbol_244) address)(*((_InvokeArgs_244*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_245(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[245]; } _InvokeArgs_245;
  typedef gint64 (*_InvokeSymbol_245)(_InvokeArgs_245);
  return (_InvokeReturn)((_InvokeSymbol_245) address)(*((_InvokeArgs_245*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_246(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[246]; } _InvokeArgs_246;
  typedef gint64 (*_InvokeSymbol_246)(_InvokeArgs_246);
  return (_InvokeReturn)((_InvokeSymbol_246) address)(*((_InvokeArgs_246*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_247(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[247]; } _InvokeArgs_247;
  typedef gint64 (*_InvokeSymbol_247)(_InvokeArgs_247);
  return (_InvokeReturn)((_InvokeSymbol_247) address)(*((_InvokeArgs_247*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_248(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[248]; } _InvokeArgs_248;
  typedef gint64 (*_InvokeSymbol_248)(_InvokeArgs_248);
  return (_InvokeReturn)((_InvokeSymbol_248) address)(*((_InvokeArgs_248*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_249(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[249]; } _InvokeArgs_249;
  typedef gint64 (*_InvokeSymbol_249)(_InvokeArgs_249);
  return (_InvokeReturn)((_InvokeSymbol_249) address)(*((_InvokeArgs_249*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_250(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[250]; } _InvokeArgs_250;
  typedef gint64 (*_InvokeSymbol_250)(_InvokeArgs_250);
  return (_InvokeReturn)((_InvokeSymbol_250) address)(*((_InvokeArgs_250*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_251(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[251]; } _InvokeArgs_251;
  typedef gint64 (*_InvokeSymbol_251)(_InvokeArgs_251);
  return (_InvokeReturn)((_InvokeSymbol_251) address)(*((_InvokeArgs_251*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_252(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[252]; } _InvokeArgs_252;
  typedef gint64 (*_InvokeSymbol_252)(_InvokeArgs_252);
  return (_InvokeReturn)((_InvokeSymbol_252) address)(*((_InvokeArgs_252*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_253(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[253]; } _InvokeArgs_253;
  typedef gint64 (*_InvokeSymbol_253)(_InvokeArgs_253);
  return (_InvokeReturn)((_InvokeSymbol_253) address)(*((_InvokeArgs_253*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_254(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[254]; } _InvokeArgs_254;
  typedef gint64 (*_InvokeSymbol_254)(_InvokeArgs_254);
  return (_InvokeReturn)((_InvokeSymbol_254) address)(*((_InvokeArgs_254*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_255(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[255]; } _InvokeArgs_255;
  typedef gint64 (*_InvokeSymbol_255)(_InvokeArgs_255);
  return (_InvokeReturn)((_InvokeSymbol_255) address)(*((_InvokeArgs_255*)args->mem));
}

static _InvokeReturn
_golem_llm_invoke_256(gpointer address,GolemStructBuilder * args)
{
  typedef struct { guint8 padding[256]; } _InvokeArgs_256;
  typedef gint64 (*_InvokeSymbol_256)(_InvokeArgs_256);
  return (_InvokeReturn)((_InvokeSymbol_256) address)(*((_InvokeArgs_256*)args->mem));
}


static _GolemLLMInvoke _golem_llm_invoke[] = {
  _golem_llm_invoke_0,
  _golem_llm_invoke_1,
  _golem_llm_invoke_2,
  _golem_llm_invoke_3,
  _golem_llm_invoke_4,
  _golem_llm_invoke_5,
  _golem_llm_invoke_6,
  _golem_llm_invoke_7,
  _golem_llm_invoke_8,
  _golem_llm_invoke_9,
  _golem_llm_invoke_10,
  _golem_llm_invoke_11,
  _golem_llm_invoke_12,
  _golem_llm_invoke_13,
  _golem_llm_invoke_14,
  _golem_llm_invoke_15,
  _golem_llm_invoke_16,
  _golem_llm_invoke_17,
  _golem_llm_invoke_18,
  _golem_llm_invoke_19,
  _golem_llm_invoke_20,
  _golem_llm_invoke_21,
  _golem_llm_invoke_22,
  _golem_llm_invoke_23,
  _golem_llm_invoke_24,
  _golem_llm_invoke_25,
  _golem_llm_invoke_26,
  _golem_llm_invoke_27,
  _golem_llm_invoke_28,
  _golem_llm_invoke_29,
  _golem_llm_invoke_30,
  _golem_llm_invoke_31,
  _golem_llm_invoke_32,
  _golem_llm_invoke_33,
  _golem_llm_invoke_34,
  _golem_llm_invoke_35,
  _golem_llm_invoke_36,
  _golem_llm_invoke_37,
  _golem_llm_invoke_38,
  _golem_llm_invoke_39,
  _golem_llm_invoke_40,
  _golem_llm_invoke_41,
  _golem_llm_invoke_42,
  _golem_llm_invoke_43,
  _golem_llm_invoke_44,
  _golem_llm_invoke_45,
  _golem_llm_invoke_46,
  _golem_llm_invoke_47,
  _golem_llm_invoke_48,
  _golem_llm_invoke_49,
  _golem_llm_invoke_50,
  _golem_llm_invoke_51,
  _golem_llm_invoke_52,
  _golem_llm_invoke_53,
  _golem_llm_invoke_54,
  _golem_llm_invoke_55,
  _golem_llm_invoke_56,
  _golem_llm_invoke_57,
  _golem_llm_invoke_58,
  _golem_llm_invoke_59,
  _golem_llm_invoke_60,
  _golem_llm_invoke_61,
  _golem_llm_invoke_62,
  _golem_llm_invoke_63,
  _golem_llm_invoke_64,
  _golem_llm_invoke_65,
  _golem_llm_invoke_66,
  _golem_llm_invoke_67,
  _golem_llm_invoke_68,
  _golem_llm_invoke_69,
  _golem_llm_invoke_70,
  _golem_llm_invoke_71,
  _golem_llm_invoke_72,
  _golem_llm_invoke_73,
  _golem_llm_invoke_74,
  _golem_llm_invoke_75,
  _golem_llm_invoke_76,
  _golem_llm_invoke_77,
  _golem_llm_invoke_78,
  _golem_llm_invoke_79,
  _golem_llm_invoke_80,
  _golem_llm_invoke_81,
  _golem_llm_invoke_82,
  _golem_llm_invoke_83,
  _golem_llm_invoke_84,
  _golem_llm_invoke_85,
  _golem_llm_invoke_86,
  _golem_llm_invoke_87,
  _golem_llm_invoke_88,
  _golem_llm_invoke_89,
  _golem_llm_invoke_90,
  _golem_llm_invoke_91,
  _golem_llm_invoke_92,
  _golem_llm_invoke_93,
  _golem_llm_invoke_94,
  _golem_llm_invoke_95,
  _golem_llm_invoke_96,
  _golem_llm_invoke_97,
  _golem_llm_invoke_98,
  _golem_llm_invoke_99,
  _golem_llm_invoke_100,
  _golem_llm_invoke_101,
  _golem_llm_invoke_102,
  _golem_llm_invoke_103,
  _golem_llm_invoke_104,
  _golem_llm_invoke_105,
  _golem_llm_invoke_106,
  _golem_llm_invoke_107,
  _golem_llm_invoke_108,
  _golem_llm_invoke_109,
  _golem_llm_invoke_110,
  _golem_llm_invoke_111,
  _golem_llm_invoke_112,
  _golem_llm_invoke_113,
  _golem_llm_invoke_114,
  _golem_llm_invoke_115,
  _golem_llm_invoke_116,
  _golem_llm_invoke_117,
  _golem_llm_invoke_118,
  _golem_llm_invoke_119,
  _golem_llm_invoke_120,
  _golem_llm_invoke_121,
  _golem_llm_invoke_122,
  _golem_llm_invoke_123,
  _golem_llm_invoke_124,
  _golem_llm_invoke_125,
  _golem_llm_invoke_126,
  _golem_llm_invoke_127,
  _golem_llm_invoke_128,
  _golem_llm_invoke_129,
  _golem_llm_invoke_130,
  _golem_llm_invoke_131,
  _golem_llm_invoke_132,
  _golem_llm_invoke_133,
  _golem_llm_invoke_134,
  _golem_llm_invoke_135,
  _golem_llm_invoke_136,
  _golem_llm_invoke_137,
  _golem_llm_invoke_138,
  _golem_llm_invoke_139,
  _golem_llm_invoke_140,
  _golem_llm_invoke_141,
  _golem_llm_invoke_142,
  _golem_llm_invoke_143,
  _golem_llm_invoke_144,
  _golem_llm_invoke_145,
  _golem_llm_invoke_146,
  _golem_llm_invoke_147,
  _golem_llm_invoke_148,
  _golem_llm_invoke_149,
  _golem_llm_invoke_150,
  _golem_llm_invoke_151,
  _golem_llm_invoke_152,
  _golem_llm_invoke_153,
  _golem_llm_invoke_154,
  _golem_llm_invoke_155,
  _golem_llm_invoke_156,
  _golem_llm_invoke_157,
  _golem_llm_invoke_158,
  _golem_llm_invoke_159,
  _golem_llm_invoke_160,
  _golem_llm_invoke_161,
  _golem_llm_invoke_162,
  _golem_llm_invoke_163,
  _golem_llm_invoke_164,
  _golem_llm_invoke_165,
  _golem_llm_invoke_166,
  _golem_llm_invoke_167,
  _golem_llm_invoke_168,
  _golem_llm_invoke_169,
  _golem_llm_invoke_170,
  _golem_llm_invoke_171,
  _golem_llm_invoke_172,
  _golem_llm_invoke_173,
  _golem_llm_invoke_174,
  _golem_llm_invoke_175,
  _golem_llm_invoke_176,
  _golem_llm_invoke_177,
  _golem_llm_invoke_178,
  _golem_llm_invoke_179,
  _golem_llm_invoke_180,
  _golem_llm_invoke_181,
  _golem_llm_invoke_182,
  _golem_llm_invoke_183,
  _golem_llm_invoke_184,
  _golem_llm_invoke_185,
  _golem_llm_invoke_186,
  _golem_llm_invoke_187,
  _golem_llm_invoke_188,
  _golem_llm_invoke_189,
  _golem_llm_invoke_190,
  _golem_llm_invoke_191,
  _golem_llm_invoke_192,
  _golem_llm_invoke_193,
  _golem_llm_invoke_194,
  _golem_llm_invoke_195,
  _golem_llm_invoke_196,
  _golem_llm_invoke_197,
  _golem_llm_invoke_198,
  _golem_llm_invoke_199,
  _golem_llm_invoke_200,
  _golem_llm_invoke_201,
  _golem_llm_invoke_202,
  _golem_llm_invoke_203,
  _golem_llm_invoke_204,
  _golem_llm_invoke_205,
  _golem_llm_invoke_206,
  _golem_llm_invoke_207,
  _golem_llm_invoke_208,
  _golem_llm_invoke_209,
  _golem_llm_invoke_210,
  _golem_llm_invoke_211,
  _golem_llm_invoke_212,
  _golem_llm_invoke_213,
  _golem_llm_invoke_214,
  _golem_llm_invoke_215,
  _golem_llm_invoke_216,
  _golem_llm_invoke_217,
  _golem_llm_invoke_218,
  _golem_llm_invoke_219,
  _golem_llm_invoke_220,
  _golem_llm_invoke_221,
  _golem_llm_invoke_222,
  _golem_llm_invoke_223,
  _golem_llm_invoke_224,
  _golem_llm_invoke_225,
  _golem_llm_invoke_226,
  _golem_llm_invoke_227,
  _golem_llm_invoke_228,
  _golem_llm_invoke_229,
  _golem_llm_invoke_230,
  _golem_llm_invoke_231,
  _golem_llm_invoke_232,
  _golem_llm_invoke_233,
  _golem_llm_invoke_234,
  _golem_llm_invoke_235,
  _golem_llm_invoke_236,
  _golem_llm_invoke_237,
  _golem_llm_invoke_238,
  _golem_llm_invoke_239,
  _golem_llm_invoke_240,
  _golem_llm_invoke_241,
  _golem_llm_invoke_242,
  _golem_llm_invoke_243,
  _golem_llm_invoke_244,
  _golem_llm_invoke_245,
  _golem_llm_invoke_246,
  _golem_llm_invoke_247,
  _golem_llm_invoke_248,
  _golem_llm_invoke_249,
  _golem_llm_invoke_250,
  _golem_llm_invoke_251,
  _golem_llm_invoke_252,
  _golem_llm_invoke_253,
  _golem_llm_invoke_254,
  _golem_llm_invoke_255,
  _golem_llm_invoke_256
};

GolemStructBuilder *
golem_struct_builder_new()
{
  GolemStructBuilder * arg = g_new0(GolemStructBuilder,1);
  arg->mem = NULL;
  arg->offset = 0;
  arg->size = 0;
  return arg;
}


#define golem_args_expand(args,type) args->mem = g_realloc(args->mem,args->size + sizeof(type));\
				     args->offset = args->size;\
				     args->size += sizeof(type)

#define GOLEM_INVOKE_ARG(args) 	((_InvokeArg*)(args->mem + args->offset))

void
golem_struct_builder_append_string(GolemStructBuilder * args,const gchar * str1)
{
  golem_args_expand(args,gchar *);
  GOLEM_INVOKE_ARG(args)->pointer = (gpointer)str1;
}

void
golem_struct_builder_append_type(GolemStructBuilder * args,GType type)
{
  golem_args_expand(args,GType);
  GOLEM_INVOKE_ARG(args)->type = type;
}

void
golem_struct_builder_append_pointer(GolemStructBuilder * args,gpointer pointer)
{
  golem_args_expand(args,gchar *);
  GOLEM_INVOKE_ARG(args)->pointer = pointer;
}

void
golem_struct_builder_append(GolemStructBuilder * args,const GValue * value)
{
  switch(g_type_fundamental(G_VALUE_TYPE(value)))
    {
    case G_TYPE_BOOLEAN:
      golem_args_expand(args,gboolean);
      GOLEM_INVOKE_ARG(args)->boolean = g_value_get_boolean(value);
      break;
    case G_TYPE_ENUM:
      golem_args_expand(args,gint32);
      GOLEM_INVOKE_ARG(args)->int32 = g_value_get_enum(value);
      break;
    case G_TYPE_FLAGS:
      golem_args_expand(args,gint32);
      GOLEM_INVOKE_ARG(args)->int32 = g_value_get_flags(value);
      break;
    case G_TYPE_CHAR:
      golem_args_expand(args,gchar);
      GOLEM_INVOKE_ARG(args)->int8 = g_value_get_schar(value);
      break;
    case G_TYPE_UCHAR:
      golem_args_expand(args,guchar);
      GOLEM_INVOKE_ARG(args)->uint8 = g_value_get_uchar(value);
      break;
    case G_TYPE_INT:
      golem_args_expand(args,gint32);
      GOLEM_INVOKE_ARG(args)->int32 = g_value_get_int(value);
      break;
    case G_TYPE_LONG:
      golem_args_expand(args,glong);
      GOLEM_INVOKE_ARG(args)->long64 = g_value_get_long(value);
      break;
    case G_TYPE_INT64:
      golem_args_expand(args,gint64);
      GOLEM_INVOKE_ARG(args)->int64 = g_value_get_int64(value);
      break;
    case G_TYPE_UINT:
      golem_args_expand(args,guint);
      GOLEM_INVOKE_ARG(args)->uint32 = g_value_get_uint(value);
      break;
    case G_TYPE_ULONG:
      golem_args_expand(args,gulong);
      GOLEM_INVOKE_ARG(args)->ulong64 = g_value_get_ulong(value);
      break;
    case G_TYPE_UINT64:
      golem_args_expand(args,guint64);
      GOLEM_INVOKE_ARG(args)->uint64 = g_value_get_uint64(value);
      break;
    case G_TYPE_FLOAT:
      golem_args_expand(args,gfloat);
      GOLEM_INVOKE_ARG(args)->float32 = g_value_get_float(value);
      break;
    case G_TYPE_DOUBLE:
      golem_args_expand(args,gdouble);
      GOLEM_INVOKE_ARG(args)->double64 = g_value_get_double(value);
      break;
    case G_TYPE_POINTER:
      golem_args_expand(args,gpointer);
      GOLEM_INVOKE_ARG(args)->pointer = g_value_get_pointer(value);
      break;
    case G_TYPE_STRING:
      golem_args_expand(args,gpointer);
      GOLEM_INVOKE_ARG(args)->pointer = (gpointer)g_value_get_string(value);
      break;
    case G_TYPE_BOXED:
      golem_args_expand(args,gpointer);
      GOLEM_INVOKE_ARG(args)->pointer = g_value_get_boxed(value);
      break;
    case G_TYPE_OBJECT:
      golem_args_expand(args,gpointer);
      GOLEM_INVOKE_ARG(args)->pointer = g_value_get_object(value);
      break;
    }
}

void
golem_struct_builder_free(GolemStructBuilder * args)
{
  g_free(args->mem);
  g_free(args);
}

static _InvokeReturn
_golem_invoke_all(gpointer address,GolemStructBuilder * args)
{
  _GolemLLMInvoke invoker = (_golem_llm_invoke[args->size]);
  return invoker(address,args);
}

void
golem_invoke(gpointer address,GolemStructBuilder * args)
{
  _golem_invoke_all(address,args);
}

guint8
golem_invoke_guint8(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).uint8;
}

guint
golem_invoke_guint(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).uint32;
}

guint64
golem_invoke_guint64(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).uint64;
}

gulong
golem_invoke_gulong(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).ulong64;
}

gint8
golem_invoke_gint8(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).int8;
}

gint
golem_invoke_gint(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).int32;
}

gint64
golem_invoke_gint64(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).int64;
}

glong
golem_invoke_glong(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).long64;
}

gfloat
golem_invoke_gfloat(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).float32;
}

gdouble
golem_invoke_gdouble(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).double64;
}

gpointer
golem_invoke_gpointer(gpointer address,GolemStructBuilder * args)
{
  return _golem_invoke_all(address,args).pointer;
}


/*
gsize _golem_vm_template_sizeof(gpointer func){
  gsize result = 0;
  for(guint8 * bytes = (guint8*)func;*bytes != 0xC3;bytes++)
    result ++;
  return result + 1;
}

guint8 _golem_guint8_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint8 _golem_guint8_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint8 _golem_guint8_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

guint16 _golem_guint16_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint16 _golem_guint16_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint16 _golem_guint16_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

guint32 _golem_guint32_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint32 _golem_guint32_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint32 _golem_guint32_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

guint64 _golem_guint64_invoke(gpointer metadata,GolemArgs args) {  return 0; }

guint64 _golem_guint64_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

guint64 _golem_guint64_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint8 _golem_gint8_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint8 _golem_gint8_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint8 _golem_gint8_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint16 _golem_gint16_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint16 _golem_gint16_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint16 _golem_gint16_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint32 _golem_gint32_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint32 _golem_gint32_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint32 _golem_gint32_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gint64 _golem_gint64_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gint64 _golem_gint64_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gint64 _golem_gint64_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gfloat _golem_gfloat_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gfloat _golem_gfloat_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gfloat _golem_gfloat_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gdouble _golem_gdouble_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gdouble _golem_gdouble_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gdouble _golem_gdouble_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gpointer _golem_gpointer_invoke(gpointer metadata,GolemArgs args) {  return 0; }

gpointer _golem_gpointer_invoke_this(gpointer metadata,GObject * this_instance,GolemArgs args) {  return 0; }

gpointer _golem_gpointer_invoke_static(gpointer metadata,GObjectClass * class_instance,GolemArgs args) {  return 0; }

gpointer _golem_guint8_pointer = _golem_guint8_invoke;
gpointer _golem_guint16_pointer = _golem_guint16_invoke;
gpointer _golem_guint32_pointer = _golem_guint16_invoke;

guint8 _golem_guint8_template(GolemArgs args)
{
  gpointer metadata = NULL;
  guint8(*internal)(gpointer,GolemArgs) = _golem_guint8_pointer;
  return internal(metadata,args);
}

guint16 _golem_guint16_template(GolemArgs args)
{
  gpointer metadata = NULL;
  guint16(*internal)(gpointer,GolemArgs) = _golem_guint16_pointer;
  return internal(metadata,args);
}

guint32 _golem_guint32_template(GolemArgs args)
{
  gpointer metadata = NULL;
  guint32(*internal)(gpointer,GolemArgs) = _golem_guint32_pointer;
  return internal(metadata,args);
}

gpointer golem_v_func(GType return_type,gpointer metadata)
{
  gpointer v_template;
  gsize v_size;

  guint8 * v_func = NULL;
  switch(return_type)
  {
    case G_TYPE_CHAR:
      v_template = _golem_guint8_template;
      v_size = _golem_vm_template_sizeof(_golem_guint8_template);
    break;
    case G_TYPE_INT:
      v_template = _golem_guint32_template;
      v_size = _golem_vm_template_sizeof(_golem_guint32_template);
    break;
    default:
      v_func = NULL;
  }

#ifndef __WIN32__
  v_func = mmap( NULL,v_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE,0,0);
  memcpy(v_func,v_template,v_size);
  memcpy(v_func + 0xC,&metadata,sizeof(gpointer));
  return v_func;
#else
  v_func = VirtualAlloc();
#endif
}

*/
