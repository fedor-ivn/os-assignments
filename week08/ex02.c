// Exercise 2.
//
// Foremost, I changed the conditions of experiment to analyze the expected
// behaviour. Specifically, I increased the portion of memory to 1.5 GB.
// The reason was that my machine has 16 GB of memory, so ten allocations of 10 MB
// did not affect `si` and `so` values.
//
// From the experiment in changed conditions, I noticed that `si` and `so` values
// did not change till the 6th iteration. From the 7th iteration, the `so` value
// started to grow. So, the operating system started to _swap out_ to disk since
// all the physical RAM was already allocated. However, `si` value also started to
// grow, maybe because the pages of more prioritized processes were _swapped in_.
// On the last iteration, operating system killed the process.
//
//
// Exercise 3.
//
// From the experiment, I noticed that the value of Memory Usage (`RES` field) was
// growing by 1.5 GB on each iteration. Obviously, it happened, because the program
// allocates exactly this portion of memory on each iteration.

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const size_t ONE_GB_IN_BYTES = 1024 * 1024 * 1024;
const size_t TEN_MB_IN_BYTES = 1.5 * ONE_GB_IN_BYTES;
const unsigned ALLOCATIONS_COUNT = 10;


int main() {
    char* allocated_chunks[ALLOCATIONS_COUNT];
    for (unsigned i = 0; i < ALLOCATIONS_COUNT; i++) {
        char *chunk = malloc(TEN_MB_IN_BYTES);
        memset(chunk, 0, TEN_MB_IN_BYTES);
        allocated_chunks[i] = chunk;

        sleep(1);
        printf("Allocated 1.25 GB for the %dnd time.\n", i + 1);
    }

    for (unsigned i = 0; i < ALLOCATIONS_COUNT; i++) {
        free(allocated_chunks[i]);
    }
    return 0;
}
