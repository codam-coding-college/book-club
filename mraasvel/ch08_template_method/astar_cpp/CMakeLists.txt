cmake_minimum_required(VERSION 3.0)

project("Astar")

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compilation Flags
if (MSVC)
	add_compile_options(/W3 /WX)
else()
	add_compile_options(-O3 -Wall -Wextra -Wpedantic -Werror)
	add_compile_options(-Wno-unused -Wno-unused-parameter)
endif()

add_subdirectory(heap)
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(eight_puzzle)
