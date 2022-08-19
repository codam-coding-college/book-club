set(EXEC test.out)
project(JSON_tests CXX)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)

file(GLOB test_srcs "*.cpp")
file(GLOB includes "../include/*.hpp")

add_executable(${EXEC} ${test_srcs} ${includes})

target_include_directories(${EXEC} PRIVATE ../include)
target_link_libraries(${EXEC} PUBLIC json_parser)

find_library(
        JSON_LIB
        NAMES json_parser.a json_parser libjson_parser
        HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../cmake-build-debug/"
        NO_DEFAULT_PATH
)
message(STATUS "JSON_LIB: [${JSON_LIB}]")

#if (NOT JSON_LIB)
#    message(SEND_ERROR "Did not find lib hello")
#endif


# Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(Catch2)
target_link_libraries(${EXEC} PUBLIC ${JSON_LIB} Catch2::Catch2)
#target_link_libraries(${EXEC} PUBLIC Catch2::Catch2)

