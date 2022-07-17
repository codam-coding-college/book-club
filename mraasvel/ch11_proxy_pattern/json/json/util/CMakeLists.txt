set(LIB util)
add_library(${LIB} STATIC
	printer.cpp
)

target_include_directories(${LIB} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
