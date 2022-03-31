/*
 * This file is part of ByteStream.
 *
 * ByteStream is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * ByteStream is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with ByteStream. If not, see <https://www.gnu.org/licenses/>
 */


#include "ByteStream.h"
#include <stdexcept>
#include <iostream>

namespace BStream {

ByteStream::ByteStream(size_t size)
	: m_wPos(0)
	, m_rPos(0)
	, m_size(size)
	, m_buffer(new char[size])
	, m_ownBuffer(true)
{
}

ByteStream::ByteStream(char* pBuf, size_t size) noexcept
	: m_wPos(0)
	, m_rPos(0)
	, m_size(size)
	, m_buffer(pBuf)
	, m_ownBuffer(false)
{
}

ByteStream::~ByteStream()
{
	std::cout << "Destructor called" << std::endl;
	if(m_ownBuffer) delete [] m_buffer;
}

// Copy CTOR
ByteStream::ByteStream(const ByteStream& other)
	: m_wPos(other.m_wPos)
	, m_rPos(other.m_rPos)
	, m_size(other.m_size)
	, m_buffer(new char[m_size])
	, m_ownBuffer(true)
{
	std::cout << "CopyConstructor called" << std::endl;
	std::copy(other.m_buffer, other.m_buffer + m_size, m_buffer);
}
// Copy assignment
ByteStream& ByteStream::operator=(const ByteStream& other)
{
	//https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
	std::cout << "Assignment constructor called" << std::endl;
	ByteStream tmp(other); // Invoke the copy CTOR

	// Kein self-assignemnt test (this != &other)
	// Swap the contents with other (which is a copy of the rhs value)
	// When this assignment ctor is executed, the destructor of other is called
	
	swap(tmp);
	return *this;
}
// Move CTOR
ByteStream::ByteStream(ByteStream&& other) noexcept
	: m_wPos(other.m_wPos)
	, m_rPos(other.m_rPos)
	, m_size(other.m_size)
	, m_buffer(other.m_buffer)
	, m_ownBuffer(other.m_ownBuffer)
{
	std::cout << "Move CTOR called" << std::endl;
	other.m_buffer = nullptr; // make call to delete in destructor of instance ,,other" harmless
}
// Move assignment
ByteStream& ByteStream::operator=(ByteStream&& other) noexcept {
	std::cout << "Move assignment CTOR called" << std::endl;
	// Steal the values of the ByteStream instance passed as argument
	swap(other);
	return *this;
}

void ByteStream::swap(ByteStream& other)
{
	std::swap(m_wPos,		other.m_wPos);
	std::swap(m_rPos,		other.m_rPos);
	std::swap(m_size,		other.m_size);
	std::swap(m_buffer,		other.m_buffer);
	std::swap(m_ownBuffer,	other.m_ownBuffer);
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
	const char* bufStr = reinterpret_cast<const char*>(m_buffer + m_rPos);
	size_t length = strlen(bufStr);
	str += bufStr;
	m_rPos += length + 1;
	return *this;
}

} // namespace