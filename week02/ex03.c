#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const unsigned short STRING_SIZE = 256;

size_t to_decimal(size_t n, unsigned short from) {
    char stringified[STRING_SIZE];
    sprintf(stringified, "%lu", n);
    size_t length = strlen(stringified);

    size_t decimal = 0;
    for (size_t ith = 0; ith < length; ith++) {
        unsigned short digit = stringified[length - 1 - ith] - '0';
        decimal += digit * pow(from, ith);
    }

    return decimal;
}

_Bool is_valid_system(unsigned short system) {
    return 2 <= system && system <= 10;
}

_Bool convert(size_t n, unsigned short from, unsigned short to) {
    size_t decimal = to_decimal(n, from);
    char converted[STRING_SIZE];

    if (!is_valid_system(from) || !is_valid_system(to)) {
        return false;
    }

    size_t length = 0;
    while (decimal) {
        char digit = decimal % to + '0';
        converted[length++] = digit;
        decimal /= to;
    }

    for (size_t ith = 0; ith < length; ith++) {
        putchar(converted[length - 1 - ith]);
    }
    putchar('\n');

    return true;
}

int main() {
    long long number;
    size_t from, to;
    size_t scanned = scanf("%llu %lu %lu", &number, &from, &to);

    if (scanned != 3) {
        printf("cannot convert!\n");
        return 1;
    }

    if (!convert(number, from, to)) {
        printf("cannot convert!\n");
        return 1;
    }
    return 0;
}
