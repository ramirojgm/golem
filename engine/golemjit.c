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

typedef struct {guint8 padding[1];} _InvokeArgs_1;
typedef struct {guint8 padding[2];} _InvokeArgs_2;
typedef struct {guint8 padding[3];} _InvokeArgs_3;
typedef struct {guint8 padding[4];} _InvokeArgs_4;
typedef struct {guint8 padding[5];} _InvokeArgs_5;
typedef struct {guint8 padding[6];} _InvokeArgs_6;
typedef struct {guint8 padding[7];} _InvokeArgs_7;
typedef struct {guint8 padding[8];} _InvokeArgs_8;
typedef struct {guint8 padding[9];} _InvokeArgs_9;
typedef struct {guint8 padding[10];} _InvokeArgs_10;
typedef struct {guint8 padding[11];} _InvokeArgs_11;
typedef struct {guint8 padding[12];} _InvokeArgs_12;
typedef struct {guint8 padding[13];} _InvokeArgs_13;
typedef struct {guint8 padding[14];} _InvokeArgs_14;
typedef struct {guint8 padding[15];} _InvokeArgs_15;
typedef struct {guint8 padding[16];} _InvokeArgs_16;
typedef struct {guint8 padding[17];} _InvokeArgs_17;
typedef struct {guint8 padding[18];} _InvokeArgs_18;
typedef struct {guint8 padding[19];} _InvokeArgs_19;
typedef struct {guint8 padding[20];} _InvokeArgs_20;
typedef struct {guint8 padding[21];} _InvokeArgs_21;
typedef struct {guint8 padding[22];} _InvokeArgs_22;
typedef struct {guint8 padding[23];} _InvokeArgs_23;
typedef struct {guint8 padding[24];} _InvokeArgs_24;
typedef struct {guint8 padding[25];} _InvokeArgs_25;
typedef struct {guint8 padding[26];} _InvokeArgs_26;
typedef struct {guint8 padding[27];} _InvokeArgs_27;
typedef struct {guint8 padding[28];} _InvokeArgs_28;
typedef struct {guint8 padding[29];} _InvokeArgs_29;
typedef struct {guint8 padding[30];} _InvokeArgs_30;
typedef struct {guint8 padding[31];} _InvokeArgs_31;
typedef struct {guint8 padding[32];} _InvokeArgs_32;
typedef struct {guint8 padding[33];} _InvokeArgs_33;
typedef struct {guint8 padding[34];} _InvokeArgs_34;
typedef struct {guint8 padding[35];} _InvokeArgs_35;
typedef struct {guint8 padding[36];} _InvokeArgs_36;
typedef struct {guint8 padding[37];} _InvokeArgs_37;
typedef struct {guint8 padding[38];} _InvokeArgs_38;
typedef struct {guint8 padding[39];} _InvokeArgs_39;
typedef struct {guint8 padding[40];} _InvokeArgs_40;
typedef struct {guint8 padding[41];} _InvokeArgs_41;
typedef struct {guint8 padding[42];} _InvokeArgs_42;
typedef struct {guint8 padding[43];} _InvokeArgs_43;
typedef struct {guint8 padding[44];} _InvokeArgs_44;
typedef struct {guint8 padding[45];} _InvokeArgs_45;
typedef struct {guint8 padding[46];} _InvokeArgs_46;
typedef struct {guint8 padding[47];} _InvokeArgs_47;
typedef struct {guint8 padding[48];} _InvokeArgs_48;
typedef struct {guint8 padding[49];} _InvokeArgs_49;
typedef struct {guint8 padding[50];} _InvokeArgs_50;
typedef struct {guint8 padding[51];} _InvokeArgs_51;
typedef struct {guint8 padding[52];} _InvokeArgs_52;
typedef struct {guint8 padding[53];} _InvokeArgs_53;
typedef struct {guint8 padding[54];} _InvokeArgs_54;
typedef struct {guint8 padding[55];} _InvokeArgs_55;
typedef struct {guint8 padding[56];} _InvokeArgs_56;
typedef struct {guint8 padding[57];} _InvokeArgs_57;
typedef struct {guint8 padding[58];} _InvokeArgs_58;
typedef struct {guint8 padding[59];} _InvokeArgs_59;
typedef struct {guint8 padding[60];} _InvokeArgs_60;
typedef struct {guint8 padding[61];} _InvokeArgs_61;
typedef struct {guint8 padding[62];} _InvokeArgs_62;
typedef struct {guint8 padding[63];} _InvokeArgs_63;
typedef struct {guint8 padding[64];} _InvokeArgs_64;
typedef struct {guint8 padding[65];} _InvokeArgs_65;
typedef struct {guint8 padding[66];} _InvokeArgs_66;
typedef struct {guint8 padding[67];} _InvokeArgs_67;
typedef struct {guint8 padding[68];} _InvokeArgs_68;
typedef struct {guint8 padding[69];} _InvokeArgs_69;
typedef struct {guint8 padding[70];} _InvokeArgs_70;
typedef struct {guint8 padding[71];} _InvokeArgs_71;
typedef struct {guint8 padding[72];} _InvokeArgs_72;
typedef struct {guint8 padding[73];} _InvokeArgs_73;
typedef struct {guint8 padding[74];} _InvokeArgs_74;
typedef struct {guint8 padding[75];} _InvokeArgs_75;
typedef struct {guint8 padding[76];} _InvokeArgs_76;
typedef struct {guint8 padding[77];} _InvokeArgs_77;
typedef struct {guint8 padding[78];} _InvokeArgs_78;
typedef struct {guint8 padding[79];} _InvokeArgs_79;
typedef struct {guint8 padding[80];} _InvokeArgs_80;
typedef struct {guint8 padding[81];} _InvokeArgs_81;
typedef struct {guint8 padding[82];} _InvokeArgs_82;
typedef struct {guint8 padding[83];} _InvokeArgs_83;
typedef struct {guint8 padding[84];} _InvokeArgs_84;
typedef struct {guint8 padding[85];} _InvokeArgs_85;
typedef struct {guint8 padding[86];} _InvokeArgs_86;
typedef struct {guint8 padding[87];} _InvokeArgs_87;
typedef struct {guint8 padding[88];} _InvokeArgs_88;
typedef struct {guint8 padding[89];} _InvokeArgs_89;
typedef struct {guint8 padding[90];} _InvokeArgs_90;
typedef struct {guint8 padding[91];} _InvokeArgs_91;
typedef struct {guint8 padding[92];} _InvokeArgs_92;
typedef struct {guint8 padding[93];} _InvokeArgs_93;
typedef struct {guint8 padding[94];} _InvokeArgs_94;
typedef struct {guint8 padding[95];} _InvokeArgs_95;
typedef struct {guint8 padding[96];} _InvokeArgs_96;
typedef struct {guint8 padding[97];} _InvokeArgs_97;
typedef struct {guint8 padding[98];} _InvokeArgs_98;
typedef struct {guint8 padding[99];} _InvokeArgs_99;
typedef struct {guint8 padding[100];} _InvokeArgs_100;
typedef struct {guint8 padding[101];} _InvokeArgs_101;
typedef struct {guint8 padding[102];} _InvokeArgs_102;
typedef struct {guint8 padding[103];} _InvokeArgs_103;
typedef struct {guint8 padding[104];} _InvokeArgs_104;
typedef struct {guint8 padding[105];} _InvokeArgs_105;
typedef struct {guint8 padding[106];} _InvokeArgs_106;
typedef struct {guint8 padding[107];} _InvokeArgs_107;
typedef struct {guint8 padding[108];} _InvokeArgs_108;
typedef struct {guint8 padding[109];} _InvokeArgs_109;
typedef struct {guint8 padding[110];} _InvokeArgs_110;
typedef struct {guint8 padding[111];} _InvokeArgs_111;
typedef struct {guint8 padding[112];} _InvokeArgs_112;
typedef struct {guint8 padding[113];} _InvokeArgs_113;
typedef struct {guint8 padding[114];} _InvokeArgs_114;
typedef struct {guint8 padding[115];} _InvokeArgs_115;
typedef struct {guint8 padding[116];} _InvokeArgs_116;
typedef struct {guint8 padding[117];} _InvokeArgs_117;
typedef struct {guint8 padding[118];} _InvokeArgs_118;
typedef struct {guint8 padding[119];} _InvokeArgs_119;
typedef struct {guint8 padding[120];} _InvokeArgs_120;
typedef struct {guint8 padding[121];} _InvokeArgs_121;
typedef struct {guint8 padding[122];} _InvokeArgs_122;
typedef struct {guint8 padding[123];} _InvokeArgs_123;
typedef struct {guint8 padding[124];} _InvokeArgs_124;
typedef struct {guint8 padding[125];} _InvokeArgs_125;
typedef struct {guint8 padding[126];} _InvokeArgs_126;
typedef struct {guint8 padding[127];} _InvokeArgs_127;
typedef struct {guint8 padding[128];} _InvokeArgs_128;
typedef struct {guint8 padding[129];} _InvokeArgs_129;
typedef struct {guint8 padding[130];} _InvokeArgs_130;
typedef struct {guint8 padding[131];} _InvokeArgs_131;
typedef struct {guint8 padding[132];} _InvokeArgs_132;
typedef struct {guint8 padding[133];} _InvokeArgs_133;
typedef struct {guint8 padding[134];} _InvokeArgs_134;
typedef struct {guint8 padding[135];} _InvokeArgs_135;
typedef struct {guint8 padding[136];} _InvokeArgs_136;
typedef struct {guint8 padding[137];} _InvokeArgs_137;
typedef struct {guint8 padding[138];} _InvokeArgs_138;
typedef struct {guint8 padding[139];} _InvokeArgs_139;
typedef struct {guint8 padding[140];} _InvokeArgs_140;
typedef struct {guint8 padding[141];} _InvokeArgs_141;
typedef struct {guint8 padding[142];} _InvokeArgs_142;
typedef struct {guint8 padding[143];} _InvokeArgs_143;
typedef struct {guint8 padding[144];} _InvokeArgs_144;
typedef struct {guint8 padding[145];} _InvokeArgs_145;
typedef struct {guint8 padding[146];} _InvokeArgs_146;
typedef struct {guint8 padding[147];} _InvokeArgs_147;
typedef struct {guint8 padding[148];} _InvokeArgs_148;
typedef struct {guint8 padding[149];} _InvokeArgs_149;
typedef struct {guint8 padding[150];} _InvokeArgs_150;
typedef struct {guint8 padding[151];} _InvokeArgs_151;
typedef struct {guint8 padding[152];} _InvokeArgs_152;
typedef struct {guint8 padding[153];} _InvokeArgs_153;
typedef struct {guint8 padding[154];} _InvokeArgs_154;
typedef struct {guint8 padding[155];} _InvokeArgs_155;
typedef struct {guint8 padding[156];} _InvokeArgs_156;
typedef struct {guint8 padding[157];} _InvokeArgs_157;
typedef struct {guint8 padding[158];} _InvokeArgs_158;
typedef struct {guint8 padding[159];} _InvokeArgs_159;
typedef struct {guint8 padding[160];} _InvokeArgs_160;
typedef struct {guint8 padding[161];} _InvokeArgs_161;
typedef struct {guint8 padding[162];} _InvokeArgs_162;
typedef struct {guint8 padding[163];} _InvokeArgs_163;
typedef struct {guint8 padding[164];} _InvokeArgs_164;
typedef struct {guint8 padding[165];} _InvokeArgs_165;
typedef struct {guint8 padding[166];} _InvokeArgs_166;
typedef struct {guint8 padding[167];} _InvokeArgs_167;
typedef struct {guint8 padding[168];} _InvokeArgs_168;
typedef struct {guint8 padding[169];} _InvokeArgs_169;
typedef struct {guint8 padding[170];} _InvokeArgs_170;
typedef struct {guint8 padding[171];} _InvokeArgs_171;
typedef struct {guint8 padding[172];} _InvokeArgs_172;
typedef struct {guint8 padding[173];} _InvokeArgs_173;
typedef struct {guint8 padding[174];} _InvokeArgs_174;
typedef struct {guint8 padding[175];} _InvokeArgs_175;
typedef struct {guint8 padding[176];} _InvokeArgs_176;
typedef struct {guint8 padding[177];} _InvokeArgs_177;
typedef struct {guint8 padding[178];} _InvokeArgs_178;
typedef struct {guint8 padding[179];} _InvokeArgs_179;
typedef struct {guint8 padding[180];} _InvokeArgs_180;
typedef struct {guint8 padding[181];} _InvokeArgs_181;
typedef struct {guint8 padding[182];} _InvokeArgs_182;
typedef struct {guint8 padding[183];} _InvokeArgs_183;
typedef struct {guint8 padding[184];} _InvokeArgs_184;
typedef struct {guint8 padding[185];} _InvokeArgs_185;
typedef struct {guint8 padding[186];} _InvokeArgs_186;
typedef struct {guint8 padding[187];} _InvokeArgs_187;
typedef struct {guint8 padding[188];} _InvokeArgs_188;
typedef struct {guint8 padding[189];} _InvokeArgs_189;
typedef struct {guint8 padding[190];} _InvokeArgs_190;
typedef struct {guint8 padding[191];} _InvokeArgs_191;
typedef struct {guint8 padding[192];} _InvokeArgs_192;
typedef struct {guint8 padding[193];} _InvokeArgs_193;
typedef struct {guint8 padding[194];} _InvokeArgs_194;
typedef struct {guint8 padding[195];} _InvokeArgs_195;
typedef struct {guint8 padding[196];} _InvokeArgs_196;
typedef struct {guint8 padding[197];} _InvokeArgs_197;
typedef struct {guint8 padding[198];} _InvokeArgs_198;
typedef struct {guint8 padding[199];} _InvokeArgs_199;
typedef struct {guint8 padding[200];} _InvokeArgs_200;
typedef struct {guint8 padding[201];} _InvokeArgs_201;
typedef struct {guint8 padding[202];} _InvokeArgs_202;
typedef struct {guint8 padding[203];} _InvokeArgs_203;
typedef struct {guint8 padding[204];} _InvokeArgs_204;
typedef struct {guint8 padding[205];} _InvokeArgs_205;
typedef struct {guint8 padding[206];} _InvokeArgs_206;
typedef struct {guint8 padding[207];} _InvokeArgs_207;
typedef struct {guint8 padding[208];} _InvokeArgs_208;
typedef struct {guint8 padding[209];} _InvokeArgs_209;
typedef struct {guint8 padding[210];} _InvokeArgs_210;
typedef struct {guint8 padding[211];} _InvokeArgs_211;
typedef struct {guint8 padding[212];} _InvokeArgs_212;
typedef struct {guint8 padding[213];} _InvokeArgs_213;
typedef struct {guint8 padding[214];} _InvokeArgs_214;
typedef struct {guint8 padding[215];} _InvokeArgs_215;
typedef struct {guint8 padding[216];} _InvokeArgs_216;
typedef struct {guint8 padding[217];} _InvokeArgs_217;
typedef struct {guint8 padding[218];} _InvokeArgs_218;
typedef struct {guint8 padding[219];} _InvokeArgs_219;
typedef struct {guint8 padding[220];} _InvokeArgs_220;
typedef struct {guint8 padding[221];} _InvokeArgs_221;
typedef struct {guint8 padding[222];} _InvokeArgs_222;
typedef struct {guint8 padding[223];} _InvokeArgs_223;
typedef struct {guint8 padding[224];} _InvokeArgs_224;
typedef struct {guint8 padding[225];} _InvokeArgs_225;
typedef struct {guint8 padding[226];} _InvokeArgs_226;
typedef struct {guint8 padding[227];} _InvokeArgs_227;
typedef struct {guint8 padding[228];} _InvokeArgs_228;
typedef struct {guint8 padding[229];} _InvokeArgs_229;
typedef struct {guint8 padding[230];} _InvokeArgs_230;
typedef struct {guint8 padding[231];} _InvokeArgs_231;
typedef struct {guint8 padding[232];} _InvokeArgs_232;
typedef struct {guint8 padding[233];} _InvokeArgs_233;
typedef struct {guint8 padding[234];} _InvokeArgs_234;
typedef struct {guint8 padding[235];} _InvokeArgs_235;
typedef struct {guint8 padding[236];} _InvokeArgs_236;
typedef struct {guint8 padding[237];} _InvokeArgs_237;
typedef struct {guint8 padding[238];} _InvokeArgs_238;
typedef struct {guint8 padding[239];} _InvokeArgs_239;
typedef struct {guint8 padding[240];} _InvokeArgs_240;
typedef struct {guint8 padding[241];} _InvokeArgs_241;
typedef struct {guint8 padding[242];} _InvokeArgs_242;
typedef struct {guint8 padding[243];} _InvokeArgs_243;
typedef struct {guint8 padding[244];} _InvokeArgs_244;
typedef struct {guint8 padding[245];} _InvokeArgs_245;
typedef struct {guint8 padding[246];} _InvokeArgs_246;
typedef struct {guint8 padding[247];} _InvokeArgs_247;
typedef struct {guint8 padding[248];} _InvokeArgs_248;
typedef struct {guint8 padding[249];} _InvokeArgs_249;
typedef struct {guint8 padding[250];} _InvokeArgs_250;
typedef struct {guint8 padding[251];} _InvokeArgs_251;
typedef struct {guint8 padding[252];} _InvokeArgs_252;
typedef struct {guint8 padding[253];} _InvokeArgs_253;
typedef struct {guint8 padding[254];} _InvokeArgs_254;
typedef struct {guint8 padding[255];} _InvokeArgs_255;
typedef struct {guint8 padding[256];} _InvokeArgs_256;

