#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const char *INPUT_FILENAME = "input.txt";

typedef struct {
    unsigned resources_count;
    unsigned *existing_resources;
    unsigned *available_resources;
    unsigned processes_count;
    unsigned **allocation_matrix;
    unsigned **request_matrix;
} Input;

void parse_sequence(FILE *input, unsigned **sequence, unsigned *len) {
    *len = 0;
    char separator;
    do {
        *sequence = reallocarray(*sequence, ++(*len), sizeof(unsigned));
        unsigned scanned;
        fscanf(input, "%d%c", &scanned, &separator);
        (*sequence)[*len - 1] = scanned;
    } while (separator != '\n');
}

void parse_matrix(FILE *input, unsigned ***matrix, unsigned *len,
                  unsigned valid_row_len) {
    *len = 0;
    while (isdigit(fgetc(input))) {
        unsigned row_len = 0;
        unsigned *sequence = NULL;
        fseek(input, -1, SEEK_CUR);
        parse_sequence(input, &sequence, &row_len);
        if (valid_row_len != row_len) {
            printf("Parsing error!\n");
        }
        *matrix = reallocarray(*matrix, ++(*len), sizeof(unsigned *));
        (*matrix)[*len - 1] = sequence;
    }
    fseek(input, -1, SEEK_CUR);
}

Input *parse_input(FILE *input, Input *parsed) {
    parsed->resources_count = parsed->processes_count = 0;
    parsed->existing_resources = parsed->available_resources = NULL;
    parsed->allocation_matrix = parsed->request_matrix = NULL;

    parse_sequence(input, &parsed->existing_resources,
                   &parsed->resources_count);

    if (fgetc(input) != '\n') {
        return NULL;
    }

    unsigned checking_count;
    parse_sequence(input, &parsed->available_resources, &checking_count);

    if (parsed->resources_count != checking_count) {
        printf("Parsing error!\n");
        return NULL;
    }

    if (fgetc(input) != '\n') {
        printf("Parsing error!\n");
        return NULL;
    }

    parse_matrix(input, &parsed->allocation_matrix, &parsed->processes_count,
                 parsed->resources_count);

    if (fgetc(input) != '\n') {
        printf("Parsing error!\n");
        return NULL;
    }

    parse_matrix(input, &parsed->request_matrix, &checking_count,
                 parsed->resources_count);

    return parsed;
}

void free_input(Input *self) {
    for (unsigned ith = 0; ith < self->processes_count; ith++) {
        free(self->allocation_matrix[ith]);
        free(self->request_matrix[ith]);
    }
    free(self->allocation_matrix);
    free(self->request_matrix);
    free(self->existing_resources);
    free(self->available_resources);
    free(self);
}

bool is_lower_or_equal(unsigned *row_a, unsigned *row_b, unsigned len) {
    for (unsigned ith = 0; ith < len; ith++) {
        if (row_a[ith] > row_b[ith]) {
            return false;
        }
    }
    return true;
}

void sum_rows(unsigned *row_a, unsigned *row_b, unsigned len) {
    for (unsigned ith = 0; ith < len; ith++) {
        row_a[ith] += row_b[ith];
    }
}

void banker_algorithm(Input *input, unsigned **locked, unsigned *len) {
    *locked = NULL;
    *len = 0;
    bool *is_completable = calloc(input->processes_count, sizeof(bool));
    bool found_completable;

    do {
        found_completable = false;
        for (unsigned ith = 0; ith < input->processes_count; ith++) {
            if (!is_completable[ith] &&
                is_lower_or_equal(input->request_matrix[ith],
                                  input->available_resources,
                                  input->resources_count)) {
                sum_rows(input->available_resources,
                         input->allocation_matrix[ith], input->resources_count);
                is_completable[ith] = true;
                found_completable = true;
            }
        }
    } while (found_completable);

    for (unsigned ith = 0; ith < input->processes_count; ith++) {
        if (!is_completable[ith]) {
            *locked = reallocarray(*locked, ++(*len), sizeof(unsigned));
            (*locked)[*len - 1] = ith;
        }
    }
    free(is_completable);
}

int main() {
    FILE *input = fopen(INPUT_FILENAME, "r");
    Input *parsed = malloc(sizeof(Input));
    parse_input(input, parsed);

    if (parsed == NULL) {
        printf("Error occured\n");
        return 1;
    }

    unsigned *locked, locked_len;
    banker_algorithm(parsed, &locked, &locked_len);

    if (locked_len > 0) {
        printf("Some processes are deadlocked.\nLocked processes indices: ");
        for (unsigned ith = 0; ith < locked_len; ith++) {
            printf("%d ", locked[ith]);
        }
        printf("\n");
    } else {
        printf("OK! All processes can be completed!\n");
    }

    fclose(input);
    free(locked);
    free_input(parsed);
    return 0;
}
