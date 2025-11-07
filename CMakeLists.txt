cmake_minimum_required(VERSION 3.29)
project(SYSC4001_A2_P2 C)

set(CMAKE_C_STANDARD 99)

add_executable(proc1 main.c
        main.h)
add_executable(proc2 process_two.c
        main.h)

add_dependencies(proc1 proc2)