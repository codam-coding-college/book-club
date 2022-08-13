set(LIBNAME command_pattern)
set(OBJECT_FILES)

list(APPEND OBJECT_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/lib.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/remote.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/device.cpp"
)

add_library(${LIBNAME} STATIC ${OBJECT_FILES})
add_subdirectory(commands)
add_subdirectory(devices)

target_include_directories("${LIBNAME}" PUBLIC ../include)
target_compile_options("${LIBNAME}" PRIVATE -Wall -Wextra -Werror)
target_compile_options("${LIBNAME}" PRIVATE -Wno-unused-parameter -Wno-unused)
