
#include <iostream>
#include "ByteStream.h"


int main()
{
	std::cout << "Doxygen Example" << std::endl;
	ByteStream stream = ByteStream(100);
	std::string hello("Hello ");
	// Writing to the stream
	stream << (long)0xAA << (short)0xBB << (double)3.14;
	stream << hello << "Doxygen " << "Sample!";

	// Reading from the stream
	long		val_a = 0;
	short		val_b = 0;
	double		val_c = 0;
	std::string val_d;

	stream >> val_a >> val_b >> val_c;
	
	std::cout << "val_a: " << val_a << std::endl;
	std::cout << "val_b: " << val_b << std::endl;
	std::cout << "val_c: " << val_c << std::endl;

	// Invoke the copy CTOR
	ByteStream anotherStream(stream);


	// Invoke the copy assignment CTOR
	ByteStream copyStream(10);
	copyStream = anotherStream;

	// Invoke the move CTOR
	ByteStream movedStream(std::move(copyStream));
	// copyStream cannot be used anymore

	// Invoke the move assignment CTOR
	ByteStream movedAssignStream(30);
	movedAssignStream = std::move(movedStream);
	

	movedAssignStream >> val_d >> val_d >> val_d;
	std::cout << "val_d: " << val_d << std::endl;
	return 0;
}
