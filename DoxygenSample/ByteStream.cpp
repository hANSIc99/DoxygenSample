#include "ByteStream.h"

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


// reinterpret_cast<const char*>