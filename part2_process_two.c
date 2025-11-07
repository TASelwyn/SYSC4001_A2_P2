#include <stdio.h>
#include <unistd.h>
#include "common.h"

int main(void) {
    int count = 0;
    while (TRUE) {
        if (count % 3 == 0) {
            printf("(C) Cycle number: %d - %d is a multiple of 3\n", count, count);
        } else {
            printf("(C) Cycle number: %d\n", count);
        }
        count--;
        usleep(500000);
    }
}