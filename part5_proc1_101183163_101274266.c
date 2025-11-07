#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include "common.h"

int main(void) {
    printf("SYSC 4001 - Assignment 2 - Concurrent Linux!\n");

    // Shared memory
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

    // Create semaphore
    int semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    union semun semargs;
    semargs.val = 1;
    semctl(semid, 0, SETVAL, semargs);

    // Initialize shared
    shared->multiple = MULTIPLE;
    shared->counter = 0;

    pid_t pid = 0;
    while (TRUE) {
        // My semaphor
        sem_wait(semid);

        if (shared->counter % shared->multiple == 0) {
            printf("(P) Cycle number: %d - %d is a multiple of %d\n", shared->counter, shared->counter, shared->multiple);
        } else {
            printf("(P) Cycle number: %d\n", shared->counter);
        }

        if (shared->counter > 100 && pid == 0) {
            pid = fork();
            if (pid == 0) {
                execl("./part5_proc2", "part5_proc2", NULL);
                perror("children execution failed");
                exit(EXIT_FAILURE);
            }
        }

        if (shared->counter > 500) {
            break;
        }

        shared->counter++;
        sem_free(semid);
        usleep(DELAY_MICROSECONDS);
    }
    printf("(P) Waiting for child to exit...\n");
    wait(NULL);
    printf("(P) Child has exited. Parent now exiting.\n");

    // Clean up shared
    shmdt(shared);

    int shmctlret = shmctl(shmid, IPC_RMID, NULL);
    if (shmctlret < 0) {
        perror("shmctl failed");
        exit(EXIT_FAILURE);
    }
    printf("(P) Goodbye.\n");
    exit(EXIT_SUCCESS);
}
