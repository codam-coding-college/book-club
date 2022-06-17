add_executable(a.out
	main.cpp
	factory_service.cpp
	user.cpp
	database.cpp
	user_service.cpp
)

target_compile_options(a.out PRIVATE -Wall -Wextra -Werror)
