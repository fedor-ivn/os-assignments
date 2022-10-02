#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(int number) {
    if (number <= 1) {
        return 0;
    }
    for (int div = 2; div * div <= number; div++) {
        if (number % div == 0) {
            return 0;
        }
    }
    return 1;
}

int global_n = 0;

// You will be locking and unlocking this
pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;

// Don't modify these variables directly, use the functions below.
int next_number_to_check = 0;
int primes_found_so_far = 0;

int get_number_to_check() {
    pthread_mutex_lock(&global_lock);
    int number =
        next_number_to_check != global_n ? ++next_number_to_check : global_n;
    pthread_mutex_unlock(&global_lock);
    return number;
}

void increment_primes() {
    pthread_mutex_lock(&global_lock);
    primes_found_so_far++;
    pthread_mutex_unlock(&global_lock);
}

void *check_primes(void *_) {
    int to_check;
    while ((to_check = get_number_to_check()) != global_n) {
        if (is_prime(to_check)) {
            increment_primes();
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    global_n = atoi(argv[1]);
    int threads_count = atoi(argv[2]);
    pthread_t *threads = calloc(sizeof(pthread_t), threads_count);

    for (int ith = 0; ith < threads_count; ith++) {
        pthread_create(&threads[ith], NULL, check_primes, NULL);
    }
    for (int ith = 0; ith < threads_count; ith++) {
        pthread_join(threads[ith], NULL);
    }
    printf("%d\n", primes_found_so_far);

    free(threads);
    pthread_mutex_destroy(&global_lock);

    return EXIT_SUCCESS;
}
