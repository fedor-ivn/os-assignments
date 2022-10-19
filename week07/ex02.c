#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned len;
    printf("Enter N: ");
    scanf("%u", &len);
    unsigned* values = calloc(len, sizeof(unsigned));
    for (unsigned i = 1; i < len; i++) {
        values[i] = i;
    }
    
    for (unsigned i = 0; i < len; i++) {
        printf("%u ", values[i]);
    }
    printf("\n");

    free(values);
    return 0;
}
