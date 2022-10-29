#include <bits/types/struct_rusage.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

const size_t TEN_MB_IN_BYTES = 10 * 1024 * 1024;
const unsigned ALLOCATIONS_COUNT = 10;

int main() {
    char *allocated_chunks[ALLOCATIONS_COUNT];
    for (unsigned i = 0; i < ALLOCATIONS_COUNT; i++) {
        char *chunk = malloc(TEN_MB_IN_BYTES);
        memset(chunk, 0, TEN_MB_IN_BYTES);
        allocated_chunks[i] = chunk;

        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);

        sleep(1);
        printf(
            "Allocated 10 MB for the %2dnd time. Current memory usage: %ld\n",
            i + 1, usage.ru_maxrss);
    }

    for (unsigned i = 0; i < ALLOCATIONS_COUNT; i++) {
        free(allocated_chunks[i]);
    }
    return 0;
}
