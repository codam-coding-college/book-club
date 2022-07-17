set(LIB mrpc)
add_library(${LIB} STATIC
	memory_storage.cpp
	storage_proxy.cpp
)

target_include_directories(${LIB} PUBLIC ./include)
target_compile_options(${LIB} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${LIB} PUBLIC net)
target_link_libraries(${LIB} PRIVATE json)
target_link_libraries(${LIB} PRIVATE json_parse)
