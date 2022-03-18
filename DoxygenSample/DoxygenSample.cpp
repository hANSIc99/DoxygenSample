// DoxygenSample.cpp: Definiert den Einstiegspunkt für die Anwendung.
//
#include <iostream>
#include "ByteStream.h"

using namespace std;



int main()
{
	cout << "Hello CMake." << endl;
	ByteStream stream = ByteStream(20);
	stream << "HELLO" << "world";
	stream << (int)0xAA << (short)0xBB;
	//stream.write('A');
	

	return 0;
}
