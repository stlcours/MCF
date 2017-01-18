// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2017, LH_Mouse. All wrongs reserved.

#ifndef __MCFCRT_EXT_REP_STOS_H_
#define __MCFCRT_EXT_REP_STOS_H_

#include "../env/_crtdef.h"

#ifndef __MCFCRT_REP_STOS_INLINE_OR_EXTERN
#	define __MCFCRT_REP_STOS_INLINE_OR_EXTERN     __attribute__((__gnu_inline__)) extern inline
#endif

_MCFCRT_EXTERN_C_BEGIN

__MCFCRT_REP_STOS_INLINE_OR_EXTERN void *_MCFCRT_rep_stosb(void *__s, _MCFCRT_STD uint8_t __c, _MCFCRT_STD size_t __n) _MCFCRT_NOEXCEPT {
	void *__p = __s;
	_MCFCRT_STD size_t __unused;
	__asm__ (
		"rep stosb \n"
		: "=m"(*(char *)__s), "+D"(__p), "=c"(__unused)
		: "a"(__c), "c"(__n)
	);
	return __p;
}
__MCFCRT_REP_STOS_INLINE_OR_EXTERN void *_MCFCRT_rep_stosw(void *__s, _MCFCRT_STD uint16_t __c, _MCFCRT_STD size_t __n) _MCFCRT_NOEXCEPT {
	void *__p = __s;
	_MCFCRT_STD size_t __unused;
	__asm__ (
		"rep stosw \n"
		: "=m"(*(char *)__s), "+D"(__p), "=c"(__unused)
		: "a"(__c), "c"(__n)
	);
	return __p;
}
__MCFCRT_REP_STOS_INLINE_OR_EXTERN void *_MCFCRT_rep_stosd(void *__s, _MCFCRT_STD uint32_t __c, _MCFCRT_STD size_t __n) _MCFCRT_NOEXCEPT {
	void *__p = __s;
	_MCFCRT_STD size_t __unused;
	__asm__ (
		"rep stosd \n"
		: "=m"(*(char *)__s), "+D"(__p), "=c"(__unused)
		: "a"(__c), "c"(__n)
	);
	return __p;
}
#ifdef _WIN64
__MCFCRT_REP_STOS_INLINE_OR_EXTERN void *_MCFCRT_rep_stosq(void *__s, _MCFCRT_STD uint64_t __c, _MCFCRT_STD size_t __n) _MCFCRT_NOEXCEPT {
	void *__p = __s;
	_MCFCRT_STD size_t __unused;
	__asm__ (
		"rep stosq \n"
		: "=m"(*(char *)__s), "+D"(__p), "=c"(__unused)
		: "a"(__c), "c"(__n)
	);
	return __p;
}
#endif

_MCFCRT_EXTERN_C_END

#endif