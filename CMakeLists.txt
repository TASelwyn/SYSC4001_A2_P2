cmake_minimum_required(VERSION 3.29)
project(SYSC4001_A2_P2 C)

set(CMAKE_C_STANDARD 99)
# Part 1
add_executable(part1 part1_main.c common.h)

# Part 2
add_executable(part2_proc1 part2_main.c common.h)
add_executable(part2_proc2 part2_process_two.c
        common.h)
add_dependencies(part2_proc1 part2_proc2)

# Part 3
add_executable(part3_proc1 part3_main.c common.h
        part3_main.c)
add_executable(part3_proc2 part3_process_two.c
        common.h)
add_dependencies(part3_proc1 part3_proc2)

# Part 4
add_executable(part4_proc1 part4_main.c
        common.h)
add_executable(part4_proc2 part4_process_two.c
        common.h)
add_dependencies(part4_proc1 part4_proc2)