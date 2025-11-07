//
// Created by Thomas on 2025-11-07.
//

#ifndef MAIN_H
#define MAIN_H

#define TRUE 1
#define FALSE 0
#define SHM_KEY 0x3385
#define MULTIPLE 3
#define DELAY_MICROSECONDS 5000

typedef struct {
    int multiple;
    int counter;
} SharedMemory;

#endif //MAIN_H
