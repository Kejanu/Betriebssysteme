# cmake_minimum_required(VERSION <specify CMake version here>)
project(BS C)

set(CMAKE_C_STANDARD 99)

#add_executable(BS qzahlen.c)
add_executable(BS A0/qzahlen_extended.c A0/qZahlenAlex.c)