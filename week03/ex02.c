#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} Point;

float distance(Point a, Point b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float area(Point a, Point b, Point c) {
    return 0.5 * fabsf(a.x * b.y - b.x * a.y + b.x * c.y - c.x * b.y +
                       c.x * a.y - a.x * c.y);
}

int main(void) {
    Point a = {2.5, 6}, b = {1, 2.2}, c = {10, 6};

    float a_to_b = distance(a, b);
    printf("A -- B distance is %f\n", a_to_b);

    float abc_area = area(a, b, c);
    printf("Area of triangle ABC is %f\n", abc_area);

    return 0;
}
