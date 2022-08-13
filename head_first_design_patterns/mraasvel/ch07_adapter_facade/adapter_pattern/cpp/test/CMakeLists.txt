set(EXEC test.out)

add_executable(${EXEC}
	main.cpp
	memory_storage.cpp
)

target_link_libraries(${EXEC} PUBLIC design)
target_link_libraries(${EXEC} PUBLIC memory_storage)

# Catch2
Include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(${EXEC} PUBLIC Catch2::Catch2)
