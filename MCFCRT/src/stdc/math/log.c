// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2016, LH_Mouse. All wrongs reserved.

#include "../../env/_crtdef.h"
#include "_fpu.h"

static inline long double fpu_log(long double x){
	return __MCFCRT_fyl2x(__MCFCRT_fldln2(), x);
}

float logf(float x){
	return (float)fpu_log(x);
}
double log(double x){
	return (double)fpu_log(x);
}
long double logl(long double x){
	return fpu_log(x);
}
