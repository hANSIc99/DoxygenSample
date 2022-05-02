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

/*! @file 
 *  Contains the declaration of the BStream::ByteStream class.
 */

namespace BStream {

/*! @class ByteStream
 * A stream class to operate on raw memory buffers (char*)
 */



/*! @fn size_t ByteStream::size() const 
 *	@brief Returns the size of the used memory buffer
 *
 * The function behaves identicallz for both
 * internal and external buffers.
 */

class ByteStream {

public:
	/*! @brief Constructor to allocates a new buffer
	 *         
	 * The internal buffer is allocated on the heap owned by the instance.
	 * Memory and size can be accessed by buffer() and size().
	 * 
	 * @param[in] size The size of the buffer
	 */
	ByteStream(size_t size);

	/*! @brief Constructor which takes an external buffer to operate on
	 *         
	 * The specified buffer already exist.
	 * Memory and size can be accessed by buffer() and size().
	 *
	 * @param[in] pBuf Pointer to existing buffer
	 * @param[in] size Size of the existing buffer
	 */
	ByteStream(char* pBuf, size_t size) noexcept; 

	// Destructor
	~ByteStream();

	/*! @brief Copy constructor
	 *
	 * Creates a deep copy.
	 */
	ByteStream(const ByteStream& stream);

	/*! @brief Copy assignment
	 *
	 * Invokes ByteStream(const ByteStream& stream) internally. Does not perform a self-assignemnt test.
	 */
	ByteStream& operator=(const ByteStream& other);

	/*! @brief Move constructor
	 *
	 * Invokes copy constructor ByteStream(const ByteStream& stream) internally. Does not perform a self-assignemnt test.
	 *
	 * @param[in] other The ByteStream instance from which the resources are stolen
	 */
	ByteStream(ByteStream&& other) noexcept;

	//! Move assignment 
	ByteStream& operator=(ByteStream&& other) noexcept;
	

	 /** @name Writing
	 *  Operators for writing to the stream
	 *  @{
	 */


	/*! @brief Template for writing basic types with known size at compile time
	 *
	 * For a list of basic types and their size refer to  [cppreference.com](https://en.cppreference.com/w/cpp/language/types)
	 */
	template<typename T>
	ByteStream& operator<<(T data) {
		size_t dataSize = sizeof(T);
		checkSize(dataSize);

		*reinterpret_cast<T*>(m_buffer + m_wPos) = data;
		m_wPos += dataSize;
		return *this;
	}

	/*! @brief Specialization for writing c-style strings
	 *
	 * The string is written till the occurence and including the the null byte.
	 */
	ByteStream& operator<<(const char* data);

	/*! @brief Specialization for writing C++ standard library strings
	 *
	 * For std::string refer to [cppreference.com](https://en.cppreference.com/w/cpp/string/basic_string).
	 */
	ByteStream& operator<<(const std::string &str);


	/** @} 
	 *  @name Reading
	 *  Operators for reading from the stream
	 *  @{
	 */


	/*! @brief Template for reading basic types with known size at compile time
	 *
	 * For a list of basic types and their size refer to  [cppreference.com](https://en.cppreference.com/w/cpp/language/types).
	 */
	template<typename T>
	ByteStream& operator>>(T &n) {
		size_t dataSize = sizeof(T);
		n = *reinterpret_cast<T*>(m_buffer + m_rPos);
		m_rPos += dataSize;
		return *this;
	}

	/*! @brief Specialization for reading C++ standard library strings
	 *
	 * For std::string refer to [cppreference.com](https://en.cppreference.com/w/cpp/string/basic_string)
	 */
	ByteStream& operator>>(std::string& str);

	/** @} */
	
	//! Returns a pointer to the memory buffer
	char* 	buffer() const noexcept;
	
	size_t	size() const noexcept;


private:

	void swap(ByteStream& other);
	void checkSize(size_t dataSize);

	size_t			m_wPos;	
	size_t			m_rPos;	
	size_t			m_size;
	char*			m_buffer;
	bool			m_ownBuffer; // indicates whether we use our own or an external buffer

};

} // namespace
#endif // BYTESTREAM_H