#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "part4_main.h"

#include <stdlib.h>

int main(void) {
    printf("SYSC 4001 - Assignment 2 - Part 2!\n");

    int shmid = shmget(SHM_KEY, sizeof(SharedMemory), 0666|IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    SharedMemory *shared = shmat(shmid, NULL, 0);
    if (shared == (void *) -1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // Initialize shared
    shared->multiple = MULTIPLE;
    shared->counter = 0;

    pid_t pid = 0;
    while (TRUE) {
        if (shared->counter % shared->multiple == 0) {
            printf("(P) Cycle number: %d - %d is a multiple of %d\n", shared->counter, shared->counter, shared->multiple);
        } else {
            printf("(P) Cycle number: %d\n", shared->counter);
        }

        if (shared->counter > 100 && pid == 0) {
            pid = fork();
            if (pid == 0) {
                execl("./proc2", "proc2", NULL);
                perror("children execution failed");
            }
        }

        if (shared->counter > 500) {
            exit(EXIT_SUCCESS);
        }

        shared->counter++;
        usleep(DELAY_MICROSECONDS);
    }
}
