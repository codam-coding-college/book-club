cmake_minimum_required(VERSION 3.0)
project("json")

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(variant)
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(app)
