#include "golem.h"

typedef gint64 (*_golem_cmshl)(gpointer address,GolemCInvoke * invoke);

static gint64 _golem_cmshl_0(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_0)(gint32,gint32,gint32,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_0) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_1(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_1)(gint32,gint32,gint32,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_1) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_2(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_2)(gint32,gint32,gint32,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_2) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_3(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_3)(gint32,gint32,gint32,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_3) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_4(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_4)(gint32,gint32,gint32,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_4) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_5(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_5)(gint32,gint32,gint32,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_5) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_6(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_6)(gint32,gint32,gint32,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_6) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_7(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_7)(gint32,gint32,gint32,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_7) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_8(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_8)(gint32,gint32,gint32,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_8) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_9(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_9)(gint32,gint32,gint32,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_9) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_10(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_10)(gint32,gint32,gint32,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_10) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_11(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_11)(gint32,gint32,gint32,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_11) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_12(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_12)(gint32,gint32,gint32,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_12) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_13(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_13)(gint32,gint32,gint32,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_13) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_14(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_14)(gint32,gint32,gint32,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_14) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_15(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_15)(gint32,gint32,gint32,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_15) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_16(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_16)(gint32,gint32,gint32,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_16) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_17(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_17)(gint32,gint32,gint32,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_17) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_18(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_18)(gint32,gint32,gint32,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_18) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_19(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_19)(gint32,gint32,gint32,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_19) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_20(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_20)(gint32,gint32,gint32,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_20) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_21(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_21)(gint32,gint32,gint32,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_21) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_22(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_22)(gint32,gint32,gint32,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_22) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_23(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_23)(gint32,gint32,gint32,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_23) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_24(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_24)(gint32,gint32,gint32,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_24) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_25(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_25)(gint32,gint32,gint32,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_25) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_26(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_26)(gint32,gint32,gint32,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_26) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_27(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_27)(gint32,gint32,gint32,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_27) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_28(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_28)(gint32,gint32,gint32,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_28) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_29(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_29)(gint32,gint32,gint32,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_29) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_30(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_30)(gint32,gint32,gint32,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_30) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_31(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_31)(gint32,gint32,gint32,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_31) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_32(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_32)(gint32,gint32,gint64,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_32) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_33(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_33)(gint32,gint32,gint64,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_33) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_34(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_34)(gint32,gint32,gint64,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_34) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_35(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_35)(gint32,gint32,gint64,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_35) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_36(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_36)(gint32,gint32,gint64,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_36) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_37(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_37)(gint32,gint32,gint64,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_37) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_38(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_38)(gint32,gint32,gint64,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_38) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_39(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_39)(gint32,gint32,gint64,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_39) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_40(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_40)(gint32,gint32,gint64,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_40) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_41(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_41)(gint32,gint32,gint64,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_41) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_42(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_42)(gint32,gint32,gint64,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_42) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_43(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_43)(gint32,gint32,gint64,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_43) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_44(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_44)(gint32,gint32,gint64,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_44) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_45(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_45)(gint32,gint32,gint64,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_45) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_46(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_46)(gint32,gint32,gint64,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_46) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_47(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_47)(gint32,gint32,gint64,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_47) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_48(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_48)(gint32,gint32,gint64,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_48) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_49(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_49)(gint32,gint32,gint64,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_49) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_50(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_50)(gint32,gint32,gint64,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_50) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_51(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_51)(gint32,gint32,gint64,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_51) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_52(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_52)(gint32,gint32,gint64,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_52) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_53(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_53)(gint32,gint32,gint64,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_53) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_54(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_54)(gint32,gint32,gint64,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_54) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_55(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_55)(gint32,gint32,gint64,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_55) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_56(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_56)(gint32,gint32,gint64,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_56) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_57(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_57)(gint32,gint32,gint64,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_57) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_58(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_58)(gint32,gint32,gint64,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_58) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_59(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_59)(gint32,gint32,gint64,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_59) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_60(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_60)(gint32,gint32,gint64,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_60) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_61(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_61)(gint32,gint32,gint64,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_61) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_62(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_62)(gint32,gint32,gint64,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_62) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_63(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_63)(gint32,gint32,gint64,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_63) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_64(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_64)(gint32,gint64,gint32,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_64) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_65(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_65)(gint32,gint64,gint32,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_65) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_66(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_66)(gint32,gint64,gint32,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_66) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_67(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_67)(gint32,gint64,gint32,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_67) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_68(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_68)(gint32,gint64,gint32,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_68) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_69(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_69)(gint32,gint64,gint32,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_69) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_70(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_70)(gint32,gint64,gint32,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_70) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_71(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_71)(gint32,gint64,gint32,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_71) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_72(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_72)(gint32,gint64,gint32,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_72) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_73(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_73)(gint32,gint64,gint32,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_73) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_74(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_74)(gint32,gint64,gint32,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_74) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_75(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_75)(gint32,gint64,gint32,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_75) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_76(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_76)(gint32,gint64,gint32,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_76) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_77(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_77)(gint32,gint64,gint32,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_77) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_78(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_78)(gint32,gint64,gint32,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_78) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_79(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_79)(gint32,gint64,gint32,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_79) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_80(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_80)(gint32,gint64,gint32,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_80) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_81(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_81)(gint32,gint64,gint32,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_81) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_82(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_82)(gint32,gint64,gint32,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_82) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_83(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_83)(gint32,gint64,gint32,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_83) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_84(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_84)(gint32,gint64,gint32,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_84) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_85(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_85)(gint32,gint64,gint32,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_85) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_86(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_86)(gint32,gint64,gint32,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_86) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_87(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_87)(gint32,gint64,gint32,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_87) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_88(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_88)(gint32,gint64,gint32,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_88) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_89(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_89)(gint32,gint64,gint32,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_89) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_90(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_90)(gint32,gint64,gint32,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_90) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_91(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_91)(gint32,gint64,gint32,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_91) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_92(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_92)(gint32,gint64,gint32,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_92) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_93(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_93)(gint32,gint64,gint32,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_93) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_94(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_94)(gint32,gint64,gint32,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_94) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_95(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_95)(gint32,gint64,gint32,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_95) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_96(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_96)(gint32,gint64,gint64,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_96) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_97(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_97)(gint32,gint64,gint64,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_97) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_98(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_98)(gint32,gint64,gint64,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_98) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_99(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_99)(gint32,gint64,gint64,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_99) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_100(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_100)(gint32,gint64,gint64,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_100) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_101(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_101)(gint32,gint64,gint64,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_101) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_102(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_102)(gint32,gint64,gint64,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_102) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_103(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_103)(gint32,gint64,gint64,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_103) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_104(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_104)(gint32,gint64,gint64,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_104) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_105(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_105)(gint32,gint64,gint64,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_105) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_106(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_106)(gint32,gint64,gint64,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_106) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_107(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_107)(gint32,gint64,gint64,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_107) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_108(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_108)(gint32,gint64,gint64,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_108) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_109(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_109)(gint32,gint64,gint64,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_109) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_110(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_110)(gint32,gint64,gint64,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_110) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_111(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_111)(gint32,gint64,gint64,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_111) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_112(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_112)(gint32,gint64,gint64,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_112) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_113(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_113)(gint32,gint64,gint64,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_113) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_114(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_114)(gint32,gint64,gint64,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_114) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_115(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_115)(gint32,gint64,gint64,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_115) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_116(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_116)(gint32,gint64,gint64,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_116) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_117(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_117)(gint32,gint64,gint64,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_117) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_118(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_118)(gint32,gint64,gint64,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_118) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_119(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_119)(gint32,gint64,gint64,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_119) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_120(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_120)(gint32,gint64,gint64,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_120) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_121(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_121)(gint32,gint64,gint64,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_121) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_122(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_122)(gint32,gint64,gint64,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_122) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_123(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_123)(gint32,gint64,gint64,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_123) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_124(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_124)(gint32,gint64,gint64,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_124) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_125(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_125)(gint32,gint64,gint64,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_125) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_126(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_126)(gint32,gint64,gint64,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_126) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_127(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_127)(gint32,gint64,gint64,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_127) address)(*((gint32*)(&(invoke->arg0.value_gint32))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_128(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_128)(gint64,gint32,gint32,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_128) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_129(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_129)(gint64,gint32,gint32,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_129) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_130(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_130)(gint64,gint32,gint32,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_130) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_131(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_131)(gint64,gint32,gint32,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_131) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_132(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_132)(gint64,gint32,gint32,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_132) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_133(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_133)(gint64,gint32,gint32,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_133) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_134(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_134)(gint64,gint32,gint32,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_134) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_135(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_135)(gint64,gint32,gint32,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_135) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_136(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_136)(gint64,gint32,gint32,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_136) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_137(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_137)(gint64,gint32,gint32,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_137) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_138(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_138)(gint64,gint32,gint32,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_138) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_139(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_139)(gint64,gint32,gint32,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_139) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_140(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_140)(gint64,gint32,gint32,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_140) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_141(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_141)(gint64,gint32,gint32,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_141) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_142(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_142)(gint64,gint32,gint32,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_142) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_143(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_143)(gint64,gint32,gint32,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_143) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_144(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_144)(gint64,gint32,gint32,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_144) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_145(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_145)(gint64,gint32,gint32,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_145) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_146(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_146)(gint64,gint32,gint32,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_146) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_147(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_147)(gint64,gint32,gint32,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_147) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_148(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_148)(gint64,gint32,gint32,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_148) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_149(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_149)(gint64,gint32,gint32,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_149) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_150(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_150)(gint64,gint32,gint32,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_150) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_151(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_151)(gint64,gint32,gint32,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_151) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_152(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_152)(gint64,gint32,gint32,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_152) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_153(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_153)(gint64,gint32,gint32,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_153) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_154(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_154)(gint64,gint32,gint32,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_154) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_155(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_155)(gint64,gint32,gint32,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_155) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_156(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_156)(gint64,gint32,gint32,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_156) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_157(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_157)(gint64,gint32,gint32,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_157) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_158(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_158)(gint64,gint32,gint32,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_158) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_159(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_159)(gint64,gint32,gint32,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_159) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_160(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_160)(gint64,gint32,gint64,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_160) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_161(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_161)(gint64,gint32,gint64,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_161) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_162(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_162)(gint64,gint32,gint64,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_162) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_163(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_163)(gint64,gint32,gint64,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_163) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_164(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_164)(gint64,gint32,gint64,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_164) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_165(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_165)(gint64,gint32,gint64,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_165) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_166(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_166)(gint64,gint32,gint64,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_166) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_167(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_167)(gint64,gint32,gint64,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_167) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_168(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_168)(gint64,gint32,gint64,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_168) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_169(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_169)(gint64,gint32,gint64,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_169) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_170(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_170)(gint64,gint32,gint64,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_170) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_171(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_171)(gint64,gint32,gint64,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_171) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_172(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_172)(gint64,gint32,gint64,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_172) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_173(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_173)(gint64,gint32,gint64,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_173) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_174(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_174)(gint64,gint32,gint64,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_174) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_175(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_175)(gint64,gint32,gint64,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_175) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_176(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_176)(gint64,gint32,gint64,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_176) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_177(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_177)(gint64,gint32,gint64,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_177) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_178(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_178)(gint64,gint32,gint64,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_178) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_179(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_179)(gint64,gint32,gint64,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_179) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_180(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_180)(gint64,gint32,gint64,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_180) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_181(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_181)(gint64,gint32,gint64,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_181) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_182(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_182)(gint64,gint32,gint64,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_182) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_183(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_183)(gint64,gint32,gint64,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_183) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_184(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_184)(gint64,gint32,gint64,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_184) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_185(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_185)(gint64,gint32,gint64,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_185) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_186(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_186)(gint64,gint32,gint64,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_186) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_187(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_187)(gint64,gint32,gint64,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_187) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_188(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_188)(gint64,gint32,gint64,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_188) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_189(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_189)(gint64,gint32,gint64,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_189) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_190(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_190)(gint64,gint32,gint64,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_190) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_191(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_191)(gint64,gint32,gint64,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_191) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint32*)(&(invoke->arg1.value_gint32))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_192(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_192)(gint64,gint64,gint32,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_192) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_193(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_193)(gint64,gint64,gint32,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_193) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_194(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_194)(gint64,gint64,gint32,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_194) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_195(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_195)(gint64,gint64,gint32,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_195) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_196(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_196)(gint64,gint64,gint32,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_196) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_197(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_197)(gint64,gint64,gint32,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_197) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_198(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_198)(gint64,gint64,gint32,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_198) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_199(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_199)(gint64,gint64,gint32,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_199) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_200(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_200)(gint64,gint64,gint32,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_200) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_201(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_201)(gint64,gint64,gint32,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_201) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_202(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_202)(gint64,gint64,gint32,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_202) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_203(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_203)(gint64,gint64,gint32,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_203) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_204(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_204)(gint64,gint64,gint32,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_204) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_205(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_205)(gint64,gint64,gint32,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_205) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_206(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_206)(gint64,gint64,gint32,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_206) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_207(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_207)(gint64,gint64,gint32,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_207) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_208(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_208)(gint64,gint64,gint32,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_208) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_209(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_209)(gint64,gint64,gint32,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_209) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_210(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_210)(gint64,gint64,gint32,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_210) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_211(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_211)(gint64,gint64,gint32,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_211) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_212(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_212)(gint64,gint64,gint32,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_212) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_213(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_213)(gint64,gint64,gint32,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_213) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_214(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_214)(gint64,gint64,gint32,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_214) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_215(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_215)(gint64,gint64,gint32,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_215) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_216(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_216)(gint64,gint64,gint32,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_216) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_217(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_217)(gint64,gint64,gint32,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_217) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_218(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_218)(gint64,gint64,gint32,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_218) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_219(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_219)(gint64,gint64,gint32,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_219) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_220(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_220)(gint64,gint64,gint32,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_220) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_221(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_221)(gint64,gint64,gint32,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_221) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_222(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_222)(gint64,gint64,gint32,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_222) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_223(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_223)(gint64,gint64,gint32,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_223) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint32*)(&(invoke->arg2.value_gint32))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_224(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_224)(gint64,gint64,gint64,gint32,gint32,gint32,gint32,gint32);
	return ((_func_gen_224) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_225(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_225)(gint64,gint64,gint64,gint32,gint32,gint32,gint32,gint64);
	return ((_func_gen_225) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_226(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_226)(gint64,gint64,gint64,gint32,gint32,gint32,gint64,gint32);
	return ((_func_gen_226) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_227(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_227)(gint64,gint64,gint64,gint32,gint32,gint32,gint64,gint64);
	return ((_func_gen_227) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_228(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_228)(gint64,gint64,gint64,gint32,gint32,gint64,gint32,gint32);
	return ((_func_gen_228) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_229(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_229)(gint64,gint64,gint64,gint32,gint32,gint64,gint32,gint64);
	return ((_func_gen_229) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_230(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_230)(gint64,gint64,gint64,gint32,gint32,gint64,gint64,gint32);
	return ((_func_gen_230) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_231(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_231)(gint64,gint64,gint64,gint32,gint32,gint64,gint64,gint64);
	return ((_func_gen_231) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_232(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_232)(gint64,gint64,gint64,gint32,gint64,gint32,gint32,gint32);
	return ((_func_gen_232) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_233(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_233)(gint64,gint64,gint64,gint32,gint64,gint32,gint32,gint64);
	return ((_func_gen_233) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_234(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_234)(gint64,gint64,gint64,gint32,gint64,gint32,gint64,gint32);
	return ((_func_gen_234) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_235(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_235)(gint64,gint64,gint64,gint32,gint64,gint32,gint64,gint64);
	return ((_func_gen_235) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_236(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_236)(gint64,gint64,gint64,gint32,gint64,gint64,gint32,gint32);
	return ((_func_gen_236) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_237(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_237)(gint64,gint64,gint64,gint32,gint64,gint64,gint32,gint64);
	return ((_func_gen_237) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_238(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_238)(gint64,gint64,gint64,gint32,gint64,gint64,gint64,gint32);
	return ((_func_gen_238) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_239(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_239)(gint64,gint64,gint64,gint32,gint64,gint64,gint64,gint64);
	return ((_func_gen_239) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint32*)(&(invoke->arg3.value_gint32))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_240(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_240)(gint64,gint64,gint64,gint64,gint32,gint32,gint32,gint32);
	return ((_func_gen_240) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_241(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_241)(gint64,gint64,gint64,gint64,gint32,gint32,gint32,gint64);
	return ((_func_gen_241) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_242(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_242)(gint64,gint64,gint64,gint64,gint32,gint32,gint64,gint32);
	return ((_func_gen_242) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_243(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_243)(gint64,gint64,gint64,gint64,gint32,gint32,gint64,gint64);
	return ((_func_gen_243) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_244(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_244)(gint64,gint64,gint64,gint64,gint32,gint64,gint32,gint32);
	return ((_func_gen_244) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_245(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_245)(gint64,gint64,gint64,gint64,gint32,gint64,gint32,gint64);
	return ((_func_gen_245) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_246(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_246)(gint64,gint64,gint64,gint64,gint32,gint64,gint64,gint32);
	return ((_func_gen_246) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_247(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_247)(gint64,gint64,gint64,gint64,gint32,gint64,gint64,gint64);
	return ((_func_gen_247) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint32*)(&(invoke->arg4.value_gint32))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_248(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_248)(gint64,gint64,gint64,gint64,gint64,gint32,gint32,gint32);
	return ((_func_gen_248) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_249(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_249)(gint64,gint64,gint64,gint64,gint64,gint32,gint32,gint64);
	return ((_func_gen_249) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_250(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_250)(gint64,gint64,gint64,gint64,gint64,gint32,gint64,gint32);
	return ((_func_gen_250) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_251(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_251)(gint64,gint64,gint64,gint64,gint64,gint32,gint64,gint64);
	return ((_func_gen_251) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint32*)(&(invoke->arg5.value_gint32))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_252(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_252)(gint64,gint64,gint64,gint64,gint64,gint64,gint32,gint32);
	return ((_func_gen_252) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_253(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_253)(gint64,gint64,gint64,gint64,gint64,gint64,gint32,gint64);
	return ((_func_gen_253) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint32*)(&(invoke->arg6.value_gint32))),*((gint64*)(&(invoke->arg7.value_gint64))));
}

static gint64 _golem_cmshl_254(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_254)(gint64,gint64,gint64,gint64,gint64,gint64,gint64,gint32);
	return ((_func_gen_254) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint32*)(&(invoke->arg7.value_gint32))));
}

static gint64 _golem_cmshl_255(gpointer address,GolemCInvoke * invoke) {
	typedef gint64 (*_func_gen_255)(gint64,gint64,gint64,gint64,gint64,gint64,gint64,gint64);
	return ((_func_gen_255) address)(*((gint64*)(&(invoke->arg0.value_gint64))),*((gint64*)(&(invoke->arg1.value_gint64))),*((gint64*)(&(invoke->arg2.value_gint64))),*((gint64*)(&(invoke->arg3.value_gint64))),*((gint64*)(&(invoke->arg4.value_gint64))),*((gint64*)(&(invoke->arg5.value_gint64))),*((gint64*)(&(invoke->arg6.value_gint64))),*((gint64*)(&(invoke->arg7.value_gint64))));
}


static _golem_cmshl _golem_marshal[2][2][2][2][2][2][2][2] = {{{{{{{{_golem_cmshl_0,_golem_cmshl_1},{_golem_cmshl_2,_golem_cmshl_3}},{{_golem_cmshl_4,_golem_cmshl_5},{_golem_cmshl_6,_golem_cmshl_7}}},{{{_golem_cmshl_8,_golem_cmshl_9},{_golem_cmshl_10,_golem_cmshl_11}},{{_golem_cmshl_12,_golem_cmshl_13},{_golem_cmshl_14,_golem_cmshl_15}}}},{{{{_golem_cmshl_16,_golem_cmshl_17},{_golem_cmshl_18,_golem_cmshl_19}},{{_golem_cmshl_20,_golem_cmshl_21},{_golem_cmshl_22,_golem_cmshl_23}}},{{{_golem_cmshl_24,_golem_cmshl_25},{_golem_cmshl_26,_golem_cmshl_27}},{{_golem_cmshl_28,_golem_cmshl_29},{_golem_cmshl_30,_golem_cmshl_31}}}}},{{{{{_golem_cmshl_32,_golem_cmshl_33},{_golem_cmshl_34,_golem_cmshl_35}},{{_golem_cmshl_36,_golem_cmshl_37},{_golem_cmshl_38,_golem_cmshl_39}}},{{{_golem_cmshl_40,_golem_cmshl_41},{_golem_cmshl_42,_golem_cmshl_43}},{{_golem_cmshl_44,_golem_cmshl_45},{_golem_cmshl_46,_golem_cmshl_47}}}},{{{{_golem_cmshl_48,_golem_cmshl_49},{_golem_cmshl_50,_golem_cmshl_51}},{{_golem_cmshl_52,_golem_cmshl_53},{_golem_cmshl_54,_golem_cmshl_55}}},{{{_golem_cmshl_56,_golem_cmshl_57},{_golem_cmshl_58,_golem_cmshl_59}},{{_golem_cmshl_60,_golem_cmshl_61},{_golem_cmshl_62,_golem_cmshl_63}}}}}},{{{{{{_golem_cmshl_64,_golem_cmshl_65},{_golem_cmshl_66,_golem_cmshl_67}},{{_golem_cmshl_68,_golem_cmshl_69},{_golem_cmshl_70,_golem_cmshl_71}}},{{{_golem_cmshl_72,_golem_cmshl_73},{_golem_cmshl_74,_golem_cmshl_75}},{{_golem_cmshl_76,_golem_cmshl_77},{_golem_cmshl_78,_golem_cmshl_79}}}},{{{{_golem_cmshl_80,_golem_cmshl_81},{_golem_cmshl_82,_golem_cmshl_83}},{{_golem_cmshl_84,_golem_cmshl_85},{_golem_cmshl_86,_golem_cmshl_87}}},{{{_golem_cmshl_88,_golem_cmshl_89},{_golem_cmshl_90,_golem_cmshl_91}},{{_golem_cmshl_92,_golem_cmshl_93},{_golem_cmshl_94,_golem_cmshl_95}}}}},{{{{{_golem_cmshl_96,_golem_cmshl_97},{_golem_cmshl_98,_golem_cmshl_99}},{{_golem_cmshl_100,_golem_cmshl_101},{_golem_cmshl_102,_golem_cmshl_103}}},{{{_golem_cmshl_104,_golem_cmshl_105},{_golem_cmshl_106,_golem_cmshl_107}},{{_golem_cmshl_108,_golem_cmshl_109},{_golem_cmshl_110,_golem_cmshl_111}}}},{{{{_golem_cmshl_112,_golem_cmshl_113},{_golem_cmshl_114,_golem_cmshl_115}},{{_golem_cmshl_116,_golem_cmshl_117},{_golem_cmshl_118,_golem_cmshl_119}}},{{{_golem_cmshl_120,_golem_cmshl_121},{_golem_cmshl_122,_golem_cmshl_123}},{{_golem_cmshl_124,_golem_cmshl_125},{_golem_cmshl_126,_golem_cmshl_127}}}}}}},{{{{{{{_golem_cmshl_128,_golem_cmshl_129},{_golem_cmshl_130,_golem_cmshl_131}},{{_golem_cmshl_132,_golem_cmshl_133},{_golem_cmshl_134,_golem_cmshl_135}}},{{{_golem_cmshl_136,_golem_cmshl_137},{_golem_cmshl_138,_golem_cmshl_139}},{{_golem_cmshl_140,_golem_cmshl_141},{_golem_cmshl_142,_golem_cmshl_143}}}},{{{{_golem_cmshl_144,_golem_cmshl_145},{_golem_cmshl_146,_golem_cmshl_147}},{{_golem_cmshl_148,_golem_cmshl_149},{_golem_cmshl_150,_golem_cmshl_151}}},{{{_golem_cmshl_152,_golem_cmshl_153},{_golem_cmshl_154,_golem_cmshl_155}},{{_golem_cmshl_156,_golem_cmshl_157},{_golem_cmshl_158,_golem_cmshl_159}}}}},{{{{{_golem_cmshl_160,_golem_cmshl_161},{_golem_cmshl_162,_golem_cmshl_163}},{{_golem_cmshl_164,_golem_cmshl_165},{_golem_cmshl_166,_golem_cmshl_167}}},{{{_golem_cmshl_168,_golem_cmshl_169},{_golem_cmshl_170,_golem_cmshl_171}},{{_golem_cmshl_172,_golem_cmshl_173},{_golem_cmshl_174,_golem_cmshl_175}}}},{{{{_golem_cmshl_176,_golem_cmshl_177},{_golem_cmshl_178,_golem_cmshl_179}},{{_golem_cmshl_180,_golem_cmshl_181},{_golem_cmshl_182,_golem_cmshl_183}}},{{{_golem_cmshl_184,_golem_cmshl_185},{_golem_cmshl_186,_golem_cmshl_187}},{{_golem_cmshl_188,_golem_cmshl_189},{_golem_cmshl_190,_golem_cmshl_191}}}}}},{{{{{{_golem_cmshl_192,_golem_cmshl_193},{_golem_cmshl_194,_golem_cmshl_195}},{{_golem_cmshl_196,_golem_cmshl_197},{_golem_cmshl_198,_golem_cmshl_199}}},{{{_golem_cmshl_200,_golem_cmshl_201},{_golem_cmshl_202,_golem_cmshl_203}},{{_golem_cmshl_204,_golem_cmshl_205},{_golem_cmshl_206,_golem_cmshl_207}}}},{{{{_golem_cmshl_208,_golem_cmshl_209},{_golem_cmshl_210,_golem_cmshl_211}},{{_golem_cmshl_212,_golem_cmshl_213},{_golem_cmshl_214,_golem_cmshl_215}}},{{{_golem_cmshl_216,_golem_cmshl_217},{_golem_cmshl_218,_golem_cmshl_219}},{{_golem_cmshl_220,_golem_cmshl_221},{_golem_cmshl_222,_golem_cmshl_223}}}}},{{{{{_golem_cmshl_224,_golem_cmshl_225},{_golem_cmshl_226,_golem_cmshl_227}},{{_golem_cmshl_228,_golem_cmshl_229},{_golem_cmshl_230,_golem_cmshl_231}}},{{{_golem_cmshl_232,_golem_cmshl_233},{_golem_cmshl_234,_golem_cmshl_235}},{{_golem_cmshl_236,_golem_cmshl_237},{_golem_cmshl_238,_golem_cmshl_239}}}},{{{{_golem_cmshl_240,_golem_cmshl_241},{_golem_cmshl_242,_golem_cmshl_243}},{{_golem_cmshl_244,_golem_cmshl_245},{_golem_cmshl_246,_golem_cmshl_247}}},{{{_golem_cmshl_248,_golem_cmshl_249},{_golem_cmshl_250,_golem_cmshl_251}},{{_golem_cmshl_252,_golem_cmshl_253},{_golem_cmshl_254,_golem_cmshl_255}}}}}}}};

static GolemCArgument *
_golem_cinvoke_get_argument(GolemCInvoke * invoke)
{
  switch(invoke->count)
  {
    case 0:
      return &(invoke->arg0);
    case 1:
      return &(invoke->arg1);
    case 2:
      return &(invoke->arg2);
    case 3:
      return &(invoke->arg3);
    case 4:
      return &(invoke->arg4);
    case 5:
      return &(invoke->arg5);
    case 6:
      return &(invoke->arg6);
    case 7:
      return &(invoke->arg7);
    default:
      return NULL;
  }
}

#define GOLEM_CTYPE_INDEX(type) (sizeof(type) <= 4 ? 0 : 1)

GolemCInvoke *
golem_cinvoke_new(GType return_type,gboolean return_const)
{
  GolemCInvoke * invoke = g_new0(GolemCInvoke,1);
  invoke->return_type = return_type;
  invoke->return_const = return_const;
  return invoke;
}

void
golem_cinvoke_push_int(GolemCInvoke * invoke,gint32 value)
{
  g_return_if_fail(invoke->count < 8);
  GolemCArgument * arg = _golem_cinvoke_get_argument(invoke);
  invoke->indexes[invoke->count] = GOLEM_CTYPE_INDEX(gint32);
  arg->value_gint32 = value;
  invoke->count ++;
}

void
golem_cinvoke_push_int64(GolemCInvoke * invoke,gint64 value)
{
  g_return_if_fail(invoke->count < 8);
  GolemCArgument * arg = _golem_cinvoke_get_argument(invoke);
  invoke->indexes[invoke->count] = GOLEM_CTYPE_INDEX(gint64);
  arg->value_gint64 = value;
  invoke->count ++;
}

void
golem_cinvoke_push_uint(GolemCInvoke * invoke,guint32 value)
{
  g_return_if_fail(invoke->count < 8);
  GolemCArgument * arg = _golem_cinvoke_get_argument(invoke);
  invoke->indexes[invoke->count] = GOLEM_CTYPE_INDEX(guint32);
  arg->value_guint32 = value;
  invoke->count ++;
}

void
golem_cinvoke_push_uint64(GolemCInvoke * invoke,guint64 value)
{
  g_return_if_fail(invoke->count < 8);
  GolemCArgument * arg = _golem_cinvoke_get_argument(invoke);
  invoke->indexes[invoke->count] = GOLEM_CTYPE_INDEX(guint64);
  arg->value_guint64 = value;
  invoke->count ++;
}

void
golem_cinvoke_push_float(GolemCInvoke * invoke,gfloat value)
{
  g_return_if_fail(invoke->count < 8);
  GolemCArgument * arg = _golem_cinvoke_get_argument(invoke);
  invoke->indexes[invoke->count] = GOLEM_CTYPE_INDEX(gfloat);
  arg->value_gfloat = value;
  invoke->count ++;
}

void
golem_cinvoke_push_double(GolemCInvoke * invoke,gdouble value)
{
  g_return_if_fail(invoke->count < 8);
  GolemCArgument * arg = _golem_cinvoke_get_argument(invoke);
  invoke->indexes[invoke->count] = GOLEM_CTYPE_INDEX(gdouble);
  arg->value_gdouble = value;
  invoke->count ++;
}

void
golem_cinvoke_push_pointer(GolemCInvoke * invoke,gpointer value)
{
  g_return_if_fail(invoke->count < 8);
  GolemCArgument * arg = _golem_cinvoke_get_argument(invoke);
  invoke->indexes[invoke->count] = GOLEM_CTYPE_INDEX(gpointer);
  arg->value_gpointer = value;
  invoke->count ++;
}

void
golem_cinvoke_push_value(GolemCInvoke * invoke,const GValue * value)
{
  g_return_if_fail(G_VALUE_TYPE(value) != G_TYPE_NONE);
  GType fundamental = G_TYPE_FUNDAMENTAL(G_VALUE_TYPE(value));
  switch(fundamental)
  {
    case G_TYPE_BOOLEAN:
      golem_cinvoke_push_int(invoke,g_value_get_boolean(value));
      break;
    case G_TYPE_CHAR:
      golem_cinvoke_push_int(invoke,g_value_get_schar(value));
      break;
    case G_TYPE_INT:
      golem_cinvoke_push_int(invoke,g_value_get_int(value));
      break;
    case G_TYPE_INT64:
      golem_cinvoke_push_int64(invoke,g_value_get_int64(value));
      break;
    case G_TYPE_UCHAR:
      golem_cinvoke_push_uint(invoke,g_value_get_uchar(value));
      break;
    case G_TYPE_UINT:
      golem_cinvoke_push_uint(invoke,g_value_get_uint(value));
      break;
    case G_TYPE_UINT64:
      golem_cinvoke_push_uint64(invoke,g_value_get_uint64(value));
      break;
    case G_TYPE_FLOAT:
      golem_cinvoke_push_float(invoke,g_value_get_float(value));
      break;
    case G_TYPE_DOUBLE:
      golem_cinvoke_push_double(invoke,g_value_get_double(value));
      break;
    case G_TYPE_POINTER:
      golem_cinvoke_push_pointer(invoke,g_value_get_pointer(value));
      break;
    case G_TYPE_STRING:
      golem_cinvoke_push_pointer(invoke,(gpointer)g_value_get_string(value));
      break;
    case G_TYPE_BOXED:
      if(G_VALUE_TYPE(value) == G_TYPE_ARRAY)
	{
	  GArray * array = g_value_get_boxed(value);
	  if(array)
	    golem_cinvoke_push_pointer(invoke,array->data);
	  else
	    golem_cinvoke_push_pointer(invoke,NULL);
	}
      else
	{
	  golem_cinvoke_push_pointer(invoke,g_value_get_boxed(value));
	}
      break;
    case G_TYPE_OBJECT:
      golem_cinvoke_push_pointer(invoke,g_value_get_object(value));
      break;
    case G_TYPE_ENUM:
      golem_cinvoke_push_int(invoke,g_value_get_enum(value));
      break;
    case G_TYPE_FLAGS:
      golem_cinvoke_push_uint(invoke,g_value_get_flags(value));
      break;
    default:
      {
	if(G_VALUE_HOLDS_GTYPE(value))
	  {
	    golem_cinvoke_push_int(invoke,g_value_get_gtype(value));
	  }
	else
	  {
	    g_print("No type found:%s\n",G_VALUE_TYPE_NAME(value));
	  }
      }
      break;
  }
}

void
golem_cinvoke_invoke(GolemCInvoke * invoke,gpointer address,GValue * result)
{
  g_return_if_fail(invoke != NULL);
  g_return_if_fail(address != NULL);
  g_return_if_fail(result != NULL);
  _golem_cmshl marshal = _golem_marshal[invoke->indexes[0]][invoke->indexes[1]][invoke->indexes[2]][invoke->indexes[3]][invoke->indexes[4]][invoke->indexes[5]][invoke->indexes[6]][invoke->indexes[7]];
  if(invoke->return_type == G_TYPE_NONE)
    {
      marshal(address,invoke);
      g_value_init(result,G_TYPE_INT);
      g_value_set_int(result,0);
    }
  else
    {
      gint64 return_int64 = marshal(address,invoke);
      GType fundamental = G_TYPE_FUNDAMENTAL(invoke->return_type);
      g_value_init(result,invoke->return_type);
      switch(fundamental)
      {
        case G_TYPE_BOOLEAN:
          g_value_set_boolean(result,((GolemCArgument*)&return_int64)->value_gint32);
          break;
        case G_TYPE_CHAR:
          g_value_set_schar(result,((GolemCArgument*)&return_int64)->value_gint32);
          break;
        case G_TYPE_INT:
          g_value_set_int(result,((GolemCArgument*)&return_int64)->value_gint32);
          break;
        case G_TYPE_INT64:
          g_value_set_int64(result,((GolemCArgument*)&return_int64)->value_gint64);
          break;
        case G_TYPE_UCHAR:
          g_value_set_uchar(result,((GolemCArgument*)&return_int64)->value_guint32);
          break;
        case G_TYPE_UINT:
          g_value_set_uint(result,((GolemCArgument*)&return_int64)->value_guint32);
          break;
        case G_TYPE_UINT64:
          g_value_set_uint64(result,((GolemCArgument*)&return_int64)->value_guint64);
          break;
        case G_TYPE_FLOAT:
          g_value_set_float(result,((GolemCArgument*)&return_int64)->value_gfloat);
          break;
        case G_TYPE_DOUBLE:
          g_value_set_double(result,((GolemCArgument*)&return_int64)->value_gdouble);
          break;
        case G_TYPE_POINTER:
          g_value_set_pointer(result,((GolemCArgument*)&return_int64)->value_gpointer);
          break;
        case G_TYPE_STRING:
          if(invoke->return_const){
              g_value_set_string(result,(const gchar*)((GolemCArgument*)&return_int64)->value_gpointer);
          }
          else {
              g_value_take_string(result,(gchar*)((GolemCArgument*)&return_int64)->value_gpointer);
          }
          break;
        case G_TYPE_BOXED:
          if(invoke->return_const){
	      g_value_set_boxed(result,((GolemCArgument*)&return_int64)->value_gpointer);
	  }
	  else {
	      g_value_take_boxed(result,((GolemCArgument*)&return_int64)->value_gpointer);
	  }
          break;
        case G_TYPE_OBJECT:
          if(invoke->return_const){
	      g_value_set_object(result,((GolemCArgument*)&return_int64)->value_gpointer);
	  }
	  else {
	      g_value_take_object(result,((GolemCArgument*)&return_int64)->value_gpointer);
	  }
          break;
        case G_TYPE_ENUM:
	  g_value_set_enum(result,((GolemCArgument*)&return_int64)->value_gint32);
          break;
        case G_TYPE_FLAGS:
          g_value_set_flags(result,((GolemCArgument*)&return_int64)->value_guint32);
          break;
      }
    }
}

void
golem_cinvoke_free(GolemCInvoke * invoke)
{
  g_free(invoke);
}
