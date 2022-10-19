#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void *my_realloc(void *ptr, size_t size) {
    size_t old_size = ptr != NULL ? malloc_usable_size(ptr) : 0;
    if (size <= old_size) {
        if (size == 0) {
            free(ptr);
        }
        return ptr;
    }
    void *new_ptr = malloc(size);
    memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}


// I took the code from Exercise 3 to test my_realloc function
int main() {
    srand(time(NULL));
    printf("Enter original array size: ");
    int n1 = 0;
    scanf("%d", &n1);
    int *a1 = calloc(n1, sizeof(int));
    int i;
    for (i = 0; i < n1; i++) {
        a1[i] = 100;
        printf("%d ", a1[i]);
    }
    printf("\nEnter new array size: ");
    int n2 = 0;
    scanf("%d", &n2);

    // Dynamically change the array to size n2 using my_realloc
    a1 = my_realloc(a1, n2 * sizeof(int));
    if (n2 > n1) {
        memset(a1 + n1, 0, (n2 - n1) * sizeof(int));
    }

    for (i = 0; i < n2; i++) {
        printf("%d ", a1[i]);
    }
    printf("\n");

    free(a1);
    return 0;
}
