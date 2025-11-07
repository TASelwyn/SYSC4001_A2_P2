#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"

/*
 * SYSC 4001 - Assignment 2 – Part II (Concurrent Processes in Unix)
 *
 * Thomas Selwyn (101183163)
 * Rayyan Kashif (101274266)
 */

int main(void) {
    printf("SYSC 4001 - Assignment 2 - Concurrent Linux!\n");

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