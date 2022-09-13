#include <stddef.h>
#include <stdio.h>

size_t tribonacci(size_t nth) {
    size_t a = 0, b = 1, c = 1, result = 0;
    if (nth == 0) {
        result = a;
    }
    if (1 == nth || nth == 2) {
        result += b;
    }
    for (size_t ith = 3; ith <= nth; ith++) {
        result = a + b + c;
        a = b;
        b = c;
        c = result;
    }
    return result;
}

int main() {
    printf("tribonacci(4) returned %lu\n", tribonacci(4));
    printf("tribonacci(36) returned %lu\n", tribonacci(36));
    return 0;
}
