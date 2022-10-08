#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned id;
    unsigned arrival;
    unsigned burst;
    unsigned finish;
} ProcessMetric;

typedef struct {
    ProcessMetric *parsed;
    unsigned len;
} ParsedProcesses;

unsigned get_turnaround(ProcessMetric *process) {
    return process->finish - process->arrival;
}

unsigned get_waiting(ProcessMetric *process) {
    return process->finish - process->arrival - process->burst;
}

int compare_by_arrival(ProcessMetric *process_a, ProcessMetric *process_b) {
    return process_a->arrival > process_b->arrival ? 1 : -1;
}

/*
    WARN: this function allocates the memory!
*/
ParsedProcesses parse_process_metrics() {
    printf("Enter the number of processes: ");
    unsigned len;
    scanf("%u", &len);
    ProcessMetric *parsed = calloc(sizeof(ProcessMetric), len);

    // TODO: make a check for length

    printf("Enter the arrival times: ");
    for (unsigned ith = 0; ith < len; ith++) {
        scanf("%u", &parsed[ith].arrival);
        parsed[ith].id = ith;
    }

    printf("Enter the burst times: ");
    for (unsigned ith = 0; ith < len; ith++) {
        scanf("%u", &parsed[ith].burst);
    }

    return (ParsedProcesses){parsed, len};
}

void center_text(char *text, int field_width) {
    int pad_len = (field_width - strlen(text)) / 2;
    printf("%*s%s%*s", pad_len, "", text, pad_len, "");
}

void prepare_job_id(unsigned index, char *s) {
    char index_to_literal = index % 26 + 65;
    unsigned div = index / 26;
    if (div) {
        sprintf(s, "%u%c", div, index_to_literal);
    } else {
        sprintf(s, "%c", index_to_literal);
    }
}

int compare_by_id(ProcessMetric *process_a, ProcessMetric *process_b) {
    return process_a->id > process_b->id ? 1 : -1;
}

void print_metrics(ProcessMetric *processes, unsigned len) {
    qsort(processes, len, sizeof(ProcessMetric), (__compar_fn_t)compare_by_id);
    unsigned sum_turnaround = 0;
    unsigned sum_waiting = 0;

    const char *border_top = "+-----+--------------+------------+-------------+"
                             "-----------------+--------------+\n";
    printf("%s", border_top);
    printf("| Job | Arrival Time | Burst Time | Finish Time | Turnaround Time "
           "| Waiting Time |\n");
    printf("%s", border_top);
    for (unsigned ith = 0; ith < len; ith++) {
        ProcessMetric *process = processes + ith;
        // TODO: is it safe ?
        char *process_literal = calloc(sizeof(char), process->id / 26 + 2);
        prepare_job_id(process->id, process_literal);
        unsigned turnaround = get_turnaround(process),
                 waiting = get_waiting(process);
        sum_turnaround += turnaround;
        sum_waiting += waiting;
        printf("| %-3s | %-12u | %-10u | %-11u | %-15u "
               "| %-12u |\n",
               process_literal, process->arrival, process->burst,
               process->finish, turnaround, waiting);
        free(process_literal);
    }
    printf("%s", border_top);
    printf(
        "| Average                                       | %-15f | %-12f |\n",
        (double)sum_turnaround / len, (double)sum_waiting / len);
    printf("%s", border_top);
}

void greet(const char *solver_name) {
    printf("\nWelcome to %s process scheduling solver!\n\n", solver_name);
}
