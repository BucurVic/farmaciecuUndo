cmake_minimum_required(VERSION 3.27)
project(farmacie2 C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(farmacie2 main.c
        Medicament.h
        Medicament.c
        Farmacie.h
        Farmacie.c
        FarmacieService.h
        FarmacieService.c
        ui.h
        ui.c)
