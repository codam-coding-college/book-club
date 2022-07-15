cmake_minimum_required(VERSION 3.17)
project("json")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -std=c++98")
set(CMAKE_LINKER_FLAGS)

file(GLOB includes "include/*.hpp")
file(GLOB_RECURSE srcs src/**.cpp)

add_executable(Json ${includes} ${srcs})
include_directories(include)