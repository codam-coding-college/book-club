set(LIBNAME astar)

add_library(${LIBNAME} STATIC
	astar.cpp
)

target_include_directories(${LIBNAME} PUBLIC .)
