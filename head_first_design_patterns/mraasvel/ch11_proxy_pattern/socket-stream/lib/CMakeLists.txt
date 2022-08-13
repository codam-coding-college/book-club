set(LIB net)

add_library(${LIB} STATIC
	net.cpp
	socket.cpp
	tcp_listener.cpp
	tcp_stream.cpp
	socket_buffer.cpp
)

target_compile_options(${LIB} PRIVATE -Wall -Wextra -Werror)
target_compile_options(${LIB} PRIVATE -Wno-unused -Wno-unused-parameter)
target_include_directories(${LIB} PUBLIC ../include)

target_link_libraries(${LIB} PRIVATE mrlog)
