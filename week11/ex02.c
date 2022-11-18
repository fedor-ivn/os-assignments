#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const char *DIRECTORY_PATH = "/";

int main() {
    printf("=============\nContent of %s\n=============\n", DIRECTORY_PATH);
    DIR *directory = opendir(DIRECTORY_PATH);
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(directory);
}
