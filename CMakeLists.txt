cmake_minimum_required(VERSION 3.24)
project(Laboratoire2 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-std=c17 -Wall -Wconversion -Wextra -Wsign-conversion -Wpedantic")

add_executable(Laboratoire2 listes_dynamiques.c listes_dynamiques.h)
add_executable(test main.c listes_dynamiques.c)
