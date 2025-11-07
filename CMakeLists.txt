cmake_minimum_required(VERSION 3.29)
project(SYSC4001_A2_P2 C)

set(CMAKE_C_STANDARD 99)

add_executable(part4_proc1 part4_main.c
        part4_main.h)
add_executable(part4_proc2 part4_process_two.c
        part4_main.h)

add_dependencies(part4_proc1 part4_proc2)