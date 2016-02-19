// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2016, LH_Mouse. All wrongs reserved.

#ifndef MCF_STREAMS_ABSTRACT_STREAMS_HPP_
#define MCF_STREAMS_ABSTRACT_STREAMS_HPP_

#include <cstddef>

namespace MCF {

class AbstractInputStream {
public:
	virtual ~AbstractInputStream();

public:
	virtual int Peek() const = 0;
	virtual int Get() = 0;
	virtual bool Discard() = 0;

	virtual std::size_t Peek(void *pData, std::size_t uSize) const = 0;
	virtual std::size_t Get(void *pData, std::size_t uSize) = 0;
	virtual std::size_t Discard(std::size_t uSize) = 0;
};

class AbstractOutputStream {
public:
	virtual ~AbstractOutputStream();

public:
	virtual void Put(unsigned char byData) = 0;

	virtual void Put(const void *pData, std::size_t uSize) = 0;
};

}

#endif
