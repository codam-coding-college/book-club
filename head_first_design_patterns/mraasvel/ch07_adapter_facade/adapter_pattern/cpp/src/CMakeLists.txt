set(EXEC a.out)

add_executable(${EXEC}
	main.cpp
)

target_link_libraries(${EXEC} PUBLIC design)
target_link_libraries(${EXEC} PUBLIC memory_storage)
