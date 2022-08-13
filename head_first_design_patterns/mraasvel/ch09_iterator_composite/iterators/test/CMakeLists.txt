set(EXEC test.out)

add_executable(${EXEC}
	main.cpp
	range_iterator.cpp
	map.cpp
	filter.cpp
	maarterator.cpp
	flatten.cpp
	chain.cpp
	take.cpp
	sum.cpp
	collect.cpp
	fold.cpp
	permutation.cpp
)

target_link_libraries(${EXEC} PUBLIC iterator)

# Catch2
Include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(${EXEC} PUBLIC Catch2::Catch2)
