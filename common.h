//
// Created by Thomas on 2025-11-07.
//

#ifndef COMMON_H
#define COMMON_H

#define TRUE 1
#define FALSE 0

#define MULTIPLE 3
#define DELAY_MICROSECONDS 5000

// Shared memory
#define SHM_KEY 0x3385

typedef struct {
    int multiple;
    int counter;
} SharedMemory;

// Semaphore system
#include <sys/sem.h>
#include <stdlib.h>

#define SEM_KEY 0x5345

union semun {
    int val;
    struct semid_s* buf;
    unsigned short* array;
};

static void sem_wait(int semid) {
    struct sembuf op = {0, -1, SEM_UNDO};
    if (semop(semid, &op, 1) == -1) {
        perror("semop P");
        exit(EXIT_FAILURE);
    }
}

static void sem_free(int semid) {
    struct sembuf op = {0, 1, SEM_UNDO};
    if (semop(semid, &op, 1) == -1) {
        perror("semop V");
        exit(EXIT_FAILURE);
    }
}

#endif //COMMON_H
