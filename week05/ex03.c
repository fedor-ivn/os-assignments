#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int div = 2; div * div <= n; div++) {
        if (n % div == 0) {
            return 0;
        }
    }
    return 1;
}

int primes_count_in_interval(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        if (is_prime(i) != 0) {
            sum++;
        }
    }
    return sum;
}

// The structure that will be passed to the threads, corresponding to an
// interval to count the number of primes in.
typedef struct {
    int start, end;
} prime_counter_request;

void *prime_counter(void *arg) {
    prime_counter_request *request = arg;
    int *count = malloc(sizeof(int));
    *count = primes_count_in_interval(request->start, request->end);
    return count;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]), threads_count = atoi(argv[2]);
    int segment_size = n / threads_count + (n % threads_count == 0 ? 0 : 1);
    int last_segment_size = n + segment_size - segment_size * threads_count;

    pthread_t *threads = calloc(sizeof(pthread_t), threads_count);

    prime_counter_request *requests =
        calloc(sizeof(prime_counter_request), threads_count);

    void **results = calloc(sizeof(void *), threads_count);

    int start = 0;
    for (int ith = 0; ith < threads_count; ith++) {
        requests[ith].start = start;
        start += ith < threads_count - 1 ? segment_size : last_segment_size;
        requests[ith].end = start;
        pthread_create(&threads[ith], NULL, prime_counter, &requests[ith]);
    }

    for (int ith = 0; ith < threads_count; ith++) {
        pthread_join(threads[ith], &results[ith]);
    }

    int total_result = 0;
    for (int ith = 0; ith < threads_count; ith++) {
        total_result += *(int *)results[ith];
        free(results[ith]);
    }
    printf("%d\n", total_result);

    free(threads);
    free(requests);
    free(results);

    return EXIT_SUCCESS;
}
