#include <stdio.h>
#include <stdlib.h>

int main() {
    char **s = malloc(sizeof(char *));
    char foo[] = "Hello World";
    *s = foo;
    printf("s is %s\n", *s);
    s[0] = foo;
    printf("s[0] is %s\n", s[0]);
    free(s);
    return (0);
}
