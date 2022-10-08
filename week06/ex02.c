#include "./commons.c"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int compare(const void *process_a, const void *process_b) {
    ProcessMetric *a = (ProcessMetric *)process_a,
                  *b = (ProcessMetric *)process_b;
    if (a->arrival > b->arrival) {
        return 1;
    }
    if (a->arrival < b->arrival) {
        return -1;
    }
    if (a->burst > b->burst) {
        return 1;
    }
    if (a->burst < b->burst) {
        return -1;
    }
    return 0;
}

void shortest_job_first(ProcessMetric *processes, unsigned len) {
    qsort(processes, len, sizeof(ProcessMetric), compare);

    unsigned current_time = 0;
    bool *is_picked = calloc(sizeof(bool), len);
    for (unsigned ith = 0; ith < len; ith++) {
        unsigned min_burst = UINT_MAX;
        unsigned min_index = ith;
        for (int jth = 0; jth < len; jth++) {
            if (processes[jth].arrival > current_time) {
                break;
            }
            if (processes[jth].arrival <= current_time &&
                min_burst > processes[jth].burst && !is_picked[jth]) {
                min_burst = processes[jth].burst;
                min_index = jth;
            }
        }
        if (processes[min_index].arrival > current_time) {
            current_time = processes[min_index].arrival;
        }
        current_time += processes[min_index].burst;
        processes[min_index].finish = current_time;
        is_picked[min_index] = true;
    }
    free(is_picked);
}

int main() {
    greet("Shortest Job First");
    ParsedProcesses input = parse_process_metrics();
    shortest_job_first(input.parsed, input.len);
    putchar('\n');
    print_metrics(input.parsed, input.len);
    free(input.parsed);
    return EXIT_SUCCESS;
}
