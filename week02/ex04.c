#include <ctype.h>
#include <stdio.h>

size_t count(char s[], char c) {
    size_t _count = 0;
    size_t ith = 0;
    while (s[ith] != '\0') {
        if (s[ith++] == c) {
            _count++;
        }
    }
    return _count;
}

void count_all(char s[]) {
    size_t ith = 0;
    for (; s[ith + 1]; ith++) {
        printf("%c:%lu, ", s[ith], count(s, s[ith]));
    }
    printf("%c:%lu\n", s[ith], count(s, s[ith]));
}

void lower(char s[]) {
    for (size_t ith = 0; s[ith]; ith++) {
        s[ith] = tolower(s[ith]);
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        return 1;
    }
    char* scanned = argv[1];
    lower(scanned);
    count_all(scanned);
    return 0;
}
