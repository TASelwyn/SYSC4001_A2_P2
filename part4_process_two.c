#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "common.h"
#include <stdlib.h>

int main(void) {
    int shmid = shmget(SHM_KEY, sizeof(SharedMemory), 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    SharedMemory *shared = shmat(shmid, NULL, 0);
    if (shared == (void *) -1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    while (TRUE) {
        if (shared->counter % shared->multiple == 0) {
            printf("(C) Cycle number: %d - %d is a multiple of %d\n", shared->counter, shared->counter, shared->multiple);
        } else {
            printf("(C) Cycle number: %d\n", shared->counter);
        }

        // Exit if done counting
        if (shared->counter > 500) {
            exit(EXIT_SUCCESS);
        }

        shared->counter++;
        usleep(DELAY_MICROSECONDS);
    }
}
