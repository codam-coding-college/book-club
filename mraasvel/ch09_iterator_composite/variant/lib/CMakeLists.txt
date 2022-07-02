set(LIB variant)

add_library(${LIB} STATIC
	lib.cpp
	variant.cpp
)

target_include_directories(${LIB} PUBLIC ./include)
