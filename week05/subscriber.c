#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
const char* FIFO_PATH = "/tmp/ex1";


int main() {
    FILE *file_read = fopen(FIFO_PATH, "r");
    char *message = NULL;
    size_t buffer_capacity = 0;
    while (getline(&message, &buffer_capacity, file_read) != EOF) {
        printf("Got from a publisher: %s", message);
    }
    free(message);
    fclose(file_read);
    return EXIT_SUCCESS;
}
