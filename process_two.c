#include <stdio.h>
#include <unistd.h>
#include "main.h"

int main(void) {
    int count = 0;
    while (TRUE) {
        if (count % 3 == 0) {
            printf("(C) Cycle number: %d - %d is a multiple of 3\n", count, count);
        } else {
            printf("(C) Cycle number: %d\n", count);
        }

        count--;
        usleep(50000);

        // Exit if done counting
        if (count < -500) {
            return 0;
        }
    }
}
