cmake_minimum_required(VERSION 3.14)
project(RSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(RSA codec64.cpp codec64.h main.cpp)