#define GOLEM_INVOKE_TYPE(result_type,address,args) switch(args->offset)\
{\
      case 1:\
      return ((result_type (*)(_InvokeArgs_1))address)(*((_InvokeArgs_1*)args->mem));\
      break;\
    case 2:\
      return ((result_type (*)(_InvokeArgs_2))address)(*((_InvokeArgs_2*)args->mem));\
      break;\
    case 3:\
      return ((result_type (*)(_InvokeArgs_3))address)(*((_InvokeArgs_3*)args->mem));\
      break;\
    case 4:\
      return ((result_type (*)(_InvokeArgs_4))address)(*((_InvokeArgs_4*)args->mem));\
      break;\
    case 5:\
      return ((result_type (*)(_InvokeArgs_5))address)(*((_InvokeArgs_5*)args->mem));\
      break;\
    case 6:\
      return ((result_type (*)(_InvokeArgs_6))address)(*((_InvokeArgs_6*)args->mem));\
      break;\
    case 7:\
      return ((result_type (*)(_InvokeArgs_7))address)(*((_InvokeArgs_7*)args->mem));\
      break;\
    case 8:\
      return ((result_type (*)(_InvokeArgs_8))address)(*((_InvokeArgs_8*)args->mem));\
      break;\
    case 9:\
      return ((result_type (*)(_InvokeArgs_9))address)(*((_InvokeArgs_9*)args->mem));\
      break;\
    case 10:\
      return ((result_type (*)(_InvokeArgs_10))address)(*((_InvokeArgs_10*)args->mem));\
      break;\
    case 11:\
      return ((result_type (*)(_InvokeArgs_11))address)(*((_InvokeArgs_11*)args->mem));\
      break;\
    case 12:\
      return ((result_type (*)(_InvokeArgs_12))address)(*((_InvokeArgs_12*)args->mem));\
      break;\
    case 13:\
      return ((result_type (*)(_InvokeArgs_13))address)(*((_InvokeArgs_13*)args->mem));\
      break;\
    case 14:\
      return ((result_type (*)(_InvokeArgs_14))address)(*((_InvokeArgs_14*)args->mem));\
      break;\
    case 15:\
      return ((result_type (*)(_InvokeArgs_15))address)(*((_InvokeArgs_15*)args->mem));\
      break;\
    case 16:\
      return ((result_type (*)(_InvokeArgs_16))address)(*((_InvokeArgs_16*)args->mem));\
      break;\
    case 17:\
      return ((result_type (*)(_InvokeArgs_17))address)(*((_InvokeArgs_17*)args->mem));\
      break;\
    case 18:\
      return ((result_type (*)(_InvokeArgs_18))address)(*((_InvokeArgs_18*)args->mem));\
      break;\
    case 19:\
      return ((result_type (*)(_InvokeArgs_19))address)(*((_InvokeArgs_19*)args->mem));\
      break;\
    case 20:\
      return ((result_type (*)(_InvokeArgs_20))address)(*((_InvokeArgs_20*)args->mem));\
      break;\
    case 21:\
      return ((result_type (*)(_InvokeArgs_21))address)(*((_InvokeArgs_21*)args->mem));\
      break;\
    case 22:\
      return ((result_type (*)(_InvokeArgs_22))address)(*((_InvokeArgs_22*)args->mem));\
      break;\
    case 23:\
      return ((result_type (*)(_InvokeArgs_23))address)(*((_InvokeArgs_23*)args->mem));\
      break;\
    case 24:\
      return ((result_type (*)(_InvokeArgs_24))address)(*((_InvokeArgs_24*)args->mem));\
      break;\
    case 25:\
      return ((result_type (*)(_InvokeArgs_25))address)(*((_InvokeArgs_25*)args->mem));\
      break;\
    case 26:\
      return ((result_type (*)(_InvokeArgs_26))address)(*((_InvokeArgs_26*)args->mem));\
      break;\
    case 27:\
      return ((result_type (*)(_InvokeArgs_27))address)(*((_InvokeArgs_27*)args->mem));\
      break;\
    case 28:\
      return ((result_type (*)(_InvokeArgs_28))address)(*((_InvokeArgs_28*)args->mem));\
      break;\
    case 29:\
      return ((result_type (*)(_InvokeArgs_29))address)(*((_InvokeArgs_29*)args->mem));\
      break;\
    case 30:\
      return ((result_type (*)(_InvokeArgs_30))address)(*((_InvokeArgs_30*)args->mem));\
      break;\
    case 31:\
      return ((result_type (*)(_InvokeArgs_31))address)(*((_InvokeArgs_31*)args->mem));\
      break;\
    case 32:\
      return ((result_type (*)(_InvokeArgs_32))address)(*((_InvokeArgs_32*)args->mem));\
      break;\
    case 33:\
      return ((result_type (*)(_InvokeArgs_33))address)(*((_InvokeArgs_33*)args->mem));\
      break;\
    case 34:\
      return ((result_type (*)(_InvokeArgs_34))address)(*((_InvokeArgs_34*)args->mem));\
      break;\
    case 35:\
      return ((result_type (*)(_InvokeArgs_35))address)(*((_InvokeArgs_35*)args->mem));\
      break;\
    case 36:\
      return ((result_type (*)(_InvokeArgs_36))address)(*((_InvokeArgs_36*)args->mem));\
      break;\
    case 37:\
      return ((result_type (*)(_InvokeArgs_37))address)(*((_InvokeArgs_37*)args->mem));\
      break;\
    case 38:\
      return ((result_type (*)(_InvokeArgs_38))address)(*((_InvokeArgs_38*)args->mem));\
      break;\
    case 39:\
      return ((result_type (*)(_InvokeArgs_39))address)(*((_InvokeArgs_39*)args->mem));\
      break;\
    case 40:\
      return ((result_type (*)(_InvokeArgs_40))address)(*((_InvokeArgs_40*)args->mem));\
      break;\
    case 41:\
      return ((result_type (*)(_InvokeArgs_41))address)(*((_InvokeArgs_41*)args->mem));\
      break;\
    case 42:\
      return ((result_type (*)(_InvokeArgs_42))address)(*((_InvokeArgs_42*)args->mem));\
      break;\
    case 43:\
      return ((result_type (*)(_InvokeArgs_43))address)(*((_InvokeArgs_43*)args->mem));\
      break;\
    case 44:\
      return ((result_type (*)(_InvokeArgs_44))address)(*((_InvokeArgs_44*)args->mem));\
      break;\
    case 45:\
      return ((result_type (*)(_InvokeArgs_45))address)(*((_InvokeArgs_45*)args->mem));\
      break;\
    case 46:\
      return ((result_type (*)(_InvokeArgs_46))address)(*((_InvokeArgs_46*)args->mem));\
      break;\
    case 47:\
      return ((result_type (*)(_InvokeArgs_47))address)(*((_InvokeArgs_47*)args->mem));\
      break;\
    case 48:\
      return ((result_type (*)(_InvokeArgs_48))address)(*((_InvokeArgs_48*)args->mem));\
      break;\
    case 49:\
      return ((result_type (*)(_InvokeArgs_49))address)(*((_InvokeArgs_49*)args->mem));\
      break;\
    case 50:\
      return ((result_type (*)(_InvokeArgs_50))address)(*((_InvokeArgs_50*)args->mem));\
      break;\
    case 51:\
      return ((result_type (*)(_InvokeArgs_51))address)(*((_InvokeArgs_51*)args->mem));\
      break;\
    case 52:\
      return ((result_type (*)(_InvokeArgs_52))address)(*((_InvokeArgs_52*)args->mem));\
      break;\
    case 53:\
      return ((result_type (*)(_InvokeArgs_53))address)(*((_InvokeArgs_53*)args->mem));\
      break;\
    case 54:\
      return ((result_type (*)(_InvokeArgs_54))address)(*((_InvokeArgs_54*)args->mem));\
      break;\
    case 55:\
      return ((result_type (*)(_InvokeArgs_55))address)(*((_InvokeArgs_55*)args->mem));\
      break;\
    case 56:\
      return ((result_type (*)(_InvokeArgs_56))address)(*((_InvokeArgs_56*)args->mem));\
      break;\
    case 57:\
      return ((result_type (*)(_InvokeArgs_57))address)(*((_InvokeArgs_57*)args->mem));\
      break;\
    case 58:\
      return ((result_type (*)(_InvokeArgs_58))address)(*((_InvokeArgs_58*)args->mem));\
      break;\
    case 59:\
      return ((result_type (*)(_InvokeArgs_59))address)(*((_InvokeArgs_59*)args->mem));\
      break;\
    case 60:\
      return ((result_type (*)(_InvokeArgs_60))address)(*((_InvokeArgs_60*)args->mem));\
      break;\
    case 61:\
      return ((result_type (*)(_InvokeArgs_61))address)(*((_InvokeArgs_61*)args->mem));\
      break;\
    case 62:\
      return ((result_type (*)(_InvokeArgs_62))address)(*((_InvokeArgs_62*)args->mem));\
      break;\
    case 63:\
      return ((result_type (*)(_InvokeArgs_63))address)(*((_InvokeArgs_63*)args->mem));\
      break;\
    case 64:\
      return ((result_type (*)(_InvokeArgs_64))address)(*((_InvokeArgs_64*)args->mem));\
      break;\
    case 65:\
      return ((result_type (*)(_InvokeArgs_65))address)(*((_InvokeArgs_65*)args->mem));\
      break;\
    case 66:\
      return ((result_type (*)(_InvokeArgs_66))address)(*((_InvokeArgs_66*)args->mem));\
      break;\
    case 67:\
      return ((result_type (*)(_InvokeArgs_67))address)(*((_InvokeArgs_67*)args->mem));\
      break;\
    case 68:\
      return ((result_type (*)(_InvokeArgs_68))address)(*((_InvokeArgs_68*)args->mem));\
      break;\
    case 69:\
      return ((result_type (*)(_InvokeArgs_69))address)(*((_InvokeArgs_69*)args->mem));\
      break;\
    case 70:\
      return ((result_type (*)(_InvokeArgs_70))address)(*((_InvokeArgs_70*)args->mem));\
      break;\
    case 71:\
      return ((result_type (*)(_InvokeArgs_71))address)(*((_InvokeArgs_71*)args->mem));\
      break;\
    case 72:\
      return ((result_type (*)(_InvokeArgs_72))address)(*((_InvokeArgs_72*)args->mem));\
      break;\
    case 73:\
      return ((result_type (*)(_InvokeArgs_73))address)(*((_InvokeArgs_73*)args->mem));\
      break;\
    case 74:\
      return ((result_type (*)(_InvokeArgs_74))address)(*((_InvokeArgs_74*)args->mem));\
      break;\
    case 75:\
      return ((result_type (*)(_InvokeArgs_75))address)(*((_InvokeArgs_75*)args->mem));\
      break;\
    case 76:\
      return ((result_type (*)(_InvokeArgs_76))address)(*((_InvokeArgs_76*)args->mem));\
      break;\
    case 77:\
      return ((result_type (*)(_InvokeArgs_77))address)(*((_InvokeArgs_77*)args->mem));\
      break;\
    case 78:\
      return ((result_type (*)(_InvokeArgs_78))address)(*((_InvokeArgs_78*)args->mem));\
      break;\
    case 79:\
      return ((result_type (*)(_InvokeArgs_79))address)(*((_InvokeArgs_79*)args->mem));\
      break;\
    case 80:\
      return ((result_type (*)(_InvokeArgs_80))address)(*((_InvokeArgs_80*)args->mem));\
      break;\
    case 81:\
      return ((result_type (*)(_InvokeArgs_81))address)(*((_InvokeArgs_81*)args->mem));\
      break;\
    case 82:\
      return ((result_type (*)(_InvokeArgs_82))address)(*((_InvokeArgs_82*)args->mem));\
      break;\
    case 83:\
      return ((result_type (*)(_InvokeArgs_83))address)(*((_InvokeArgs_83*)args->mem));\
      break;\
    case 84:\
      return ((result_type (*)(_InvokeArgs_84))address)(*((_InvokeArgs_84*)args->mem));\
      break;\
    case 85:\
      return ((result_type (*)(_InvokeArgs_85))address)(*((_InvokeArgs_85*)args->mem));\
      break;\
    case 86:\
      return ((result_type (*)(_InvokeArgs_86))address)(*((_InvokeArgs_86*)args->mem));\
      break;\
    case 87:\
      return ((result_type (*)(_InvokeArgs_87))address)(*((_InvokeArgs_87*)args->mem));\
      break;\
    case 88:\
      return ((result_type (*)(_InvokeArgs_88))address)(*((_InvokeArgs_88*)args->mem));\
      break;\
    case 89:\
      return ((result_type (*)(_InvokeArgs_89))address)(*((_InvokeArgs_89*)args->mem));\
      break;\
    case 90:\
      return ((result_type (*)(_InvokeArgs_90))address)(*((_InvokeArgs_90*)args->mem));\
      break;\
    case 91:\
      return ((result_type (*)(_InvokeArgs_91))address)(*((_InvokeArgs_91*)args->mem));\
      break;\
    case 92:\
      return ((result_type (*)(_InvokeArgs_92))address)(*((_InvokeArgs_92*)args->mem));\
      break;\
    case 93:\
      return ((result_type (*)(_InvokeArgs_93))address)(*((_InvokeArgs_93*)args->mem));\
      break;\
    case 94:\
      return ((result_type (*)(_InvokeArgs_94))address)(*((_InvokeArgs_94*)args->mem));\
      break;\
    case 95:\
      return ((result_type (*)(_InvokeArgs_95))address)(*((_InvokeArgs_95*)args->mem));\
      break;\
    case 96:\
      return ((result_type (*)(_InvokeArgs_96))address)(*((_InvokeArgs_96*)args->mem));\
      break;\
    case 97:\
      return ((result_type (*)(_InvokeArgs_97))address)(*((_InvokeArgs_97*)args->mem));\
      break;\
    case 98:\
      return ((result_type (*)(_InvokeArgs_98))address)(*((_InvokeArgs_98*)args->mem));\
      break;\
    case 99:\
      return ((result_type (*)(_InvokeArgs_99))address)(*((_InvokeArgs_99*)args->mem));\
      break;\
    case 100:\
      return ((result_type (*)(_InvokeArgs_100))address)(*((_InvokeArgs_100*)args->mem));\
      break;\
    case 101:\
      return ((result_type (*)(_InvokeArgs_101))address)(*((_InvokeArgs_101*)args->mem));\
      break;\
    case 102:\
      return ((result_type (*)(_InvokeArgs_102))address)(*((_InvokeArgs_102*)args->mem));\
      break;\
    case 103:\
      return ((result_type (*)(_InvokeArgs_103))address)(*((_InvokeArgs_103*)args->mem));\
      break;\
    case 104:\
      return ((result_type (*)(_InvokeArgs_104))address)(*((_InvokeArgs_104*)args->mem));\
      break;\
    case 105:\
      return ((result_type (*)(_InvokeArgs_105))address)(*((_InvokeArgs_105*)args->mem));\
      break;\
    case 106:\
      return ((result_type (*)(_InvokeArgs_106))address)(*((_InvokeArgs_106*)args->mem));\
      break;\
    case 107:\
      return ((result_type (*)(_InvokeArgs_107))address)(*((_InvokeArgs_107*)args->mem));\
      break;\
    case 108:\
      return ((result_type (*)(_InvokeArgs_108))address)(*((_InvokeArgs_108*)args->mem));\
      break;\
    case 109:\
      return ((result_type (*)(_InvokeArgs_109))address)(*((_InvokeArgs_109*)args->mem));\
      break;\
    case 110:\
      return ((result_type (*)(_InvokeArgs_110))address)(*((_InvokeArgs_110*)args->mem));\
      break;\
    case 111:\
      return ((result_type (*)(_InvokeArgs_111))address)(*((_InvokeArgs_111*)args->mem));\
      break;\
    case 112:\
      return ((result_type (*)(_InvokeArgs_112))address)(*((_InvokeArgs_112*)args->mem));\
      break;\
    case 113:\
      return ((result_type (*)(_InvokeArgs_113))address)(*((_InvokeArgs_113*)args->mem));\
      break;\
    case 114:\
      return ((result_type (*)(_InvokeArgs_114))address)(*((_InvokeArgs_114*)args->mem));\
      break;\
    case 115:\
      return ((result_type (*)(_InvokeArgs_115))address)(*((_InvokeArgs_115*)args->mem));\
      break;\
    case 116:\
      return ((result_type (*)(_InvokeArgs_116))address)(*((_InvokeArgs_116*)args->mem));\
      break;\
    case 117:\
      return ((result_type (*)(_InvokeArgs_117))address)(*((_InvokeArgs_117*)args->mem));\
      break;\
    case 118:\
      return ((result_type (*)(_InvokeArgs_118))address)(*((_InvokeArgs_118*)args->mem));\
      break;\
    case 119:\
      return ((result_type (*)(_InvokeArgs_119))address)(*((_InvokeArgs_119*)args->mem));\
      break;\
    case 120:\
      return ((result_type (*)(_InvokeArgs_120))address)(*((_InvokeArgs_120*)args->mem));\
      break;\
    case 121:\
      return ((result_type (*)(_InvokeArgs_121))address)(*((_InvokeArgs_121*)args->mem));\
      break;\
    case 122:\
      return ((result_type (*)(_InvokeArgs_122))address)(*((_InvokeArgs_122*)args->mem));\
      break;\
    case 123:\
      return ((result_type (*)(_InvokeArgs_123))address)(*((_InvokeArgs_123*)args->mem));\
      break;\
    case 124:\
      return ((result_type (*)(_InvokeArgs_124))address)(*((_InvokeArgs_124*)args->mem));\
      break;\
    case 125:\
      return ((result_type (*)(_InvokeArgs_125))address)(*((_InvokeArgs_125*)args->mem));\
      break;\
    case 126:\
      return ((result_type (*)(_InvokeArgs_126))address)(*((_InvokeArgs_126*)args->mem));\
      break;\
    case 127:\
      return ((result_type (*)(_InvokeArgs_127))address)(*((_InvokeArgs_127*)args->mem));\
      break;\
    case 128:\
      return ((result_type (*)(_InvokeArgs_128))address)(*((_InvokeArgs_128*)args->mem));\
      break;\
    case 129:\
      return ((result_type (*)(_InvokeArgs_129))address)(*((_InvokeArgs_129*)args->mem));\
      break;\
    case 130:\
      return ((result_type (*)(_InvokeArgs_130))address)(*((_InvokeArgs_130*)args->mem));\
      break;\
    case 131:\
      return ((result_type (*)(_InvokeArgs_131))address)(*((_InvokeArgs_131*)args->mem));\
      break;\
    case 132:\
      return ((result_type (*)(_InvokeArgs_132))address)(*((_InvokeArgs_132*)args->mem));\
      break;\
    case 133:\
      return ((result_type (*)(_InvokeArgs_133))address)(*((_InvokeArgs_133*)args->mem));\
      break;\
    case 134:\
      return ((result_type (*)(_InvokeArgs_134))address)(*((_InvokeArgs_134*)args->mem));\
      break;\
    case 135:\
      return ((result_type (*)(_InvokeArgs_135))address)(*((_InvokeArgs_135*)args->mem));\
      break;\
    case 136:\
      return ((result_type (*)(_InvokeArgs_136))address)(*((_InvokeArgs_136*)args->mem));\
      break;\
    case 137:\
      return ((result_type (*)(_InvokeArgs_137))address)(*((_InvokeArgs_137*)args->mem));\
      break;\
    case 138:\
      return ((result_type (*)(_InvokeArgs_138))address)(*((_InvokeArgs_138*)args->mem));\
      break;\
    case 139:\
      return ((result_type (*)(_InvokeArgs_139))address)(*((_InvokeArgs_139*)args->mem));\
      break;\
    case 140:\
      return ((result_type (*)(_InvokeArgs_140))address)(*((_InvokeArgs_140*)args->mem));\
      break;\
    case 141:\
      return ((result_type (*)(_InvokeArgs_141))address)(*((_InvokeArgs_141*)args->mem));\
      break;\
    case 142:\
      return ((result_type (*)(_InvokeArgs_142))address)(*((_InvokeArgs_142*)args->mem));\
      break;\
    case 143:\
      return ((result_type (*)(_InvokeArgs_143))address)(*((_InvokeArgs_143*)args->mem));\
      break;\
    case 144:\
      return ((result_type (*)(_InvokeArgs_144))address)(*((_InvokeArgs_144*)args->mem));\
      break;\
    case 145:\
      return ((result_type (*)(_InvokeArgs_145))address)(*((_InvokeArgs_145*)args->mem));\
      break;\
    case 146:\
      return ((result_type (*)(_InvokeArgs_146))address)(*((_InvokeArgs_146*)args->mem));\
      break;\
    case 147:\
      return ((result_type (*)(_InvokeArgs_147))address)(*((_InvokeArgs_147*)args->mem));\
      break;\
    case 148:\
      return ((result_type (*)(_InvokeArgs_148))address)(*((_InvokeArgs_148*)args->mem));\
      break;\
    case 149:\
      return ((result_type (*)(_InvokeArgs_149))address)(*((_InvokeArgs_149*)args->mem));\
      break;\
    case 150:\
      return ((result_type (*)(_InvokeArgs_150))address)(*((_InvokeArgs_150*)args->mem));\
      break;\
    case 151:\
      return ((result_type (*)(_InvokeArgs_151))address)(*((_InvokeArgs_151*)args->mem));\
      break;\
    case 152:\
      return ((result_type (*)(_InvokeArgs_152))address)(*((_InvokeArgs_152*)args->mem));\
      break;\
    case 153:\
      return ((result_type (*)(_InvokeArgs_153))address)(*((_InvokeArgs_153*)args->mem));\
      break;\
    case 154:\
      return ((result_type (*)(_InvokeArgs_154))address)(*((_InvokeArgs_154*)args->mem));\
      break;\
    case 155:\
      return ((result_type (*)(_InvokeArgs_155))address)(*((_InvokeArgs_155*)args->mem));\
      break;\
    case 156:\
      return ((result_type (*)(_InvokeArgs_156))address)(*((_InvokeArgs_156*)args->mem));\
      break;\
    case 157:\
      return ((result_type (*)(_InvokeArgs_157))address)(*((_InvokeArgs_157*)args->mem));\
      break;\
    case 158:\
      return ((result_type (*)(_InvokeArgs_158))address)(*((_InvokeArgs_158*)args->mem));\
      break;\
    case 159:\
      return ((result_type (*)(_InvokeArgs_159))address)(*((_InvokeArgs_159*)args->mem));\
      break;\
    case 160:\
      return ((result_type (*)(_InvokeArgs_160))address)(*((_InvokeArgs_160*)args->mem));\
      break;\
    case 161:\
      return ((result_type (*)(_InvokeArgs_161))address)(*((_InvokeArgs_161*)args->mem));\
      break;\
    case 162:\
      return ((result_type (*)(_InvokeArgs_162))address)(*((_InvokeArgs_162*)args->mem));\
      break;\
    case 163:\
      return ((result_type (*)(_InvokeArgs_163))address)(*((_InvokeArgs_163*)args->mem));\
      break;\
    case 164:\
      return ((result_type (*)(_InvokeArgs_164))address)(*((_InvokeArgs_164*)args->mem));\
      break;\
    case 165:\
      return ((result_type (*)(_InvokeArgs_165))address)(*((_InvokeArgs_165*)args->mem));\
      break;\
    case 166:\
      return ((result_type (*)(_InvokeArgs_166))address)(*((_InvokeArgs_166*)args->mem));\
      break;\
    case 167:\
      return ((result_type (*)(_InvokeArgs_167))address)(*((_InvokeArgs_167*)args->mem));\
      break;\
    case 168:\
      return ((result_type (*)(_InvokeArgs_168))address)(*((_InvokeArgs_168*)args->mem));\
      break;\
    case 169:\
      return ((result_type (*)(_InvokeArgs_169))address)(*((_InvokeArgs_169*)args->mem));\
      break;\
    case 170:\
      return ((result_type (*)(_InvokeArgs_170))address)(*((_InvokeArgs_170*)args->mem));\
      break;\
    case 171:\
      return ((result_type (*)(_InvokeArgs_171))address)(*((_InvokeArgs_171*)args->mem));\
      break;\
    case 172:\
      return ((result_type (*)(_InvokeArgs_172))address)(*((_InvokeArgs_172*)args->mem));\
      break;\
    case 173:\
      return ((result_type (*)(_InvokeArgs_173))address)(*((_InvokeArgs_173*)args->mem));\
      break;\
    case 174:\
      return ((result_type (*)(_InvokeArgs_174))address)(*((_InvokeArgs_174*)args->mem));\
      break;\
    case 175:\
      return ((result_type (*)(_InvokeArgs_175))address)(*((_InvokeArgs_175*)args->mem));\
      break;\
    case 176:\
      return ((result_type (*)(_InvokeArgs_176))address)(*((_InvokeArgs_176*)args->mem));\
      break;\
    case 177:\
      return ((result_type (*)(_InvokeArgs_177))address)(*((_InvokeArgs_177*)args->mem));\
      break;\
    case 178:\
      return ((result_type (*)(_InvokeArgs_178))address)(*((_InvokeArgs_178*)args->mem));\
      break;\
    case 179:\
      return ((result_type (*)(_InvokeArgs_179))address)(*((_InvokeArgs_179*)args->mem));\
      break;\
    case 180:\
      return ((result_type (*)(_InvokeArgs_180))address)(*((_InvokeArgs_180*)args->mem));\
      break;\
    case 181:\
      return ((result_type (*)(_InvokeArgs_181))address)(*((_InvokeArgs_181*)args->mem));\
      break;\
    case 182:\
      return ((result_type (*)(_InvokeArgs_182))address)(*((_InvokeArgs_182*)args->mem));\
      break;\
    case 183:\
      return ((result_type (*)(_InvokeArgs_183))address)(*((_InvokeArgs_183*)args->mem));\
      break;\
    case 184:\
      return ((result_type (*)(_InvokeArgs_184))address)(*((_InvokeArgs_184*)args->mem));\
      break;\
    case 185:\
      return ((result_type (*)(_InvokeArgs_185))address)(*((_InvokeArgs_185*)args->mem));\
      break;\
    case 186:\
      return ((result_type (*)(_InvokeArgs_186))address)(*((_InvokeArgs_186*)args->mem));\
      break;\
    case 187:\
      return ((result_type (*)(_InvokeArgs_187))address)(*((_InvokeArgs_187*)args->mem));\
      break;\
    case 188:\
      return ((result_type (*)(_InvokeArgs_188))address)(*((_InvokeArgs_188*)args->mem));\
      break;\
    case 189:\
      return ((result_type (*)(_InvokeArgs_189))address)(*((_InvokeArgs_189*)args->mem));\
      break;\
    case 190:\
      return ((result_type (*)(_InvokeArgs_190))address)(*((_InvokeArgs_190*)args->mem));\
      break;\
    case 191:\
      return ((result_type (*)(_InvokeArgs_191))address)(*((_InvokeArgs_191*)args->mem));\
      break;\
    case 192:\
      return ((result_type (*)(_InvokeArgs_192))address)(*((_InvokeArgs_192*)args->mem));\
      break;\
    case 193:\
      return ((result_type (*)(_InvokeArgs_193))address)(*((_InvokeArgs_193*)args->mem));\
      break;\
    case 194:\
      return ((result_type (*)(_InvokeArgs_194))address)(*((_InvokeArgs_194*)args->mem));\
      break;\
    case 195:\
      return ((result_type (*)(_InvokeArgs_195))address)(*((_InvokeArgs_195*)args->mem));\
      break;\
    case 196:\
      return ((result_type (*)(_InvokeArgs_196))address)(*((_InvokeArgs_196*)args->mem));\
      break;\
    case 197:\
      return ((result_type (*)(_InvokeArgs_197))address)(*((_InvokeArgs_197*)args->mem));\
      break;\
    case 198:\
      return ((result_type (*)(_InvokeArgs_198))address)(*((_InvokeArgs_198*)args->mem));\
      break;\
    case 199:\
      return ((result_type (*)(_InvokeArgs_199))address)(*((_InvokeArgs_199*)args->mem));\
      break;\
    case 200:\
      return ((result_type (*)(_InvokeArgs_200))address)(*((_InvokeArgs_200*)args->mem));\
      break;\
    case 201:\
      return ((result_type (*)(_InvokeArgs_201))address)(*((_InvokeArgs_201*)args->mem));\
      break;\
    case 202:\
      return ((result_type (*)(_InvokeArgs_202))address)(*((_InvokeArgs_202*)args->mem));\
      break;\
    case 203:\
      return ((result_type (*)(_InvokeArgs_203))address)(*((_InvokeArgs_203*)args->mem));\
      break;\
    case 204:\
      return ((result_type (*)(_InvokeArgs_204))address)(*((_InvokeArgs_204*)args->mem));\
      break;\
    case 205:\
      return ((result_type (*)(_InvokeArgs_205))address)(*((_InvokeArgs_205*)args->mem));\
      break;\
    case 206:\
      return ((result_type (*)(_InvokeArgs_206))address)(*((_InvokeArgs_206*)args->mem));\
      break;\
    case 207:\
      return ((result_type (*)(_InvokeArgs_207))address)(*((_InvokeArgs_207*)args->mem));\
      break;\
    case 208:\
      return ((result_type (*)(_InvokeArgs_208))address)(*((_InvokeArgs_208*)args->mem));\
      break;\
    case 209:\
      return ((result_type (*)(_InvokeArgs_209))address)(*((_InvokeArgs_209*)args->mem));\
      break;\
    case 210:\
      return ((result_type (*)(_InvokeArgs_210))address)(*((_InvokeArgs_210*)args->mem));\
      break;\
    case 211:\
      return ((result_type (*)(_InvokeArgs_211))address)(*((_InvokeArgs_211*)args->mem));\
      break;\
    case 212:\
      return ((result_type (*)(_InvokeArgs_212))address)(*((_InvokeArgs_212*)args->mem));\
      break;\
    case 213:\
      return ((result_type (*)(_InvokeArgs_213))address)(*((_InvokeArgs_213*)args->mem));\
      break;\
    case 214:\
      return ((result_type (*)(_InvokeArgs_214))address)(*((_InvokeArgs_214*)args->mem));\
      break;\
    case 215:\
      return ((result_type (*)(_InvokeArgs_215))address)(*((_InvokeArgs_215*)args->mem));\
      break;\
    case 216:\
      return ((result_type (*)(_InvokeArgs_216))address)(*((_InvokeArgs_216*)args->mem));\
      break;\
    case 217:\
      return ((result_type (*)(_InvokeArgs_217))address)(*((_InvokeArgs_217*)args->mem));\
      break;\
    case 218:\
      return ((result_type (*)(_InvokeArgs_218))address)(*((_InvokeArgs_218*)args->mem));\
      break;\
    case 219:\
      return ((result_type (*)(_InvokeArgs_219))address)(*((_InvokeArgs_219*)args->mem));\
      break;\
    case 220:\
      return ((result_type (*)(_InvokeArgs_220))address)(*((_InvokeArgs_220*)args->mem));\
      break;\
    case 221:\
      return ((result_type (*)(_InvokeArgs_221))address)(*((_InvokeArgs_221*)args->mem));\
      break;\
    case 222:\
      return ((result_type (*)(_InvokeArgs_222))address)(*((_InvokeArgs_222*)args->mem));\
      break;\
    case 223:\
      return ((result_type (*)(_InvokeArgs_223))address)(*((_InvokeArgs_223*)args->mem));\
      break;\
    case 224:\
      return ((result_type (*)(_InvokeArgs_224))address)(*((_InvokeArgs_224*)args->mem));\
      break;\
    case 225:\
      return ((result_type (*)(_InvokeArgs_225))address)(*((_InvokeArgs_225*)args->mem));\
      break;\
    case 226:\
      return ((result_type (*)(_InvokeArgs_226))address)(*((_InvokeArgs_226*)args->mem));\
      break;\
    case 227:\
      return ((result_type (*)(_InvokeArgs_227))address)(*((_InvokeArgs_227*)args->mem));\
      break;\
    case 228:\
      return ((result_type (*)(_InvokeArgs_228))address)(*((_InvokeArgs_228*)args->mem));\
      break;\
    case 229:\
      return ((result_type (*)(_InvokeArgs_229))address)(*((_InvokeArgs_229*)args->mem));\
      break;\
    case 230:\
      return ((result_type (*)(_InvokeArgs_230))address)(*((_InvokeArgs_230*)args->mem));\
      break;\
    case 231:\
      return ((result_type (*)(_InvokeArgs_231))address)(*((_InvokeArgs_231*)args->mem));\
      break;\
    case 232:\
      return ((result_type (*)(_InvokeArgs_232))address)(*((_InvokeArgs_232*)args->mem));\
      break;\
    case 233:\
      return ((result_type (*)(_InvokeArgs_233))address)(*((_InvokeArgs_233*)args->mem));\
      break;\
    case 234:\
      return ((result_type (*)(_InvokeArgs_234))address)(*((_InvokeArgs_234*)args->mem));\
      break;\
    case 235:\
      return ((result_type (*)(_InvokeArgs_235))address)(*((_InvokeArgs_235*)args->mem));\
      break;\
    case 236:\
      return ((result_type (*)(_InvokeArgs_236))address)(*((_InvokeArgs_236*)args->mem));\
      break;\
    case 237:\
      return ((result_type (*)(_InvokeArgs_237))address)(*((_InvokeArgs_237*)args->mem));\
      break;\
    case 238:\
      return ((result_type (*)(_InvokeArgs_238))address)(*((_InvokeArgs_238*)args->mem));\
      break;\
    case 239:\
      return ((result_type (*)(_InvokeArgs_239))address)(*((_InvokeArgs_239*)args->mem));\
      break;\
    case 240:\
      return ((result_type (*)(_InvokeArgs_240))address)(*((_InvokeArgs_240*)args->mem));\
      break;\
    case 241:\
      return ((result_type (*)(_InvokeArgs_241))address)(*((_InvokeArgs_241*)args->mem));\
      break;\
    case 242:\
      return ((result_type (*)(_InvokeArgs_242))address)(*((_InvokeArgs_242*)args->mem));\
      break;\
    case 243:\
      return ((result_type (*)(_InvokeArgs_243))address)(*((_InvokeArgs_243*)args->mem));\
      break;\
    case 244:\
      return ((result_type (*)(_InvokeArgs_244))address)(*((_InvokeArgs_244*)args->mem));\
      break;\
    case 245:\
      return ((result_type (*)(_InvokeArgs_245))address)(*((_InvokeArgs_245*)args->mem));\
      break;\
    case 246:\
      return ((result_type (*)(_InvokeArgs_246))address)(*((_InvokeArgs_246*)args->mem));\
      break;\
    case 247:\
      return ((result_type (*)(_InvokeArgs_247))address)(*((_InvokeArgs_247*)args->mem));\
      break;\
    case 248:\
      return ((result_type (*)(_InvokeArgs_248))address)(*((_InvokeArgs_248*)args->mem));\
      break;\
    case 249:\
      return ((result_type (*)(_InvokeArgs_249))address)(*((_InvokeArgs_249*)args->mem));\
      break;\
    case 250:\
      return ((result_type (*)(_InvokeArgs_250))address)(*((_InvokeArgs_250*)args->mem));\
      break;\
    case 251:\
      return ((result_type (*)(_InvokeArgs_251))address)(*((_InvokeArgs_251*)args->mem));\
      break;\
    case 252:\
      return ((result_type (*)(_InvokeArgs_252))address)(*((_InvokeArgs_252*)args->mem));\
      break;\
    case 253:\
      return ((result_type (*)(_InvokeArgs_253))address)(*((_InvokeArgs_253*)args->mem));\
      break;\
    case 254:\
      return ((result_type (*)(_InvokeArgs_254))address)(*((_InvokeArgs_254*)args->mem));\
      break;\
    case 255:\
      return ((result_type (*)(_InvokeArgs_255))address)(*((_InvokeArgs_255*)args->mem));\
      break;\
    case 256:\
      return ((result_type (*)(_InvokeArgs_256))address)(*((_InvokeArgs_256*)args->mem));\
      break;\
    default:\
      return ((result_type (*)())address)();\
}

