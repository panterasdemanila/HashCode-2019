cmake_minimum_required(VERSION 3.13)
project(HashCode2019)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast" )

add_executable(HashCode2019 main.cpp Photo.cpp Photo.h io_operations.cpp io_operations.h)