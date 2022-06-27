set(EXEC a.out)

add_executable(${EXEC}
	main.cpp
	eight_puzzle.cpp
)

target_link_libraries(${EXEC} PRIVATE astar)
