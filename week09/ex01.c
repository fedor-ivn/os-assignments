#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned page_t;
typedef struct {
    page_t page;
    bool is_referenced;
    unsigned counter;
} TableEntry;

const char *INPUT_FILENAME = "input.txt";

const unsigned TICKS_PER_CLOCK_INTERRUPT = 4;
const unsigned COUNTER_BITS = 8;

TableEntry *oldest_entry(TableEntry *table, unsigned table_size) {
    TableEntry *candidate = table;
    for (unsigned ith = 0; ith < table_size; ith++) {
        TableEntry *entry = &table[ith];
        if (entry->counter < candidate->counter) {
            candidate = entry;
        }
    }
    return candidate;
}

TableEntry *find_entry(TableEntry *table, unsigned table_size, page_t page) {
    for (unsigned ith = 0; ith < table_size; ith++) {
        if (table[ith].page == page) {
            return &table[ith];
        }
    }
    return NULL;
}

void swap_in(page_t entering, TableEntry *available) {
    available->page = entering;
    available->is_referenced = true;
    available->counter = 0;
}

void clock_interrupt(TableEntry *table, unsigned table_size) {
    for (unsigned ith = 0; ith < table_size; ith++) {
        TableEntry *entry = &table[ith];
        entry->counter =
            entry->is_referenced << (COUNTER_BITS - 1) | entry->counter >> 1;
        entry->is_referenced = false;
    }
}

unsigned aging_algorithm_hits(unsigned table_len, const page_t *references,
                              unsigned references_len) {
    TableEntry *table = calloc(table_len, sizeof(TableEntry));
    unsigned table_size = 0, ticks = 0, hits = 0;

    for (unsigned ith = 0; ith < references_len; ith++) {
        page_t page = references[ith];
        TableEntry *found = find_entry(table, table_size, page);
        if (found == NULL) {
            TableEntry *available;
            if (table_size < table_len) {
                available = &table[table_size++];
            } else {
                available = oldest_entry(table, table_size);
            }
            swap_in(page, available);
        } else {
            found->is_referenced = true;
            hits++;
        }

        if (ticks++ == TICKS_PER_CLOCK_INTERRUPT) {
            ticks = 0;
            clock_interrupt(table, table_size);
        }
    }

    free(table);

    return hits;
}

int main() {
    FILE *input_file = fopen(INPUT_FILENAME, "r");
    unsigned table_len;
    printf("Enter the number of page frames: ");
    scanf("%d", &table_len);

    unsigned len = 0;
    unsigned bufsize = 1;
    page_t *references = malloc(bufsize * sizeof(page_t));
    while (fscanf(input_file, "%d", &references[len]) != EOF) {
        if (++len == bufsize) {
            bufsize *= 2;
            references = realloc(references, bufsize * sizeof(page_t));
        }
    }

    unsigned hits = aging_algorithm_hits(table_len, references, len),
             misses = len - hits;
    double ratio = (double)hits / misses;
    printf("\n    Table size: %8d\n          Hits: %8d\n        Misses: %8d\nHit/Miss ratio: %f\n",
           table_len, hits, misses, ratio);

    free(references);

    return 0;
}
