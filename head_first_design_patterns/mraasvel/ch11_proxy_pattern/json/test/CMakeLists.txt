set(EXEC test.out)

add_executable(${EXEC}
	main.cpp
	null.cpp
	array.cpp
	"string.cpp"
	object.cpp
	"bool.cpp"
	number.cpp
)

target_link_libraries(${EXEC} PUBLIC json_parse)
target_link_libraries(${EXEC} PUBLIC json)

# Catch2
Include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(${EXEC} PUBLIC Catch2::Catch2)
