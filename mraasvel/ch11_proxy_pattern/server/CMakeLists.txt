set(EXEC server.out)

add_executable(${EXEC}
	main.cpp
)

target_compile_options(${EXEC} PUBLIC -Wall -Wextra -Werror)

target_link_libraries(${EXEC} PUBLIC mrpc)
target_link_libraries(${EXEC} PUBLIC net)
target_link_libraries(${EXEC} PUBLIC json)
target_link_libraries(${EXEC} PUBLIC json_parse)
target_link_libraries(${EXEC} PUBLIC mrlog)
