#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("Welcome to simplistic shell\nType \"exit\" to leave the shell\n");
    while (1) {
        char *cmd = NULL;
        size_t buffer_capacity = 0;
        printf(">>> ");
        int characters = getline(&cmd, &buffer_capacity, stdin);
        if (characters < 0 || strcmp(cmd, "exit\n") == 0){
            printf("Exiting the shell... Goodbye!\n");
            return 0;
        }
        
        if (cmd[characters - 2] == '&') {
            cmd[characters - 2] = '\0';
            if (fork() == 0) {
                system(cmd);
                return 0;
            }
        } else {
            system(cmd);
        }
    }
    return 0;
}
