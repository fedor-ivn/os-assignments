#include "./commons.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void round_robbin(ProcessMetric *processes, unsigned len, unsigned quantum) {
    qsort(processes, len, sizeof(ProcessMetric),
          (__compar_fn_t)compare_by_arrival);

    int *remainings = calloc(sizeof(int), len);
    bool *is_queued = calloc(sizeof(bool), len);
    int *queue = calloc(sizeof(int), len);

    int finished_count = 0, queue_len = 0;
    int current_time = processes[0].arrival;
    for (int ith = 0; ith < len; ith++) {
        remainings[ith] = processes[ith].burst;
        is_queued[ith] = false;
        queue[ith] = 0;
        if (processes[ith].arrival <= current_time) {
            is_queued[ith] = true;
            queue[queue_len++] = ith;
        }
    }

    while (finished_count != len) {
        if (queue_len == 0) {
            for (int ith = 0; ith < len; ith++) {
                if (is_queued[ith] == 0) {
                    current_time = processes[ith].arrival;
                    break;
                }
            }
            for (int ith = 0; ith < len; ith++) {
                if (!is_queued[ith] && processes[ith].arrival <= current_time) {
                    queue[queue_len++] = ith;
                }
            }
        }

        for (int ith = 0; ith < queue_len; ith++) {
            bool is_finished = false;
            if (quantum >= remainings[queue[ith]]) {
                current_time += remainings[queue[ith]];
                processes[queue[ith]].finish = current_time;
                finished_count++;
                is_finished = true;
            } else {
                current_time += quantum;
                remainings[queue[ith]] -= quantum;
            }

            int arrived_count = 0;
            int *arrived = calloc(sizeof(int), len);
            for (int jth = 0; jth < len; jth++) {
                if (processes[jth].arrival <= current_time && !is_queued[jth]) {
                    arrived[arrived_count++] = jth;
                    is_queued[jth] = true;
                }
            }

            if (arrived_count > 0) {
                for (int jth = queue_len - 1; jth >= ith + is_finished; jth--) {
                    queue[jth + arrived_count - is_finished] = queue[jth];
                }
                for (int jth = 0; jth < arrived_count; jth++) {
                    queue[ith++] = arrived[jth];
                    queue_len++;
                }
            } else if (is_finished) {
                for (int jth = ith; jth < queue_len - 1; jth++) {
                    queue[jth] = queue[jth + 1];
                }
            }

            if (is_finished) {
                queue_len--;
                ith--;
            }

            free(arrived);
        }
    }

    free(remainings);
    free(is_queued);
    free(queue);
}

int main() {
    greet("Round Robbin");
    printf("Enter the time quantum: ");
    unsigned quantum;
    scanf("%u", &quantum);

    ParsedProcesses input = parse_process_metrics();
    round_robbin(input.parsed, input.len, quantum);
    putchar('\n');
    print_metrics(input.parsed, input.len);
    free(input.parsed);
    return EXIT_SUCCESS;
}
