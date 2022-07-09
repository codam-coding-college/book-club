set(LIB json)

add_library(${LIB} STATIC
	json.cpp
)

target_include_directories(${LIB} PUBLIC ./include)
target_compile_options(${LIB} PRIVATE
	-Wall
	-Wextra
	-Werror
)
