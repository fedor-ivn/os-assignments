#include <stdio.h>
#include <string.h>

int main() {
    int scanned[256];
    int letter = 0;
    size_t length = 0;

    while ((letter = getchar()) != '.' && letter != '\n' && letter != EOF) {
        scanned[length++] = letter;
        if (length + 1 == 256) {
            break;
        }
    }

    // reverse the string
    putchar('"');
    for (size_t ith = 0; ith < length; ith++) {
      putchar(scanned[length - 1 - ith]);
    }
    putchar('"');
    putchar('\n');
    return 0;
}
