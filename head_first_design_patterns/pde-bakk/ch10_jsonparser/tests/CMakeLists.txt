set(EXEC test.out)
project(JSON_tests CXX)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)

file(GLOB test_srcs "*.cpp")
file(GLOB includes "../include/*.hpp")

add_executable(${EXEC} ${test_srcs} ${includes})

target_include_directories(${EXEC} PRIVATE ../include)
target_link_libraries(${EXEC} PUBLIC json_parser)


# Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(Catch2)
target_link_libraries(${EXEC} PUBLIC Catch2::Catch2)

