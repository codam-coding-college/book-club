SET(NAME "test.out")

add_executable(${NAME}
	main.c
)

target_link_libraries(${NAME} PUBLIC "criterion")
target_link_libraries(${NAME} PUBLIC "ft")
