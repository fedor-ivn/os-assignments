#include <float.h>
#include <limits.h>
#include <stdio.h>

int main() {
    int a = INT_MAX;
    unsigned short b = USHRT_MAX;
    long c = LONG_MAX;
    float d = FLT_MAX;
    double e = DBL_MAX;

    printf("Type: int; Size: %lu; Value: %d\n", sizeof(int), a);
    printf("Type: unsigned short; Size: %lu; Value: %d\n",
           sizeof(unsigned short), b);
    printf("Type: long; Size: %lu; Value: %ld\n", sizeof(long), c);
    printf("Type: float; Size: %lu; Value: %f\n", sizeof(float), d);
    printf("Type: double; Size: %lu; Value: %f\n", sizeof(double), e);
    return 0;
}
