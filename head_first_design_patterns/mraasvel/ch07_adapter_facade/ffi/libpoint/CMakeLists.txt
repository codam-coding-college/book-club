cmake_minimum_required(VERSION 3.0)
project(LibPoint)
add_library(libpoint STATIC point.c)
install(TARGETS libpoint DESTINATION .)
