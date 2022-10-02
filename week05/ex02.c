#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_t id;
    int i;
    char message[256];
} Thread;

void *say_hello(void *_thread) {
    Thread *thread = _thread;
    printf("%lu: %s\n", thread->id, thread->message);
    pthread_exit(EXIT_SUCCESS);
}

int main() {
    unsigned threads_count;
    printf("Enter the number of threads: ");
    scanf("%d", &threads_count);

    Thread *threads = calloc(sizeof(Thread), threads_count);
    for (unsigned ith = 0; ith < threads_count; ith++) {
        threads[ith].i = ith;
        sprintf(threads[ith].message, "Hello from thread %d", ith);
        printf("Thread %d is created\n", threads[ith].i);
        pthread_create(&threads[ith].id, NULL, say_hello, &threads[ith]);
        pthread_join(threads[ith].id, NULL);
    }

    return EXIT_SUCCESS;
}
