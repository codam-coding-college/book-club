set(LIB json_parse)

add_library(${LIB} STATIC
	json_parse.cpp
	parser.cpp
	parser_null.cpp
)

target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/public)
target_include_directories(${LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/private)
target_link_libraries(${LIB} PUBLIC json)

target_compile_options(${LIB} PRIVATE
	-Wall
	-Wextra
	-Werror
)
