// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2018, LH_Mouse. All wrongs reserved.

#include "_UniqueNtHandle.hpp"
#include <ntdef.h>

extern "C" {

__attribute__((__dllimport__, __stdcall__))
extern NTSTATUS NtClose(HANDLE hObject) noexcept;

}

namespace MCF {

template class UniqueHandle<Impl_UniqueNtHandle::NtHandleCloser>;

namespace Impl_UniqueNtHandle {
	void NtHandleCloser::operator()(Handle hObject) const noexcept {
		const auto lStatus = ::NtClose(hObject);
		MCF_ASSERT_MSG(NT_SUCCESS(lStatus), L"NtClose() 失败。");
	}
}

}
