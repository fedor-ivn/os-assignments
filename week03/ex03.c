#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t global_files_counter = 1;
const unsigned short MAX_SUBDIRECTORIES = 8;

struct Directory;
struct File;

struct File {
    size_t id;
    char name[64];
    size_t size;
    char data[1024];

    struct Directory *directory; // The parent directory
};
typedef struct File File;

struct Directory {
    int files_count;
    int directories_count;
    char path[2048];

    File **files;
    struct Directory **directories;
};
typedef struct Directory Directory;

// Operations on files
File *create_file(const char *name);
void add_to_file(File *file, const char *content);
void append_to_file(File *file, const char *content);
void pwd_file(File *file);

// Operations on directories
Directory *create_directory(const char *name);
void add_file(File *file, Directory *dir);
void add_dir(Directory *dir1, Directory *dir2); // given to you

// Helper functions
void show_dir(Directory *dir);
void show_file(File *file);
void show_file_detailed(File *file);

int main() {
    char content1[] = "int printf(const char * format, ...);";
    char content2[] = "int main(){printf('Hello World');}";
    char content3[] = "//This is a comment in C language";
    char content4[] = "Bourne Again Shell!";

    Directory *home = create_directory("/home");
    Directory *bin = create_directory("/bin");
    Directory *root = create_directory("/");

    // Example: the path of the folder home is /home

    // Add subdirectories
    add_dir(home, root);
    add_dir(bin, root);
    // show_dir(root);

    File *bash = create_file("bash"), *ex31 = create_file("ex3_1.c"),
         *ex32 = create_file("ex3_2.c");

    add_to_file(ex31, content1);
    add_to_file(ex32, content3);
    add_to_file(bash, content4);

    add_file(bash, bin);
    add_file(ex31, home);
    add_file(ex32, home);

    append_to_file(ex31, content2);

    show_dir(root);
    show_file_detailed(bash);
    show_file_detailed(ex31);
    show_file_detailed(ex32);

    pwd_file(bash);
    pwd_file(ex31);
    pwd_file(ex32);

    return 0;
}

// Helper functions

// Displays the content of the Directory dir
void show_dir(Directory *dir) {
    printf("\nDIRECTORY\n");
    printf(" path: %s\n", dir->path);
    printf(" files:\n");
    printf("    [ ");
    for (int i = 0; i < dir->files_count; i++) {
        show_file(dir->files[i]);
    }
    printf("]\n");
    printf(" directories:\n");
    printf("    { ");

    for (int i = 0; i < dir->directories_count; i++) {
        show_dir(dir->directories[i]);
    }
    printf("}\n");
}

// Prints the name of the File file
void show_file(File *file) { printf("%s ", file->name); }

// Shows details of the File file
void show_file_detailed(File *file) {
    printf("\nFILE\n");
    printf(" id: %zu\n", file->id);
    printf(" name: %s\n", file->name);
    printf(" size: %lu\n", file->size);
    printf(" data:\n");
    printf("    [ %s ]\n", file->data);
}

// Implementation: Operations on files
File *create_file(const char *name) {
    File *created = malloc(sizeof(File));
    created->id = global_files_counter++;
    strcpy(created->name, name);
    return created;
}

// Adds the content to the File file
void add_to_file(File *file, const char *content) {
    strcpy(file->data, content);
    file->size = strlen(content);
}

// Appends the content to the File file
void append_to_file(File *file, const char *content) {
    strcat(file->data, content);
    file->size = strlen(file->data);
}

// Prints the path of the File file
void pwd_file(File *file) {
    printf("%s", file->directory->path);
    printf("/%s\n", file->name);
}

// Implementation: Operations on directories
Directory *create_directory(const char *name) {
    Directory *created = malloc(sizeof(Directory));
    created->directories = malloc(sizeof(Directory) * MAX_SUBDIRECTORIES);
    created->directories_count = 0;
    created->files_count = 0;
    strcat(created->path, name);
    return created;
}

// Adds the File file to the Directory dir
void add_file(File *file, Directory *dir) {
    dir->files = realloc(dir->files, sizeof(File) * dir->files_count);
    dir->files[dir->files_count] = file;
    dir->files_count++;
    file->directory = dir;
}

// Given to you
// Adds the subdirectory dir1 to the directory dir2
void add_dir(Directory *child, Directory *parent) {
    if (child && parent) {
        parent->directories =
            realloc(parent->directories,
                    sizeof(Directory) * (parent->directories_count + 1));
        parent->directories[parent->directories_count++] = child;
        char tmp[2048];
        strcpy(tmp, child->path);
        strcpy(child->path, parent->path);
        strcpy(child->path, tmp);
    }
}
