cmake_minimum_required (VERSION 3.14)

add_library(ByteStream STATIC ByteStream.cpp ByteStream.h)

target_include_directories(ByteStream INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})