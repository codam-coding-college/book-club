set(LIB memory_storage)

add_library(${LIB} INTERFACE)
target_include_directories(${LIB} INTERFACE ./include)
