#include "./commons.c"
#include <stdio.h>
#include <stdlib.h>

void first_come_first_served(ProcessMetric *processes, unsigned len) {
    qsort(processes, len, sizeof(ProcessMetric),
          (__compar_fn_t)compare_by_arrival);
    for (unsigned ith = 0; ith < len; ith++) {
        if (ith == 0 || processes[ith].arrival > processes[ith - 1].finish) {
            processes[ith].finish =
                processes[ith].arrival + processes[ith].burst;
        } else {
            processes[ith].finish =
                processes[ith - 1].finish + processes[ith].burst;
        }
    }
}

int main() {
    greet("First Come First Served");
    ParsedProcesses input = parse_process_metrics();
    first_come_first_served(input.parsed, input.len);
    putchar('\n');
    print_metrics(input.parsed, input.len);
    free(input.parsed);
    return EXIT_SUCCESS;
}
