set(EXEC a.out)

add_executable(${EXEC}
	main.cpp
)

target_compile_options(${EXEC} PUBLIC -Wall -Wextra -Werror)
target_link_libraries(${EXEC} PUBLIC mrpc)
target_link_libraries(${EXEC} PUBLIC mrlog)
