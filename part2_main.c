#include <stdio.h>
#include <unistd.h>
#include "common.h"

int main(void) {
    printf("SYSC 4001 - Assignment 2 - Concurrent Linux!\n");

    const pid_t pid = fork();
    if (pid == 0) {
        execl("./part2_proc2", "part2_proc2", NULL);
        perror("children execution failed");
    } else {
        int count = 0;
        while (TRUE) {
            if (count % 3 == 0) {
                printf("(P) Cycle number: %d - %d is a multiple of 3\n", count, count);
            } else {
                printf("(P) Cycle number: %d\n", count);
            }
            count++;
            usleep(500000);
        }
    }
}