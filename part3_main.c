#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "common.h"

int main(void) {
    printf("SYSC 4001 - Assignment 2 - Concurrent Linux!\n");

    const pid_t pid = fork();
    if (pid == 0) {
        execl("./part3_proc2", "part3_proc2", NULL);
        perror("children execution failed");
    } else {
        // Let's wait for the child
        wait(NULL);
        return 0;
    }
}