GolemArgs *
golem_args_new()
{
  GolemArgs * arg = g_new0(GolemArgs,1);
  arg->mem = NULL;
  arg->offset = 0;
  return arg;
}


#define GOLEM_ARGS_SET(type,value_get)  size = sizeof(type);\
					args->mem = g_realloc(args->mem,args->offset + size);\
					*((type*)(args->mem + offset)) = value_get(value)

void
golem_args_append_string(GolemArgs * args,const gchar * str1)
{
  args->mem = g_realloc(args->mem,args->offset + sizeof(gchar*));
  *((const gchar**)args->mem + args->offset) = str1;
  args->offset += sizeof(gchar*);
}

void
golem_args_append_type(GolemArgs * args,GType type)
{
  args->mem = g_realloc(args->mem,args->offset + sizeof(GType));
  *((GType*)args->mem + args->offset) = type;
  args->offset += sizeof(GType);
}

void
golem_args_append_pointer(GolemArgs * args,gpointer pointer)
{
  args->mem = g_realloc(args->mem,args->offset + sizeof(gpointer));
  *((gpointer*)args->mem + args->offset) = pointer;
  args->offset += sizeof(gpointer);
}


void
golem_args_append(GolemArgs * args,const GValue * value)
{
  guint16 offset = args->offset;
  guint16 size;
  switch(g_type_fundamental(G_VALUE_TYPE(value)))
    {
    case G_TYPE_BOOLEAN:
      GOLEM_ARGS_SET(gboolean,g_value_get_boolean);
      break;
    case G_TYPE_ENUM:
      GOLEM_ARGS_SET(gint,g_value_get_enum);
      break;
    case G_TYPE_FLAGS:
      GOLEM_ARGS_SET(guint,g_value_get_flags);
      break;
    case G_TYPE_CHAR:
      GOLEM_ARGS_SET(gchar,g_value_get_schar);
      break;
    case G_TYPE_UCHAR:
      GOLEM_ARGS_SET(guchar,g_value_get_uchar);
      break;
    case G_TYPE_INT:
      GOLEM_ARGS_SET(gint,g_value_get_int);
      break;
    case G_TYPE_LONG:
      GOLEM_ARGS_SET(glong,g_value_get_long);
      break;
    case G_TYPE_INT64:
      GOLEM_ARGS_SET(gint64,g_value_get_int64);
      break;
    case G_TYPE_UINT:
      GOLEM_ARGS_SET(guint,g_value_get_uint);
      break;
    case G_TYPE_ULONG:
      GOLEM_ARGS_SET(gulong,g_value_get_ulong);
      break;
    case G_TYPE_UINT64:
      GOLEM_ARGS_SET(guint64,g_value_get_uint64);
      break;
    case G_TYPE_FLOAT:
      GOLEM_ARGS_SET(gfloat,g_value_get_float);
      break;
    case G_TYPE_DOUBLE:
      GOLEM_ARGS_SET(gdouble,g_value_get_double);
      break;
    case G_TYPE_POINTER:
      GOLEM_ARGS_SET(gpointer,g_value_get_pointer);
      break;
    case G_TYPE_STRING:
      GOLEM_ARGS_SET(gchar*,g_value_get_string);
      break;
    case G_TYPE_BOXED:
      GOLEM_ARGS_SET(gpointer,g_value_get_boxed);
      break;
    case G_TYPE_OBJECT:
      GOLEM_ARGS_SET(GObject*,g_value_get_object);
      break;
    }
   args->offset += size;
}

