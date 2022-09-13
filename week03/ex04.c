#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void* aggregate(void* base, size_t size, int n, void* initial_value,
                void* (*opr)(const void*, const void*));

void* add_int(const void* a, const void* b) {
    int* result = malloc(sizeof(int));
    *result = *((int*)a) + *((int*)b);
    return result;
}

void* add_double(const void* a, const void* b) {
    double* result = malloc(sizeof(double));
    *result = *((double*)a) + *((double*)b);
    return result;
}

void* multiply_int(const void* a, const void* b) {
    int* result = malloc(sizeof(int));
    *result = *((int*)a) * *((int*)b);
    return result;
}

void* multiply_double(const void* a, const void* b) {
    double* result = malloc(sizeof(double));
    *result = *((double*)a) * *((double*)b);
    return result;
}

typedef struct Mean {
    size_t n;
    double mean;
} Mean;

Mean* init_mean() {
    Mean* initialized = malloc(sizeof(Mean));
    initialized->n = 0;
    initialized->mean = 0;
    return initialized;
}

void* mean_int(const void* a, const void* b) {
    Mean* previous = (Mean*)a;
    Mean* result = init_mean();
    result->n = previous->n + 1;
    result->mean = (previous->mean * previous->n + *(int*)b) / result->n;
    return result;
}

void* mean_double(const void* a, const void* b) {
    Mean* previous = (Mean*)a;
    Mean* result = init_mean();
    result->n = previous->n + 1;
    result->mean = (previous->mean * previous->n + *(double*)b) / result->n;
    return result;
}

void* aggregate(void* base, size_t size, int n, void* initial_value,
                void* (*opr)(const void*, const void*)) {
    void* aggregated = initial_value;
    aggregated = opr(aggregated, base);
    for (size_t ith = 1; ith < n; ith++) {
        void* to_drop = aggregated;
        aggregated = opr(aggregated, (base + ith * size));
        free(to_drop);
    }
    return aggregated;
}

int main() {
    const size_t SAMPLES_COUNT = 5;

    int* ints = malloc(sizeof(int) * SAMPLES_COUNT);
    double* doubles = malloc(sizeof(double) * SAMPLES_COUNT);

    for (int ith = 0; ith < SAMPLES_COUNT; ith++) {
        scanf("%d", ints + ith);
    }

    for (int ith = 0; ith < SAMPLES_COUNT; ith++) {
        scanf("%lf", doubles + ith);
    }

    // // Addition
    int* int_initial_add = malloc(sizeof(int));
    *int_initial_add = 0;
    int* result_int_add =
        aggregate(ints, sizeof(int), SAMPLES_COUNT, int_initial_add, add_int);
    printf("%d\n", *result_int_add);

    double* double_initial_add = malloc(sizeof(double));
    *double_initial_add = 0;
    double* result_double_add = aggregate(
        doubles, sizeof(double), SAMPLES_COUNT, double_initial_add, add_double);

    printf("%f\n", *result_double_add);

    // Multiplication
    int* int_initial_mult = malloc(sizeof(int));
    *int_initial_mult = 1;
    int* result_int_mult = aggregate(ints, sizeof(int), SAMPLES_COUNT,
                                     int_initial_mult, multiply_int);

    printf("%d\n", *result_int_mult);

    double* double_initial_mult = malloc(sizeof(double));
    *double_initial_mult = 1;
    double* result_double_mult =
        aggregate(doubles, sizeof(double), SAMPLES_COUNT, double_initial_mult,
                  multiply_double);

    printf("%f\n", *result_double_mult);

    // Mean
    Mean* initial_int_mean = init_mean();

    Mean* result_int_mean =
        aggregate(ints, sizeof(int), SAMPLES_COUNT, initial_int_mean, mean_int);

    printf("%f\n", result_int_mean->mean);

    Mean* initial_double_mean = init_mean();
    Mean* result_double_mean = aggregate(doubles, sizeof(double), SAMPLES_COUNT,
                                         initial_double_mean, mean_double);

    printf("%f\n", result_double_mean->mean);

    // free the pointers
    void* to_free[] = {doubles,          ints,
                       int_initial_add,  double_initial_add,
                       int_initial_mult, double_initial_mult,
                       initial_int_mean, initial_double_mean,
                       result_int_add,   result_double_add,
                       result_int_mult,  result_double_mult,
                       result_int_mean,  result_double_mean};
    for (size_t ith = 0; ith < 10; ith++) {
        free(to_free[ith]);
    }
    return 0;
}
