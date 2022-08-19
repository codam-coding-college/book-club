cmake_minimum_required(VERSION 3.22)
project(json_parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

file(GLOB_RECURSE SOURCE_FILES "srcs/*.cpp")
file(GLOB HEADER_FILES "include/*.hpp")


add_library(json_parser ${SOURCE_FILES} ${HEADER_FILES})
#add_executable(test json_parser.a main.cpp)
include_directories(include libft/include)

add_subdirectory(tests)
