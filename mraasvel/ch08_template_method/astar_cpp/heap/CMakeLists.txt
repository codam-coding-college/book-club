set(LIBNAME heap)

add_library(${LIBNAME} STATIC heap.cpp)
target_include_directories(${LIBNAME} PUBLIC .)
