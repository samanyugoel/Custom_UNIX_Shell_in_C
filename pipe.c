#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "functions.h"

int pipe_function(int pipe_implement, char *input, char **args, int z){

    if (args[0] == NULL){
        fprintf(stderr, "Syntax error : expected command before '|' \n");
        return 0;
    }

    if (args[pipe_implement + 1] == NULL){
        fprintf(stderr, "Syntax error : expected command after '|' \n");
        return 0;
    }
    free(args[pipe_implement]);
    //frees the '|' from the array
    args[pipe_implement] = NULL;
    //sets that slot to NULL for exec()
    int pid1 = -1;
    int pid2 = -1;
    int fd[2];
    //0 -> input
    //1 -> output

    if (pipe(fd) == -1){
        perror("pipe");
        return -1;
    }

        //first process in pipe
    pid1 = fork();
    if (pid1 == -1){
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return 3;
    }
    if (pid1 == 0)
    {
        //child process
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);

        if (args[0] != NULL){
            run_command(args);
        }
        cleanup(input, args, z);
        exit(0);
    }

    //second process in pipe
    pid2 = fork();
    if (pid2 == -1){
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return 3;
    }

    if (pid2 == 0)
    {
        //child process
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (args[pipe_implement + 1] != NULL){
            run_command(&args[pipe_implement + 1]);
        }
        cleanup(input, args, z);
        exit(0);
    }


    close(fd[0]);
    close(fd[1]);

    int status1 = 0;
    int status2 = 0;
    //for storing the status from both processes

    if (pid1 > 0) {
        waitpid(pid1, &status1, 0);
    }
    if (pid2 > 0) {
        waitpid(pid2, &status2, 0);
    }

    if ((WIFEXITED(status2) && WEXITSTATUS(status2)) != 0 || (WIFEXITED(status1) && WEXITSTATUS(status1)) != 0) {
        fprintf(stderr, "Command failed.\n");
    }
    return 0;
}
