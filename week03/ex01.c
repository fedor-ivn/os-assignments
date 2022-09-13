#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int years_old) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900 - years_old;
}

int main() {
    const int SIZE = 5;
    const int x = 10;
    int* q = &x;

    const int* const p = (const int* const)malloc(sizeof(int) * SIZE);
    for (int ith = 0; ith < SIZE; ith++) {
     ((int*) p)[ith] = x;
    }
    for (int ith = 0; ith < SIZE; ith++) {
        printf("The address of cell #%d: %p\n", ith + 1, ((int*) p) + ith);
    }

    for (int ith = 0; ith < SIZE; ith++) {
        scanf("%d", ((int*) p) + ith);
    }
    for (int ith = 0; ith < SIZE; ith++) {
        ((int*) p)[ith] = foo(((int*) p)[ith]);
    }

    for (int ith = 0; ith < SIZE; ith++) {
        printf("Birthday of Student #%d: %d\n", ith + 1, ((int*) p)[ith]);
    }
    free(((int*) p));
    return 0;
}
