#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *DIRECTORY_PATH = "./tmp";

typedef struct {
    ino_t inode;
    char *name;
} INodeAndName;

bool is_valid(char *name) {
    if (strlen(name) == 1 && name[0] == '.') {
        return false;
    } else if (strlen(name) == 2 && name[0] == '.' && name[1] == '.') {
        return false;
    }
    return true;
}

int main() {
    DIR *directory = opendir(DIRECTORY_PATH);

    INodeAndName *pairs = NULL;
    unsigned size = 0;
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        if (!is_valid(entry->d_name)) {
            continue;
        }
        struct stat buf;
        size_t path_len = strlen(entry->d_name) + strlen(DIRECTORY_PATH) + 2;
        char *path = calloc(path_len, sizeof(char));
        sprintf(path, "%s/%s", DIRECTORY_PATH, entry->d_name);
        stat(path, &buf);
        if (buf.st_nlink >= 2) {
            pairs = reallocarray(pairs, ++size, sizeof(INodeAndName));
            INodeAndName *pair = &pairs[size - 1];
            pair->name = strdup(entry->d_name);
            pair->inode = entry->d_ino;
        }
        free(path);
    }
    closedir(directory);

    puts("File --- Hard Links");
    for (unsigned ith = 0; ith < size; ith++) {
        INodeAndName *current = &pairs[ith];
        printf("%s --- ", current->name);
        unsigned jth = 0;
        for (; jth < size; jth++) {
            INodeAndName *pair = &pairs[jth];
            if (current->inode == pair->inode) {
                printf("%s", pair->name);
                jth++;
                break;
            }
        }
        for (; jth < size; jth++) {
            INodeAndName *pair = &pairs[jth];
            if (current->inode == pair->inode) {
                printf(", %s", pair->name);
            }
        }
        printf("\n");
    }

    for (unsigned ith = 0; ith < size; ith++) {
        free(pairs[ith].name);
    }
    free(pairs);
}
