set(LIBNAME astar)

add_library(${LIBNAME} STATIC
	astar.cpp
)

target_link_libraries(${LIBNAME} PUBLIC heap)
target_include_directories(${LIBNAME} PUBLIC .)
