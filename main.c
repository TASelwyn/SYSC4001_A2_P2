#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0

int main(void) {
    printf("SYSC 4001 - Assignment 2 - Part 2!\n");

    const pid_t pid = fork();
    if (pid == 0) {
        printf("Child process created\n");
        uint32_t count = 0;
        while (TRUE) {
            printf("Children count: %d\n", count++);
            usleep(500000);
        }
    } else {
        uint32_t count = 0;
        while (TRUE) {
            printf("Parents  count: %d\n", count++);
            usleep(500000);
        }
    }
}
