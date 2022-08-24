cmake_minimum_required(VERSION 3.22)
project(json_parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

file(GLOB_RECURSE SOURCE_FILES "srcs/*.cpp")
file(GLOB HEADER_FILES "include/*.hpp")


add_library(json_parser ${SOURCE_FILES} ${HEADER_FILES})
#add_executable(test json_parser.a main.cpp)
include_directories(include libft/include)



## Testing suite:

# Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.9
)
file(GLOB test_srcs "tests/*.cpp")
FetchContent_MakeAvailable(Catch2)
add_executable(test.out ${test_srcs} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(test.out PUBLIC Catch2::Catch2)
