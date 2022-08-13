cmake_minimum_required(VERSION 3.22)
project(book-club)

set(CMAKE_CXX_STANDARD 14)

add_executable(book-club srcs/main.cpp
		srcs/binarySearch.cpp
		includes/binarySearch.hpp)