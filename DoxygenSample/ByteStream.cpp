/*
 * This file is part of ByteStream.
 *
 * ByteStream is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * Pythonic is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Pythonic. If not, see <https://www.gnu.org/licenses/>
 */


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

ByteStream& ByteStream::operator<<(const char* data)
{

	size_t dataSize = strlen(data) + 1; // include the terminating 0-byte
	checkSize(dataSize);

	strcpy(m_buffer + m_wPos, data);
	m_wPos += dataSize;
	return *this;
}

ByteStream& ByteStream::operator<<(const std::string& str)
{
	size_t dataSize = str.length() + 1; // include the terminating 0-byte
	checkSize(dataSize);

	strcpy(m_buffer + m_wPos, str.c_str());
	m_wPos += dataSize;
	return *this;
}

ByteStream& ByteStream::operator>>(std::string& str)
{
	const char* bufStr = reinterpret_cast<char*>(m_buffer + m_rPos);
	size_t length = strlen(bufStr);
	str += bufStr;
	m_rPos += length + 1;
	return *this;
}