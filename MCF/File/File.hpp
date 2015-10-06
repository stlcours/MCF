// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2015, LH_Mouse. All wrongs reserved.

#ifndef MCF_CORE_FILE_HPP_
#define MCF_CORE_FILE_HPP_

#include "../Core/StringView.hpp"
#include "../Core/UniqueHandle.hpp"
#include "../Function/FunctionObserver.hpp"
#include <cstddef>
#include <cstdint>

namespace MCF {

namespace Impl_File {
	struct NtHandleCloser {
		constexpr void *operator()() const noexcept {
			return nullptr;
		}
		void operator()(void *hFile) const noexcept;
	};
}

class File {
public:
	enum : std::uint32_t {
		// 权限控制。
		kToRead        = 0x00000001,
		kToWrite       = 0x00000002,

		// 创建行为控制。如果没有指定 TO_WRITE，这些选项都无效。
		kDontCreate    = 0x00000004, // 文件不存在则失败。若指定该选项则 kFailIfExists 无效。
		kFailIfExists  = 0x00000008, // 文件已存在则失败。

		// 杂项。
		kNoBuffering   = 0x00000010,
		kWriteThrough  = 0x00000020,
		kDeleteOnClose = 0x00000040,
		kDontTruncate  = 0x00000080, // 默认情况下使用 kToWrite 打开文件会清空现有内容。
	};

private:
	UniqueHandle<Impl_File::NtHandleCloser> x_hFile;

public:
	constexpr File() noexcept
		: x_hFile()
	{
	}

	File(const WideStringView &wsvPath, std::uint32_t u32Flags);

public:
	bool IsOpen() const noexcept;
	void Open(const WideStringView &wsvPath, std::uint32_t u32Flags);
	bool OpenNoThrow(const WideStringView &wsvPath, std::uint32_t u32Flags);
	void Close();

	std::uint64_t GetSize() const;
	void Resize(std::uint64_t u64NewSize);
	void Clear();

	// 1. fnAsyncProc 总是会被执行一次，即使读取或写入操作失败；
	// 2. 所有的回调函数都可以抛出异常；在这种情况下，异常将在读取或写入操作完成或失败后被重新抛出。
	// 3. 当且仅当 fnAsyncProc 成功返回且异步操作成功后 fnCompleteCallback 才会被执行。
	std::size_t Read(void *pBuffer, std::uint32_t u32BytesToRead, std::uint64_t u64Offset,
		FunctionObserver<void ()> fnAsyncProc = nullptr, FunctionObserver<void ()> fnCompleteCallback = nullptr) const;
	std::size_t Write(std::uint64_t u64Offset, const void *pBuffer, std::uint32_t u32BytesToWrite,
		FunctionObserver<void ()> fnAsyncProc = nullptr, FunctionObserver<void ()> fnCompleteCallback = nullptr);
	void Flush() const;

	void Swap(File &rhs) noexcept {
		using std::swap;
		swap(x_hFile, rhs.x_hFile);
	}

public:
	explicit operator bool() const noexcept {
		return IsOpen();
	}
};

inline void swap(File &lhs, File &rhs) noexcept {
	lhs.Swap(rhs);
}

}

#endif
