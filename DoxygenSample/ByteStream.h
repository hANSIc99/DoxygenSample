#pragma once

#include <string>

class ByteStream {

public:
	ByteStream::ByteStream(size_t size);
	ByteStream::ByteStream();


	// https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c
	// Template function müssen in den Header
	//void write(std::any data);

	template<typename T>
	ByteStream& operator<<(T data) {
		size_t dataSize = sizeof(T);
		checkSize(dataSize);

		*reinterpret_cast<T*>(m_buffer + m_wPos) = data;
		m_wPos += dataSize;
		return *this;
	}
	ByteStream& operator<<(const char* data) {

		size_t dataSize = strlen(data) + 1; // include the terminating 0-byte
		checkSize(dataSize);

		strcpy(m_buffer + m_wPos, data);
		m_wPos += dataSize;
		return *this;
	}
	
	template<typename T>
	ByteStream& operator>>(T &n) {
		size_t dataSize = sizeof(T);
		n = *reinterpret_cast<T*>(m_buffer + m_rPos);
		m_rPos += dataSize;
		return *this;
	}

; private:

	void checkSize(size_t dataSize);

	size_t			m_wPos;
	size_t			m_rPos;
	size_t			m_size;
	char*			m_buffer;

};