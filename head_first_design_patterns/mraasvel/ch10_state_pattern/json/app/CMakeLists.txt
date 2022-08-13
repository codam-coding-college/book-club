set(EXEC a.out)

add_executable(${EXEC}
	main.cpp
)

target_link_libraries(${EXEC} PUBLIC json_parse)

target_compile_options(${EXEC} PRIVATE -Wall -Wextra -Werror)
target_compile_options(${EXEC} PRIVATE -Wno-unused -Wno-unused-parameter)
