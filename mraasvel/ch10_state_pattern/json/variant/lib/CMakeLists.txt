set(LIB variant)

add_library(${LIB} STATIC
	variant.cpp
)

target_include_directories(${LIB} PUBLIC ./include)
target_compile_options(${LIB} PRIVATE
	-Wall
	-Wextra
	-Werror
)
