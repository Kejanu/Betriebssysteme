# cmake_minimum_required(VERSION <specify CMake version here>)
project(BS C)

set(CMAKE_C_STANDARD 99)

add_executable(BS A0/qzahlen.c)
add_executable(BS A0/qzahlen_extended.c A0/qZahlenAlex.c A0/qZahlen_extendedAlex.c A0/qzahlen.c )
add_executable(AlexExtended A0/qZahlen_extendedAlex.c)
add_executable(Alex A0/qZahlenAlex.c)
add_executable(Kevin A0/qzahlen.c)
add_executable(KevinExtended A0/qzahlen_extended.c)


target_link_libraries(Kevin m)