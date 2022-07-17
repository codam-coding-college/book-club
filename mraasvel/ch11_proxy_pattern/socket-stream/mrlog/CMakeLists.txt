set(LIB mrlog)

add_library(${LIB} STATIC mrlog.cpp)
target_include_directories(${LIB} PUBLIC ./include)
target_compile_options(${LIB} PRIVATE -Wall -Wextra -Werror)
