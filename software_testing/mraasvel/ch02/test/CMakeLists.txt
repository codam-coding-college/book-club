SET(NAME "test.out")

add_executable(${NAME}
	test_ft_split.c
	test_ft_itoa.c
)

target_link_libraries(${NAME} PUBLIC "criterion")
target_link_libraries(${NAME} PUBLIC "ft")