void
golem_args_free(GolemArgs * args)
{
  g_free(args->mem);
  g_free(args);
}

void
golem_invoke(gpointer address,GolemArgs * args)
{
  switch(args->offset)
  {
    case 1:
    	((void (*)(_InvokeArgs_1))address)(*((_InvokeArgs_1*)args->mem));
    	break;
    case 2:
    	((void (*)(_InvokeArgs_2))address)(*((_InvokeArgs_2*)args->mem));
    	break;
    case 3:
    	((void (*)(_InvokeArgs_3))address)(*((_InvokeArgs_3*)args->mem));
    	break;
    case 4:
    	((void (*)(_InvokeArgs_4))address)(*((_InvokeArgs_4*)args->mem));
    	break;
    case 5:
    	((void (*)(_InvokeArgs_5))address)(*((_InvokeArgs_5*)args->mem));
    	break;
    case 6:
    	((void (*)(_InvokeArgs_6))address)(*((_InvokeArgs_6*)args->mem));
    	break;
    case 7:
    	((void (*)(_InvokeArgs_7))address)(*((_InvokeArgs_7*)args->mem));
    	break;
    case 8:
    	((void (*)(_InvokeArgs_8))address)(*((_InvokeArgs_8*)args->mem));
    	break;
    case 9:
    	((void (*)(_InvokeArgs_9))address)(*((_InvokeArgs_9*)args->mem));
    	break;
    case 10:
    	((void (*)(_InvokeArgs_10))address)(*((_InvokeArgs_10*)args->mem));
    	break;
    case 11:
    	((void (*)(_InvokeArgs_11))address)(*((_InvokeArgs_11*)args->mem));
    	break;
    case 12:
    	((void (*)(_InvokeArgs_12))address)(*((_InvokeArgs_12*)args->mem));
    	break;
    case 13:
    	((void (*)(_InvokeArgs_13))address)(*((_InvokeArgs_13*)args->mem));
    	break;
    case 14:
    	((void (*)(_InvokeArgs_14))address)(*((_InvokeArgs_14*)args->mem));
    	break;
    case 15:
    	((void (*)(_InvokeArgs_15))address)(*((_InvokeArgs_15*)args->mem));
    	break;
    case 16:
    	((void (*)(_InvokeArgs_16))address)(*((_InvokeArgs_16*)args->mem));
    	break;
    case 17:
    	((void (*)(_InvokeArgs_17))address)(*((_InvokeArgs_17*)args->mem));
    	break;
    case 18:
    	((void (*)(_InvokeArgs_18))address)(*((_InvokeArgs_18*)args->mem));
    	break;
    case 19:
    	((void (*)(_InvokeArgs_19))address)(*((_InvokeArgs_19*)args->mem));
    	break;
    case 20:
    	((void (*)(_InvokeArgs_20))address)(*((_InvokeArgs_20*)args->mem));
    	break;
    case 21:
    	((void (*)(_InvokeArgs_21))address)(*((_InvokeArgs_21*)args->mem));
    	break;
    case 22:
    	((void (*)(_InvokeArgs_22))address)(*((_InvokeArgs_22*)args->mem));
    	break;
    case 23:
    	((void (*)(_InvokeArgs_23))address)(*((_InvokeArgs_23*)args->mem));
    	break;
    case 24:
    	((void (*)(_InvokeArgs_24))address)(*((_InvokeArgs_24*)args->mem));
    	break;
    case 25:
    	((void (*)(_InvokeArgs_25))address)(*((_InvokeArgs_25*)args->mem));
    	break;
    case 26:
    	((void (*)(_InvokeArgs_26))address)(*((_InvokeArgs_26*)args->mem));
    	break;
    case 27:
    	((void (*)(_InvokeArgs_27))address)(*((_InvokeArgs_27*)args->mem));
    	break;
    case 28:
    	((void (*)(_InvokeArgs_28))address)(*((_InvokeArgs_28*)args->mem));
    	break;
    case 29:
    	((void (*)(_InvokeArgs_29))address)(*((_InvokeArgs_29*)args->mem));
    	break;
    case 30:
    	((void (*)(_InvokeArgs_30))address)(*((_InvokeArgs_30*)args->mem));
    	break;
    case 31:
    	((void (*)(_InvokeArgs_31))address)(*((_InvokeArgs_31*)args->mem));
    	break;
    case 32:
    	((void (*)(_InvokeArgs_32))address)(*((_InvokeArgs_32*)args->mem));
    	break;
    case 33:
    	((void (*)(_InvokeArgs_33))address)(*((_InvokeArgs_33*)args->mem));
    	break;
    case 34:
    	((void (*)(_InvokeArgs_34))address)(*((_InvokeArgs_34*)args->mem));
    	break;
    case 35:
    	((void (*)(_InvokeArgs_35))address)(*((_InvokeArgs_35*)args->mem));
    	break;
    case 36:
    	((void (*)(_InvokeArgs_36))address)(*((_InvokeArgs_36*)args->mem));
    	break;
    case 37:
    	((void (*)(_InvokeArgs_37))address)(*((_InvokeArgs_37*)args->mem));
    	break;
    case 38:
    	((void (*)(_InvokeArgs_38))address)(*((_InvokeArgs_38*)args->mem));
    	break;
    case 39:
    	((void (*)(_InvokeArgs_39))address)(*((_InvokeArgs_39*)args->mem));
    	break;
    case 40:
    	((void (*)(_InvokeArgs_40))address)(*((_InvokeArgs_40*)args->mem));
    	break;
    case 41:
    	((void (*)(_InvokeArgs_41))address)(*((_InvokeArgs_41*)args->mem));
    	break;
    case 42:
    	((void (*)(_InvokeArgs_42))address)(*((_InvokeArgs_42*)args->mem));
    	break;
    case 43:
    	((void (*)(_InvokeArgs_43))address)(*((_InvokeArgs_43*)args->mem));
    	break;
    case 44:
    	((void (*)(_InvokeArgs_44))address)(*((_InvokeArgs_44*)args->mem));
    	break;
    case 45:
    	((void (*)(_InvokeArgs_45))address)(*((_InvokeArgs_45*)args->mem));
    	break;
    case 46:
    	((void (*)(_InvokeArgs_46))address)(*((_InvokeArgs_46*)args->mem));
    	break;
    case 47:
    	((void (*)(_InvokeArgs_47))address)(*((_InvokeArgs_47*)args->mem));
    	break;
    case 48:
    	((void (*)(_InvokeArgs_48))address)(*((_InvokeArgs_48*)args->mem));
    	break;
    case 49:
    	((void (*)(_InvokeArgs_49))address)(*((_InvokeArgs_49*)args->mem));
    	break;
    case 50:
    	((void (*)(_InvokeArgs_50))address)(*((_InvokeArgs_50*)args->mem));
    	break;
    case 51:
    	((void (*)(_InvokeArgs_51))address)(*((_InvokeArgs_51*)args->mem));
    	break;
    case 52:
    	((void (*)(_InvokeArgs_52))address)(*((_InvokeArgs_52*)args->mem));
    	break;
    case 53:
    	((void (*)(_InvokeArgs_53))address)(*((_InvokeArgs_53*)args->mem));
    	break;
    case 54:
    	((void (*)(_InvokeArgs_54))address)(*((_InvokeArgs_54*)args->mem));
    	break;
    case 55:
    	((void (*)(_InvokeArgs_55))address)(*((_InvokeArgs_55*)args->mem));
    	break;
    case 56:
    	((void (*)(_InvokeArgs_56))address)(*((_InvokeArgs_56*)args->mem));
    	break;
    case 57:
    	((void (*)(_InvokeArgs_57))address)(*((_InvokeArgs_57*)args->mem));
    	break;
    case 58:
    	((void (*)(_InvokeArgs_58))address)(*((_InvokeArgs_58*)args->mem));
    	break;
    case 59:
    	((void (*)(_InvokeArgs_59))address)(*((_InvokeArgs_59*)args->mem));
    	break;
    case 60:
    	((void (*)(_InvokeArgs_60))address)(*((_InvokeArgs_60*)args->mem));
    	break;
    case 61:
    	((void (*)(_InvokeArgs_61))address)(*((_InvokeArgs_61*)args->mem));
    	break;
    case 62:
    	((void (*)(_InvokeArgs_62))address)(*((_InvokeArgs_62*)args->mem));
    	break;
    case 63:
    	((void (*)(_InvokeArgs_63))address)(*((_InvokeArgs_63*)args->mem));
    	break;
    case 64:
    	((void (*)(_InvokeArgs_64))address)(*((_InvokeArgs_64*)args->mem));
    	break;
    case 65:
    	((void (*)(_InvokeArgs_65))address)(*((_InvokeArgs_65*)args->mem));
    	break;
    case 66:
    	((void (*)(_InvokeArgs_66))address)(*((_InvokeArgs_66*)args->mem));
    	break;
    case 67:
    	((void (*)(_InvokeArgs_67))address)(*((_InvokeArgs_67*)args->mem));
    	break;
    case 68:
    	((void (*)(_InvokeArgs_68))address)(*((_InvokeArgs_68*)args->mem));
    	break;
    case 69:
    	((void (*)(_InvokeArgs_69))address)(*((_InvokeArgs_69*)args->mem));
    	break;
    case 70:
    	((void (*)(_InvokeArgs_70))address)(*((_InvokeArgs_70*)args->mem));
    	break;
    case 71:
    	((void (*)(_InvokeArgs_71))address)(*((_InvokeArgs_71*)args->mem));
    	break;
    case 72:
    	((void (*)(_InvokeArgs_72))address)(*((_InvokeArgs_72*)args->mem));
    	break;
    case 73:
    	((void (*)(_InvokeArgs_73))address)(*((_InvokeArgs_73*)args->mem));
    	break;
    case 74:
    	((void (*)(_InvokeArgs_74))address)(*((_InvokeArgs_74*)args->mem));
    	break;
    case 75:
    	((void (*)(_InvokeArgs_75))address)(*((_InvokeArgs_75*)args->mem));
    	break;
    case 76:
    	((void (*)(_InvokeArgs_76))address)(*((_InvokeArgs_76*)args->mem));
    	break;
    case 77:
    	((void (*)(_InvokeArgs_77))address)(*((_InvokeArgs_77*)args->mem));
    	break;
    case 78:
    	((void (*)(_InvokeArgs_78))address)(*((_InvokeArgs_78*)args->mem));
    	break;
    case 79:
    	((void (*)(_InvokeArgs_79))address)(*((_InvokeArgs_79*)args->mem));
    	break;
    case 80:
    	((void (*)(_InvokeArgs_80))address)(*((_InvokeArgs_80*)args->mem));
    	break;
    case 81:
    	((void (*)(_InvokeArgs_81))address)(*((_InvokeArgs_81*)args->mem));
    	break;
    case 82:
    	((void (*)(_InvokeArgs_82))address)(*((_InvokeArgs_82*)args->mem));
    	break;
    case 83:
    	((void (*)(_InvokeArgs_83))address)(*((_InvokeArgs_83*)args->mem));
    	break;
    case 84:
    	((void (*)(_InvokeArgs_84))address)(*((_InvokeArgs_84*)args->mem));
    	break;
    case 85:
    	((void (*)(_InvokeArgs_85))address)(*((_InvokeArgs_85*)args->mem));
    	break;
    case 86:
    	((void (*)(_InvokeArgs_86))address)(*((_InvokeArgs_86*)args->mem));
    	break;
    case 87:
    	((void (*)(_InvokeArgs_87))address)(*((_InvokeArgs_87*)args->mem));
    	break;
    case 88:
    	((void (*)(_InvokeArgs_88))address)(*((_InvokeArgs_88*)args->mem));
    	break;
    case 89:
    	((void (*)(_InvokeArgs_89))address)(*((_InvokeArgs_89*)args->mem));
    	break;
    case 90:
    	((void (*)(_InvokeArgs_90))address)(*((_InvokeArgs_90*)args->mem));
    	break;
    case 91:
    	((void (*)(_InvokeArgs_91))address)(*((_InvokeArgs_91*)args->mem));
    	break;
    case 92:
    	((void (*)(_InvokeArgs_92))address)(*((_InvokeArgs_92*)args->mem));
    	break;
    case 93:
    	((void (*)(_InvokeArgs_93))address)(*((_InvokeArgs_93*)args->mem));
    	break;
    case 94:
    	((void (*)(_InvokeArgs_94))address)(*((_InvokeArgs_94*)args->mem));
    	break;
    case 95:
    	((void (*)(_InvokeArgs_95))address)(*((_InvokeArgs_95*)args->mem));
    	break;
    case 96:
    	((void (*)(_InvokeArgs_96))address)(*((_InvokeArgs_96*)args->mem));
    	break;
    case 97:
    	((void (*)(_InvokeArgs_97))address)(*((_InvokeArgs_97*)args->mem));
    	break;
    case 98:
    	((void (*)(_InvokeArgs_98))address)(*((_InvokeArgs_98*)args->mem));
    	break;
    case 99:
    	((void (*)(_InvokeArgs_99))address)(*((_InvokeArgs_99*)args->mem));
    	break;
    case 100:
    	((void (*)(_InvokeArgs_100))address)(*((_InvokeArgs_100*)args->mem));
    	break;
    case 101:
    	((void (*)(_InvokeArgs_101))address)(*((_InvokeArgs_101*)args->mem));
    	break;
    case 102:
    	((void (*)(_InvokeArgs_102))address)(*((_InvokeArgs_102*)args->mem));
    	break;
    case 103:
    	((void (*)(_InvokeArgs_103))address)(*((_InvokeArgs_103*)args->mem));
    	break;
    case 104:
    	((void (*)(_InvokeArgs_104))address)(*((_InvokeArgs_104*)args->mem));
    	break;
    case 105:
    	((void (*)(_InvokeArgs_105))address)(*((_InvokeArgs_105*)args->mem));
    	break;
    case 106:
    	((void (*)(_InvokeArgs_106))address)(*((_InvokeArgs_106*)args->mem));
    	break;
    case 107:
    	((void (*)(_InvokeArgs_107))address)(*((_InvokeArgs_107*)args->mem));
    	break;
    case 108:
    	((void (*)(_InvokeArgs_108))address)(*((_InvokeArgs_108*)args->mem));
    	break;
    case 109:
    	((void (*)(_InvokeArgs_109))address)(*((_InvokeArgs_109*)args->mem));
    	break;
    case 110:
    	((void (*)(_InvokeArgs_110))address)(*((_InvokeArgs_110*)args->mem));
    	break;
    case 111:
    	((void (*)(_InvokeArgs_111))address)(*((_InvokeArgs_111*)args->mem));
    	break;
    case 112:
    	((void (*)(_InvokeArgs_112))address)(*((_InvokeArgs_112*)args->mem));
    	break;
    case 113:
    	((void (*)(_InvokeArgs_113))address)(*((_InvokeArgs_113*)args->mem));
    	break;
    case 114:
    	((void (*)(_InvokeArgs_114))address)(*((_InvokeArgs_114*)args->mem));
    	break;
    case 115:
    	((void (*)(_InvokeArgs_115))address)(*((_InvokeArgs_115*)args->mem));
    	break;
    case 116:
    	((void (*)(_InvokeArgs_116))address)(*((_InvokeArgs_116*)args->mem));
    	break;
    case 117:
    	((void (*)(_InvokeArgs_117))address)(*((_InvokeArgs_117*)args->mem));
    	break;
    case 118:
    	((void (*)(_InvokeArgs_118))address)(*((_InvokeArgs_118*)args->mem));
    	break;
    case 119:
    	((void (*)(_InvokeArgs_119))address)(*((_InvokeArgs_119*)args->mem));
    	break;
    case 120:
    	((void (*)(_InvokeArgs_120))address)(*((_InvokeArgs_120*)args->mem));
    	break;
    case 121:
    	((void (*)(_InvokeArgs_121))address)(*((_InvokeArgs_121*)args->mem));
    	break;
    case 122:
    	((void (*)(_InvokeArgs_122))address)(*((_InvokeArgs_122*)args->mem));
    	break;
    case 123:
    	((void (*)(_InvokeArgs_123))address)(*((_InvokeArgs_123*)args->mem));
    	break;
    case 124:
    	((void (*)(_InvokeArgs_124))address)(*((_InvokeArgs_124*)args->mem));
    	break;
    case 125:
    	((void (*)(_InvokeArgs_125))address)(*((_InvokeArgs_125*)args->mem));
    	break;
    case 126:
    	((void (*)(_InvokeArgs_126))address)(*((_InvokeArgs_126*)args->mem));
    	break;
    case 127:
    	((void (*)(_InvokeArgs_127))address)(*((_InvokeArgs_127*)args->mem));
    	break;
    case 128:
    	((void (*)(_InvokeArgs_128))address)(*((_InvokeArgs_128*)args->mem));
    	break;
    case 129:
    	((void (*)(_InvokeArgs_129))address)(*((_InvokeArgs_129*)args->mem));
    	break;
    case 130:
    	((void (*)(_InvokeArgs_130))address)(*((_InvokeArgs_130*)args->mem));
    	break;
    case 131:
    	((void (*)(_InvokeArgs_131))address)(*((_InvokeArgs_131*)args->mem));
    	break;
    case 132:
    	((void (*)(_InvokeArgs_132))address)(*((_InvokeArgs_132*)args->mem));
    	break;
    case 133:
    	((void (*)(_InvokeArgs_133))address)(*((_InvokeArgs_133*)args->mem));
    	break;
    case 134:
    	((void (*)(_InvokeArgs_134))address)(*((_InvokeArgs_134*)args->mem));
    	break;
    case 135:
    	((void (*)(_InvokeArgs_135))address)(*((_InvokeArgs_135*)args->mem));
    	break;
    case 136:
    	((void (*)(_InvokeArgs_136))address)(*((_InvokeArgs_136*)args->mem));
    	break;
    case 137:
    	((void (*)(_InvokeArgs_137))address)(*((_InvokeArgs_137*)args->mem));
    	break;
    case 138:
    	((void (*)(_InvokeArgs_138))address)(*((_InvokeArgs_138*)args->mem));
    	break;
    case 139:
    	((void (*)(_InvokeArgs_139))address)(*((_InvokeArgs_139*)args->mem));
    	break;
    case 140:
    	((void (*)(_InvokeArgs_140))address)(*((_InvokeArgs_140*)args->mem));
    	break;
    case 141:
    	((void (*)(_InvokeArgs_141))address)(*((_InvokeArgs_141*)args->mem));
    	break;
    case 142:
    	((void (*)(_InvokeArgs_142))address)(*((_InvokeArgs_142*)args->mem));
    	break;
    case 143:
    	((void (*)(_InvokeArgs_143))address)(*((_InvokeArgs_143*)args->mem));
    	break;
    case 144:
    	((void (*)(_InvokeArgs_144))address)(*((_InvokeArgs_144*)args->mem));
    	break;
    case 145:
    	((void (*)(_InvokeArgs_145))address)(*((_InvokeArgs_145*)args->mem));
    	break;
    case 146:
    	((void (*)(_InvokeArgs_146))address)(*((_InvokeArgs_146*)args->mem));
    	break;
    case 147:
    	((void (*)(_InvokeArgs_147))address)(*((_InvokeArgs_147*)args->mem));
    	break;
    case 148:
    	((void (*)(_InvokeArgs_148))address)(*((_InvokeArgs_148*)args->mem));
    	break;
    case 149:
    	((void (*)(_InvokeArgs_149))address)(*((_InvokeArgs_149*)args->mem));
    	break;
    case 150:
    	((void (*)(_InvokeArgs_150))address)(*((_InvokeArgs_150*)args->mem));
    	break;
    case 151:
    	((void (*)(_InvokeArgs_151))address)(*((_InvokeArgs_151*)args->mem));
    	break;
    case 152:
    	((void (*)(_InvokeArgs_152))address)(*((_InvokeArgs_152*)args->mem));
    	break;
    case 153:
    	((void (*)(_InvokeArgs_153))address)(*((_InvokeArgs_153*)args->mem));
    	break;
    case 154:
    	((void (*)(_InvokeArgs_154))address)(*((_InvokeArgs_154*)args->mem));
    	break;
    case 155:
    	((void (*)(_InvokeArgs_155))address)(*((_InvokeArgs_155*)args->mem));
    	break;
    case 156:
    	((void (*)(_InvokeArgs_156))address)(*((_InvokeArgs_156*)args->mem));
    	break;
    case 157:
    	((void (*)(_InvokeArgs_157))address)(*((_InvokeArgs_157*)args->mem));
    	break;
    case 158:
    	((void (*)(_InvokeArgs_158))address)(*((_InvokeArgs_158*)args->mem));
    	break;
    case 159:
    	((void (*)(_InvokeArgs_159))address)(*((_InvokeArgs_159*)args->mem));
    	break;
    case 160:
    	((void (*)(_InvokeArgs_160))address)(*((_InvokeArgs_160*)args->mem));
    	break;
    case 161:
    	((void (*)(_InvokeArgs_161))address)(*((_InvokeArgs_161*)args->mem));
    	break;
    case 162:
    	((void (*)(_InvokeArgs_162))address)(*((_InvokeArgs_162*)args->mem));
    	break;
    case 163:
    	((void (*)(_InvokeArgs_163))address)(*((_InvokeArgs_163*)args->mem));
    	break;
    case 164:
    	((void (*)(_InvokeArgs_164))address)(*((_InvokeArgs_164*)args->mem));
    	break;
    case 165:
    	((void (*)(_InvokeArgs_165))address)(*((_InvokeArgs_165*)args->mem));
    	break;
    case 166:
    	((void (*)(_InvokeArgs_166))address)(*((_InvokeArgs_166*)args->mem));
    	break;
    case 167:
    	((void (*)(_InvokeArgs_167))address)(*((_InvokeArgs_167*)args->mem));
    	break;
    case 168:
    	((void (*)(_InvokeArgs_168))address)(*((_InvokeArgs_168*)args->mem));
    	break;
    case 169:
    	((void (*)(_InvokeArgs_169))address)(*((_InvokeArgs_169*)args->mem));
    	break;
    case 170:
    	((void (*)(_InvokeArgs_170))address)(*((_InvokeArgs_170*)args->mem));
    	break;
    case 171:
    	((void (*)(_InvokeArgs_171))address)(*((_InvokeArgs_171*)args->mem));
    	break;
    case 172:
    	((void (*)(_InvokeArgs_172))address)(*((_InvokeArgs_172*)args->mem));
    	break;
    case 173:
    	((void (*)(_InvokeArgs_173))address)(*((_InvokeArgs_173*)args->mem));
    	break;
    case 174:
    	((void (*)(_InvokeArgs_174))address)(*((_InvokeArgs_174*)args->mem));
    	break;
    case 175:
    	((void (*)(_InvokeArgs_175))address)(*((_InvokeArgs_175*)args->mem));
    	break;
    case 176:
    	((void (*)(_InvokeArgs_176))address)(*((_InvokeArgs_176*)args->mem));
    	break;
    case 177:
    	((void (*)(_InvokeArgs_177))address)(*((_InvokeArgs_177*)args->mem));
    	break;
    case 178:
    	((void (*)(_InvokeArgs_178))address)(*((_InvokeArgs_178*)args->mem));
    	break;
    case 179:
    	((void (*)(_InvokeArgs_179))address)(*((_InvokeArgs_179*)args->mem));
    	break;
    case 180:
    	((void (*)(_InvokeArgs_180))address)(*((_InvokeArgs_180*)args->mem));
    	break;
    case 181:
    	((void (*)(_InvokeArgs_181))address)(*((_InvokeArgs_181*)args->mem));
    	break;
    case 182:
    	((void (*)(_InvokeArgs_182))address)(*((_InvokeArgs_182*)args->mem));
    	break;
    case 183:
    	((void (*)(_InvokeArgs_183))address)(*((_InvokeArgs_183*)args->mem));
    	break;
    case 184:
    	((void (*)(_InvokeArgs_184))address)(*((_InvokeArgs_184*)args->mem));
    	break;
    case 185:
    	((void (*)(_InvokeArgs_185))address)(*((_InvokeArgs_185*)args->mem));
    	break;
    case 186:
    	((void (*)(_InvokeArgs_186))address)(*((_InvokeArgs_186*)args->mem));
    	break;
    case 187:
    	((void (*)(_InvokeArgs_187))address)(*((_InvokeArgs_187*)args->mem));
    	break;
    case 188:
    	((void (*)(_InvokeArgs_188))address)(*((_InvokeArgs_188*)args->mem));
    	break;
    case 189:
    	((void (*)(_InvokeArgs_189))address)(*((_InvokeArgs_189*)args->mem));
    	break;
    case 190:
    	((void (*)(_InvokeArgs_190))address)(*((_InvokeArgs_190*)args->mem));
    	break;
    case 191:
    	((void (*)(_InvokeArgs_191))address)(*((_InvokeArgs_191*)args->mem));
    	break;
    case 192:
    	((void (*)(_InvokeArgs_192))address)(*((_InvokeArgs_192*)args->mem));
    	break;
    case 193:
    	((void (*)(_InvokeArgs_193))address)(*((_InvokeArgs_193*)args->mem));
    	break;
    case 194:
    	((void (*)(_InvokeArgs_194))address)(*((_InvokeArgs_194*)args->mem));
    	break;
    case 195:
    	((void (*)(_InvokeArgs_195))address)(*((_InvokeArgs_195*)args->mem));
    	break;
    case 196:
    	((void (*)(_InvokeArgs_196))address)(*((_InvokeArgs_196*)args->mem));
    	break;
    case 197:
    	((void (*)(_InvokeArgs_197))address)(*((_InvokeArgs_197*)args->mem));
    	break;
    case 198:
    	((void (*)(_InvokeArgs_198))address)(*((_InvokeArgs_198*)args->mem));
    	break;
    case 199:
    	((void (*)(_InvokeArgs_199))address)(*((_InvokeArgs_199*)args->mem));
    	break;
    case 200:
    	((void (*)(_InvokeArgs_200))address)(*((_InvokeArgs_200*)args->mem));
    	break;
    case 201:
    	((void (*)(_InvokeArgs_201))address)(*((_InvokeArgs_201*)args->mem));
    	break;
    case 202:
    	((void (*)(_InvokeArgs_202))address)(*((_InvokeArgs_202*)args->mem));
    	break;
    case 203:
    	((void (*)(_InvokeArgs_203))address)(*((_InvokeArgs_203*)args->mem));
    	break;
    case 204:
    	((void (*)(_InvokeArgs_204))address)(*((_InvokeArgs_204*)args->mem));
    	break;
    case 205:
    	((void (*)(_InvokeArgs_205))address)(*((_InvokeArgs_205*)args->mem));
    	break;
    case 206:
    	((void (*)(_InvokeArgs_206))address)(*((_InvokeArgs_206*)args->mem));
    	break;
    case 207:
    	((void (*)(_InvokeArgs_207))address)(*((_InvokeArgs_207*)args->mem));
    	break;
    case 208:
    	((void (*)(_InvokeArgs_208))address)(*((_InvokeArgs_208*)args->mem));
    	break;
    case 209:
    	((void (*)(_InvokeArgs_209))address)(*((_InvokeArgs_209*)args->mem));
    	break;
    case 210:
    	((void (*)(_InvokeArgs_210))address)(*((_InvokeArgs_210*)args->mem));
    	break;
    case 211:
    	((void (*)(_InvokeArgs_211))address)(*((_InvokeArgs_211*)args->mem));
    	break;
    case 212:
    	((void (*)(_InvokeArgs_212))address)(*((_InvokeArgs_212*)args->mem));
    	break;
    case 213:
    	((void (*)(_InvokeArgs_213))address)(*((_InvokeArgs_213*)args->mem));
    	break;
    case 214:
    	((void (*)(_InvokeArgs_214))address)(*((_InvokeArgs_214*)args->mem));
    	break;
    case 215:
    	((void (*)(_InvokeArgs_215))address)(*((_InvokeArgs_215*)args->mem));
    	break;
    case 216:
    	((void (*)(_InvokeArgs_216))address)(*((_InvokeArgs_216*)args->mem));
    	break;
    case 217:
    	((void (*)(_InvokeArgs_217))address)(*((_InvokeArgs_217*)args->mem));
    	break;
    case 218:
    	((void (*)(_InvokeArgs_218))address)(*((_InvokeArgs_218*)args->mem));
    	break;
    case 219:
    	((void (*)(_InvokeArgs_219))address)(*((_InvokeArgs_219*)args->mem));
    	break;
    case 220:
    	((void (*)(_InvokeArgs_220))address)(*((_InvokeArgs_220*)args->mem));
    	break;
    case 221:
    	((void (*)(_InvokeArgs_221))address)(*((_InvokeArgs_221*)args->mem));
    	break;
    case 222:
    	((void (*)(_InvokeArgs_222))address)(*((_InvokeArgs_222*)args->mem));
    	break;
    case 223:
    	((void (*)(_InvokeArgs_223))address)(*((_InvokeArgs_223*)args->mem));
    	break;
    case 224:
    	((void (*)(_InvokeArgs_224))address)(*((_InvokeArgs_224*)args->mem));
    	break;
    case 225:
    	((void (*)(_InvokeArgs_225))address)(*((_InvokeArgs_225*)args->mem));
    	break;
    case 226:
    	((void (*)(_InvokeArgs_226))address)(*((_InvokeArgs_226*)args->mem));
    	break;
    case 227:
    	((void (*)(_InvokeArgs_227))address)(*((_InvokeArgs_227*)args->mem));
    	break;
    case 228:
    	((void (*)(_InvokeArgs_228))address)(*((_InvokeArgs_228*)args->mem));
    	break;
    case 229:
    	((void (*)(_InvokeArgs_229))address)(*((_InvokeArgs_229*)args->mem));
    	break;
    case 230:
    	((void (*)(_InvokeArgs_230))address)(*((_InvokeArgs_230*)args->mem));
    	break;
    case 231:
    	((void (*)(_InvokeArgs_231))address)(*((_InvokeArgs_231*)args->mem));
    	break;
    case 232:
    	((void (*)(_InvokeArgs_232))address)(*((_InvokeArgs_232*)args->mem));
    	break;
    case 233:
    	((void (*)(_InvokeArgs_233))address)(*((_InvokeArgs_233*)args->mem));
    	break;
    case 234:
    	((void (*)(_InvokeArgs_234))address)(*((_InvokeArgs_234*)args->mem));
    	break;
    case 235:
    	((void (*)(_InvokeArgs_235))address)(*((_InvokeArgs_235*)args->mem));
    	break;
    case 236:
    	((void (*)(_InvokeArgs_236))address)(*((_InvokeArgs_236*)args->mem));
    	break;
    case 237:
    	((void (*)(_InvokeArgs_237))address)(*((_InvokeArgs_237*)args->mem));
    	break;
    case 238:
    	((void (*)(_InvokeArgs_238))address)(*((_InvokeArgs_238*)args->mem));
    	break;
    case 239:
    	((void (*)(_InvokeArgs_239))address)(*((_InvokeArgs_239*)args->mem));
    	break;
    case 240:
    	((void (*)(_InvokeArgs_240))address)(*((_InvokeArgs_240*)args->mem));
    	break;
    case 241:
    	((void (*)(_InvokeArgs_241))address)(*((_InvokeArgs_241*)args->mem));
    	break;
    case 242:
    	((void (*)(_InvokeArgs_242))address)(*((_InvokeArgs_242*)args->mem));
    	break;
    case 243:
    	((void (*)(_InvokeArgs_243))address)(*((_InvokeArgs_243*)args->mem));
    	break;
    case 244:
    	((void (*)(_InvokeArgs_244))address)(*((_InvokeArgs_244*)args->mem));
    	break;
    case 245:
    	((void (*)(_InvokeArgs_245))address)(*((_InvokeArgs_245*)args->mem));
    	break;
    case 246:
    	((void (*)(_InvokeArgs_246))address)(*((_InvokeArgs_246*)args->mem));
    	break;
    case 247:
    	((void (*)(_InvokeArgs_247))address)(*((_InvokeArgs_247*)args->mem));
    	break;
    case 248:
    	((void (*)(_InvokeArgs_248))address)(*((_InvokeArgs_248*)args->mem));
    	break;
    case 249:
    	((void (*)(_InvokeArgs_249))address)(*((_InvokeArgs_249*)args->mem));
    	break;
    case 250:
    	((void (*)(_InvokeArgs_250))address)(*((_InvokeArgs_250*)args->mem));
    	break;
    case 251:
    	((void (*)(_InvokeArgs_251))address)(*((_InvokeArgs_251*)args->mem));
    	break;
    case 252:
    	((void (*)(_InvokeArgs_252))address)(*((_InvokeArgs_252*)args->mem));
    	break;
    case 253:
    	((void (*)(_InvokeArgs_253))address)(*((_InvokeArgs_253*)args->mem));
    	break;
    case 254:
    	((void (*)(_InvokeArgs_254))address)(*((_InvokeArgs_254*)args->mem));
    	break;
    case 255:
    	((void (*)(_InvokeArgs_255))address)(*((_InvokeArgs_255*)args->mem));
    	break;
    case 256:
    	((void (*)(_InvokeArgs_256))address)(*((_InvokeArgs_256*)args->mem));
    	break;
    default:
	((void (*)())address)();
	break;
  }
}

guint8
golem_invoke_guint8(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(guint8,address,args)
}

guint
golem_invoke_guint(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(guint,address,args)
}

guint64
golem_invoke_guint64(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(guint64,address,args)
}

gulong
golem_invoke_gulong(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(gulong,address,args)
}

gint8
golem_invoke_gint8(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(gint8,address,args)
}

gint
golem_invoke_gint(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(gint,address,args)
}

gint64
golem_invoke_gint64(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(gint64,address,args)
}

glong
golem_invoke_glong(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(glong,address,args)
}

gfloat
golem_invoke_gfloat(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(gfloat,address,args)
}

gdouble
golem_invoke_gdouble(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(gdouble,address,args)
}

gpointer
golem_invoke_gpointer(gpointer address,GolemArgs * args)
{
  GOLEM_INVOKE_TYPE(gpointer,address,args)
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
