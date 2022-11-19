SET(NAME ft)

add_library(${NAME} STATIC
	ft_split.c
	ft_itoa.c
)

target_include_directories(${NAME} PUBLIC .)
