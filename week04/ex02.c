#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static const char TEMP_FILENAME[] = "temp.txt";
static const unsigned VECTOR_DIMENSION = 120;
static const unsigned VECTOR_RAND_MAX = 100;

unsigned long *get_random_vector() {
    unsigned long *created = malloc(sizeof(unsigned long) * VECTOR_DIMENSION);
    for (unsigned i = 0; i < VECTOR_DIMENSION; i++) {
        created[i] = rand() % VECTOR_RAND_MAX;
    }
    return created;
}

unsigned long dot_product(unsigned long *u, unsigned long *v,
                          size_t dimension) {
    unsigned long result = 0;
    for (size_t i = 0; i < dimension; i++) {
        result += u[i] * v[i];
    }
    return result;
}

void fork_routine(unsigned long *u, unsigned long *v, unsigned calcs_count,
                  FILE *file) {
    unsigned long calculated = dot_product(u, v, calcs_count);
    fprintf(file, "%ld\n", calculated);
}

unsigned long aggregate_calcs(FILE *file, unsigned forks_count) {
    rewind(file);
    unsigned long aggregated = 0;
    for (unsigned i = 0; i < forks_count; i++) {
        unsigned long calculation;
        fscanf(file, "%ld\n", &calculation);
        aggregated += calculation;
    }
    return aggregated;
}

void print_vector(unsigned long *vector) {
    for (unsigned i = 0; i < VECTOR_DIMENSION - 1; i++) {
        printf("%ld,", vector[i]);
    }
    printf("%ld", vector[VECTOR_DIMENSION - 1]);
}

int main() {
    srand(time(NULL));
    unsigned long *u = get_random_vector();
    unsigned long *v = get_random_vector();

    unsigned forks_count;
    printf("Enter the number of processes: ");
    scanf("%d", &forks_count);

    pid_t *forks = malloc(sizeof(pid_t) * forks_count);
    unsigned calcs_per_fork = VECTOR_DIMENSION / forks_count;
    FILE *temp_file = fopen(TEMP_FILENAME, "w+");

    unsigned long *shifted_u = u, *shifted_v = v;
    for (unsigned ith = 0; ith < forks_count; ith++) {
        forks[ith] = fork();
        if (forks[ith] == 0) {
            fork_routine(shifted_u, shifted_v, calcs_per_fork, temp_file);
            exit(EXIT_SUCCESS);
        }
        shifted_u += calcs_per_fork;
        shifted_v += calcs_per_fork;
    }

    // wait for each child to die
    for (unsigned ith = 0; ith < forks_count; ith++) {
        waitpid(forks[ith], NULL, 0);
    }
    unsigned long aggregated = aggregate_calcs(temp_file, forks_count);
    fclose(temp_file);

    printf("Given:\nu = [");
    print_vector(u);
    printf("]\nv = [");
    print_vector(v);
    printf("]\n\nResult:\n");
    printf("u * v = %ld\n", aggregated);

    free(u);
    free(v);
    free(forks);
    return 0;
}
