#pragma once

#include <any>

class ByteStream {

public:
	ByteStream::ByteStream(size_t size);
	ByteStream::ByteStream();


	// https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c
	// Template function müssen in den Header
	//void write(std::any data);

	template<typename T>
	ByteStream& operator<<(T data) {
		*reinterpret_cast<T*>(m_buffer + m_wPos) = data;
		m_wPos += sizeof(T);
		return *this;
	}
	ByteStream& operator<<(const char* data) {
		strcpy(m_buffer + m_wPos, data);
		m_wPos += strlen(data) + 1; // including hte terminating 0-byte
		return *this;
	}
	

; private:
	unsigned long	m_wPos;
	unsigned long	m_rPos;
	size_t			m_size;
	char*			m_buffer;
};