#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

const unsigned PUBLISH_DELAY_NS = 10000000;
const char *FIFO_PATH = "/tmp/ex1";
const mode_t FIFO_MODE = S_IRUSR + S_IWUSR;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    unsigned n = strtol(argv[1], NULL, 10);

    mkfifo(FIFO_PATH, FIFO_MODE);

    FILE *writable = fopen(FIFO_PATH, "w");
    char *message = NULL;
    size_t buffer_capacity = 0;
    struct timespec ts = {0, PUBLISH_DELAY_NS};
    printf("Input a message: ");
    while (getline(&message, &buffer_capacity, stdin) != EOF) {
        printf("Input a message: ");
        for (unsigned ith = 0; ith < n; ith++) {
            fputs(message, writable);
            fflush(writable);
            nanosleep(&ts, NULL);
        }
    }

    fclose(writable);
    free(message);

    return EXIT_SUCCESS;
}
