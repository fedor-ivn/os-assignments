#include <stdio.h>
#include <time.h>
#include <unistd.h>

void print_process_meta(const char *process_name, clock_t start_time) {
    double execution_time = (double)(clock() - start_time) / CLOCKS_PER_SEC * 1000;
    printf("Process: %-10s    ID: %d    Parent ID: %d    Execution time: "
           "%f milliseconds\n",
           process_name, getpid(), getppid(), execution_time);
}

int main() {
    clock_t main_start = clock();
    pid_t first, second;

    first = fork();
    clock_t first_start = clock();
    if (first == 0) {
        print_process_meta("Child #1", first_start);
    } else {
        second = fork();
        pid_t second_start = clock();
        if (second == 0) {
            print_process_meta("Child #2", second_start);
        } else {
            print_process_meta("Main", main_start);
        }
    }

    return 0;
}
