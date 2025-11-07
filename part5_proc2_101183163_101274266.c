#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include "common.h"

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

    // Get semaphore
    int semid = semget(SEM_KEY, 1, 0666);

    while (TRUE) {
        sem_wait(semid);

        if (shared->counter % shared->multiple == 0) {
            printf("(C) Cycle number: %d - %d is a multiple of %d\n", shared->counter, shared->counter, shared->multiple);
        } else {
            printf("(C) Cycle number: %d\n", shared->counter);
        }

        if (shared->counter > 500) {
            break;
        }

        shared->counter++;
        sem_free(semid);

        usleep(DELAY_MICROSECONDS);
    }

    // Clean up shared
    shmdt(shared);

    int shmctlret = shmctl(shmid, IPC_RMID, NULL);
    if (shmctlret < 0) {
        perror("shmctl failed");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}
