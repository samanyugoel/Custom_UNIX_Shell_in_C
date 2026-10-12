#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include "functions.h"

int run_command(char **args){
    if (strcmp(args[0], "ls") == 0){
        char *targetdir = (args[1] != NULL) ? args[1] : ".";

        DIR *dir = opendir(targetdir);
        if (dir == NULL) {
            //If the directory doesn't exist or we don't have permission
            fprintf(stderr, "ls: Cannot open '%s' : %s\n", targetdir, strerror(errno));
            return -1;
        }
        else {
            struct dirent *entry;
            //using built-in struct for accessing the directory
            //Read every file entry one at a time
            while ((entry = readdir(dir)) != NULL) {
                if (entry -> d_name[0] == '.'){
                    //skips hidden files
                    continue;
                }
                printf("%s\n", entry -> d_name);
           }
            fflush(stdout);
            closedir(dir);
            return 0;
        }
    }
    else if (strcmp(args[0], "pwd") == 0){
        char cwd[1024];
        if (getcwd (cwd, sizeof(cwd)) != NULL){
            printf("%s\n", cwd);
        }
        else {
            perror("pwd");
        }
        return 0;
    }
    else if (strcmp(args[0], "echo") == 0){
        for (int j = 1; args[j] != NULL; j++){
            printf("%s", args[j]);
            if (args[j+1] != NULL){
                printf(" ");
            }
        }
        printf("\n");
        return 0;
    }
    else
        {
            execvp(args[0], args);
            perror(args[0]);
            //gives error if does not properly
            return -1;
        }
}
