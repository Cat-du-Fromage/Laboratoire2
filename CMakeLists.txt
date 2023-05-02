cmake_minimum_required(VERSION 3.23.2)
project(Laboratoire2 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-std=c17 -Wall -Wconversion -Wextra -Wsign-conversion -Wpedantic")

add_executable(Laboratoire2 main.c listes_dynamiques.c utilitaires.c utilitaires.h testUnitaire.c testUnitaire.h)
