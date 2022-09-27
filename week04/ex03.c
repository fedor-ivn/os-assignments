#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        return 0;
    }
    unsigned forks_count = strtol(argv[1], NULL, 10);
    for (unsigned ith = 0; ith < forks_count; ith++) {
        fork();
        sleep(5);
    }
    return 0;
}
