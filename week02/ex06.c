#include <stddef.h>
#include <stdio.h>

const char PRINTABLE = '*';

void print_n(size_t n) {
    for (size_t jth = 0; jth < n; jth++) {
        putchar(PRINTABLE);
    }
    putchar('\n');
}

void print_first_pattern(size_t height) {
    for (size_t ith = 0; ith < height; ith++) {
        print_n(ith + 1);
    }
}

void print_second_pattern(size_t height) {
    size_t half = height / 2;
    for (size_t ith = 0; ith < half; ith++) {
        print_n(ith + 1);
    }
    if (height % 2) {
        print_n(half + 1);
    }
    for (size_t ith = 0; ith < half; ith++) {
        print_n(half - ith);
    }
}

void print_third_pattern(size_t height, size_t width) {
    for (size_t ith = 0; ith < height; ith++) {
        print_n(width);
    }
}

int main() {
    const size_t height = 7;
    const size_t width = 7;

    printf("First pattern:\n");
    print_first_pattern(height);

    printf("Second pattern:\n");
    print_second_pattern(height);

        printf("Third pattern:\n");
    print_third_pattern(height, width);

    return 0; 
}
