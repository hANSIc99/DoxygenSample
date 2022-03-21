#include "ByteStream.h"
#include <stdexcept>
#include <iostream>

ByteStream::ByteStream(size_t size)
	: m_wPos(0)
	, m_rPos(0)
	, m_size(size)
{
	m_buffer = new char[size];
	memset(m_buffer, 0, size); // debug
}

ByteStream::ByteStream()
{
	delete m_buffer;
}

void ByteStream::checkSize(size_t dataSize)
{
	if (m_wPos + dataSize > m_size) {
		const char* errMsg = "Error ByteStream - Buffer not large enough";
		std::cerr << errMsg << std::endl;
		throw std::runtime_error(errMsg);
	}
}


// reinterpret_cast<const char*>