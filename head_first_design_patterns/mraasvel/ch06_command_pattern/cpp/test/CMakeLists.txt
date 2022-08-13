set(EXEC_NAME test.out)

add_executable("${EXEC_NAME}"
	main.cpp
	remote.cpp
)

target_link_libraries("${EXEC_NAME}" PUBLIC command_pattern)

# Catch2
Include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries("${EXEC_NAME}" PUBLIC Catch2::Catch2)
