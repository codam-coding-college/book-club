set(EXEC_NAME a.out)
add_executable("${EXEC_NAME}"
	main.cpp)

target_link_libraries(a.out PRIVATE command_pattern)

target_compile_options("${EXEC_NAME}" PRIVATE -Wall -Wextra -Werror)
