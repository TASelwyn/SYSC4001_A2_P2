#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

int main(void) {
    printf("SYSC 4001 - Assignment 2 - Part 2!\n");

    const pid_t pid = fork();
    if (pid == 0) {
        execl("./proc2", "proc2", NULL);
        perror("children execution failed");
    } else {
        // Let's wait for the child
        wait(NULL);
        return 0;
    }
}
