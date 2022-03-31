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

#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include <cstddef>
#include <string>
#include <cstring>
#include <algorithm>

/*! \file 
 *  docs for this file
 */


/*!
 * A stream class to operate on raw memory buffers (char*)
 *
 * ByteStream takes the size of a
 *
 * @param theory Even if there is only one possible unified theory. it is just a
 *               set of rules and equations.
 */

namespace BStream {



class ByteStream {

public:
	/*! \brief Constructor to allocates a new buffer
	 *         
	 *
	 *  Detailed description starts here.
	 */
	ByteStream(size_t size);
	/*! Constructor which takes an external buffer to operate on */
	ByteStream(char* pBuf, size_t size); 
	// Destructor
	~ByteStream();
	// Copy constructor
	ByteStream(const ByteStream& stream);
	// Copy assignment
	// Pass by value to invoke the copy ctor
	ByteStream& operator=(const ByteStream& other);

	// Move constructor
	// The move contructor is called instead of the default constructor
	// and ,,steals" the ressources of the argument (,,ressource stealing")
	ByteStream(ByteStream&& other) noexcept;

	// Move assignment 
	ByteStream& operator=(ByteStream&& other) noexcept;





	// https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c
	// Template function muessen in den Header
	//void write(std::any data);

	/******************************
	 *                            *
	 *          WRINTING          *
	 *                            *
	 ******************************/

	 /** @name Writing
	 *  Operators for writing to the stream
	 *  @{
	 */

	/*! Template for writing basic types with known size at compile time */
	template<typename T>
	ByteStream& operator<<(T data) {
		size_t dataSize = sizeof(T);
		checkSize(dataSize);

		*reinterpret_cast<T*>(m_buffer + m_wPos) = data;
		m_wPos += dataSize;
		return *this;
	}

	/*! Specialization for writing c-style strings */
	ByteStream& operator<<(const char* data);
	/*! Specialization for writing C++ standard library strings */
	ByteStream& operator<<(const std::string &str);

	/** @} 
	 * @name Reading
	 *  Operators for reading from the stream
	 *  @{
	 */
	

	/******************************
	 *                            *
	 *          READING           *
	 *                            *
	 ******************************/

	/*! Template for reading basic types with known size at compile time */
	template<typename T>
	ByteStream& operator>>(T &n) {
		size_t dataSize = sizeof(T);
		n = *reinterpret_cast<T*>(m_buffer + m_rPos);
		m_rPos += dataSize;
		return *this;
	}
	/*! Specialization for reading C++ standard library strings */
	ByteStream& operator>>(std::string& str);

	/** @} */

	// Copy-and-swap idiom
	//TODO noexcept ??
	void swap(ByteStream& other);

; private:

	void checkSize(size_t dataSize);

	size_t			m_wPos;	
	size_t			m_rPos;	
	size_t			m_size;
	char*			m_buffer;
	bool			m_ownBuffer; // indicates whether we use our own or an external buffer

};

} // namespace
#endif // BYTESTREAM_H