set(TARGET diff.out)

add_executable(
	${TARGET}
	main.cpp
	matrix.cpp
)

target_include_directories(${TARGET} PRIVATE .)
