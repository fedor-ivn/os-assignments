#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const unsigned PUBLISH_DELAY = 100;

void publisher_routine(int fd_read, int fd_write) {
    close(fd_read);
    FILE *file_write = fdopen(fd_write, "w");
    char *message = NULL;
    size_t buffer_capacity = 0;
    printf("Input a message: ");
    while (getline(&message, &buffer_capacity, stdin) != EOF) {
        fputs(message, file_write);
        fflush(file_write);

        printf("Input a message: ");
        // sleep for PUBLISH_DELAY ms
        // to let the subscriber print the message
        struct timespec ts = {0, PUBLISH_DELAY * 1000000};
        nanosleep(&ts, NULL);
    }
    free(message);
    fclose(file_write);
}

void subscriber_routine(int fd_read, int fd_write) {
    close(fd_write);
    FILE *file_read = fdopen(fd_read, "r");
    char *message = NULL;
    size_t buffer_capacity = 0;
    while (getline(&message, &buffer_capacity, file_read) != EOF) {
        printf("Got from a publisher: %s", message);
    }
    free(message);
    fclose(file_read);
}

int main() {
    int pipe_fds[2];
    pipe(pipe_fds);
    int fd_read = pipe_fds[0];
    int fd_write = pipe_fds[1];

    pid_t subscriber = fork();
    if (subscriber > 0) {
        publisher_routine(fd_read, fd_write);
    } else if (subscriber == 0) {
        subscriber_routine(fd_read, fd_write);
    } else {
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
