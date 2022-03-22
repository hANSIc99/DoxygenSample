
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

	stream >> val_d >> val_d >> val_d;
	std::cout << "val_d: " << val_d;
	return 0;
}
