cmake_minimum_required (VERSION 3.14)

add_executable (DoxygenSample DoxygenSample.cpp)
target_link_libraries(DoxygenSample PUBLIC ByteStream)