# cmake_minimum_required(VERSION <specify CMake version here>)
project(BS C)


set(CMAKE_C_STANDARD 99)

add_executable(BS A0/qzahlen.c)
#add_executable(BS A0/qzahlen_extended.c A0/qZahlenAlex.c A0/qZahlen_extendedAlex.c A0/qzahlen.c )
add_executable(AlexExtended A0/qZahlen_extendedAlex.c)
add_executable(Alex A0/qZahlenAlex.c A1/Alex/1a.c A1/Alex/1b.c A1/Alex/Test.c A1/Alex/1c.c A1/Alex/1extended.c)
add_executable(Kevin A0/qzahlen.c)

add_executable(Kevin1a A1/Kevin/1a.c)
add_executable(Kevin1b A1/Kevin/1b.c)
add_executable(Kevin1c A1/Kevin/1c.c)
add_executable(Kevin1extended A1/Kevin/1extended.c)


#add_executable(Testen A1/Kevin/Testen.c)
add_executable(Alex1a A1/Alex/1a.c)
add_executable(Test A1/Alex/Test.c)
add_executable(Alex1b A1/Alex/1b.c)
add_executable(Alex1c A1/Alex/1c.c)
add_executable(AlexExtended2 A1/Alex/1extended.c)


add_executable(Vorgabe A2/Vorgabe/prime.c)
add_executable(PrimeAlex A2/Alex/primeOld.c)
add_executable(PrimeAlexExtended A2/Alex/prime.c)


target_link_libraries(Kevin m)