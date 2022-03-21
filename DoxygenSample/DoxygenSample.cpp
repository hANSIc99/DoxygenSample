// DoxygenSample.cpp: Definiert den Einstiegspunkt für die Anwendung.
//
#include <iostream>
#include "ByteStream.h"

using namespace std;



int main()
{
	cout << "Hello CMake." << endl;
	ByteStream stream = ByteStream(20);
	
	stream << (long)0xAA << (long)0xBB << (long)0xCC;
	//stream << "Hallo ihr Pupspüpchen" << "world";
	//stream.write('A');

	long test_a = 123;
	long test_b = 123;
	stream >> test_a >> test_b;
	cout << "Ende CMake." << endl;
	return 0;
}
