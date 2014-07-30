// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2014, LH_Mouse. All wrongs reserved.

#include "../../env/_crtdef.h"
#include "_mathasm.h"

float fmaxf(float x, float y){
	register float ret;
	uintptr_t unused;
	__asm__ __volatile__(
#ifdef _WIN64
		"movss xmm0, dword ptr[%3] \n"
		"movss xmm1, xmm0 \n"
		"movss xmm2, dword ptr[%4] \n"
		"cmpss xmm1, xmm2, 6 \n"
		"xorps xmm0, xmm2 \n"
		"andps xmm0, xmm1 \n"
		"xorps xmm0, xmm2 \n"
#else
		"fld dword ptr[%3] \n"
		"fcomp dword ptr[%4] \n"
		"fstsw ax \n"
		"and ah, 0x41 \n"
		"neg ah \n"
		"sbb eax, eax \n"
		"xor %4, %3 \n"
		"and %4, eax \n"
		"xor %4, %3 \n"
		"fld dword ptr[%4] \n"
#endif
		: "=r"(unused), "=r"(unused), __MCF_FLT_RET_CONS(ret)
		: "0"(&x), "1"(&y)
		: "ax"
	);
	return ret;
}

double fmax(double x, double y){
	register double ret;
	uintptr_t unused;
	__asm__ __volatile__(
#ifdef _WIN64
		"movsd xmm0, qword ptr[%3] \n"
		"movsd xmm1, xmm0 \n"
		"movsd xmm2, qword ptr[%4] \n"
		"cmpsd xmm1, xmm2, 6 \n"
		"xorpd xmm0, xmm2 \n"
		"andpd xmm0, xmm1 \n"
		"xorpd xmm0, xmm2 \n"
#else
		"fld qword ptr[%3] \n"
		"fcomp qword ptr[%4] \n"
		"fstsw ax \n"
		"and ah, 0x41 \n"
		"neg ah \n"
		"sbb eax, eax \n"
		"xor %4, %3 \n"
		"and %4, eax \n"
		"xor %4, %3 \n"
		"fld qword ptr[%4] \n"
#endif
		: "=r"(unused), "=r"(unused), __MCF_DBL_RET_CONS(ret)
		: "0"(&x), "1"(&y)
		: "ax"
	);
	return ret;
}

__MCF_LDBL_DECL(fmaxl, long double x, long double y){
	register long double ret;
	uintptr_t unused;
	__asm__ __volatile__(
		"fld tbyte ptr[%4] \n"
		"fld tbyte ptr[%3] \n"
		"fcompp \n"
		"fstsw ax \n"
		"and ah, 0x41 \n"
		"neg ah \n"
#ifdef _WIN64
		"sbb rax, rax \n"
		"xor %4, %3 \n"
		"and %4, rax \n"
		"xor %4, %3 \n"
#else
		"sbb eax, eax \n"
		"xor %4, %3 \n"
		"and %4, eax \n"
		"xor %4, %3 \n"
#endif
		__MCF_LDBL_RET_MEM("%4", "a")
		: "=r"(unused), "=r"(unused), __MCF_LDBL_RET_CONS(ret)
		: "0"(&x), "1"(&y), __MCF_LDBL_RET_CONS_IN()
		: "ax"
	);
	__MCF_LDBL_RETURN(ret);
}
