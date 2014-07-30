// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2014, LH_Mouse. All wrongs reserved.

#include "../../env/_crtdef.h"
#include "../../env/heap.h"

__attribute__((__noinline__)) void *__wrap_realloc(void *p, size_t cb){
	if(p){
		return __MCF_CRT_HeapReAlloc(p, cb, __builtin_return_address(0));
	} else {
		return __MCF_CRT_HeapAlloc(cb, __builtin_return_address(0));
	}
}

void *realloc(void *p, size_t cb)
	__attribute__((__alias__("__wrap_realloc")));
