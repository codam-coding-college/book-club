set(LIB variant)

add_library(${LIB} STATIC
	variant.cpp
)

target_include_directories(${LIB} PUBLIC ./include)
