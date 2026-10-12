#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    while(1)
    //infinite loop so the shell works after finishing the execution of any command
    {
        printf("shell> ");
        fflush(stdout);

        int i, z, x;
        i = x = z = 0;
        int args_buffer = 20;
        char *input = malloc(INPUT_BUFFER * sizeof(char));
        char **args = malloc(args_buffer * sizeof(char*));
        //dynamic memory allocation used to allocate memory for the input of arguments


        if (input == NULL || args == NULL){
            //error handling for allocation errors
            fprintf(stderr, "Memory Allocation Error.\n");
            return 1;
        }


        if (fgets(input, INPUT_BUFFER * sizeof(char), stdin) == NULL){
            //frees the memory if error with fetching the user input
            cleanup(input, args, z);
            return 0;
        }

        while (input[x] != '\0' && input[x] != '\n'){
           while (input[x] != '\0' && isspace((unsigned char)input[x])) {
                x++;
                //skips the spaces for proper tokenization
            }

            if (input[x] == '\0' || input[x] == '\n'){
                break;
            }
            else{
                if (z >= args_buffer - 1) {
                    args_buffer *= 2;

                    char **temp = realloc(args, args_buffer * sizeof(char*));
                    //reallocate memory if no more space is left for parsing the input
                    if (temp == NULL) {
                        fprintf(stderr, "Memory Allocation Error during realloc.\n");
                        cleanup(input, args, z);
                        return 1;
                    }
                    args = temp;
                }
                args[z] = getword(x, &input[0]);
                //calls the getword() for tokenized output stored in an array
                x += strlen(args[z]);
                z++;
            }
        }

        args[z] = NULL;
        //sets the last place in the array to NULL so as to run the exec() properly as it requires a NULL argument in the end

        if (args[0] == NULL) {
            //frees memory if no character is entered
            cleanup(input, args, z);
            continue;
        }

        int pipe_implement = -1;
        while (args[i] != NULL){
            if (strcmp(args[i], "|") == 0){
                pipe_implement = i;
                //sets the variable to the position of the pipe, which allows easy control over changes and access to that slot of the array
                break;
                //break exits the while loop whenever a pipe is found
            }
            i++;
        }

        if(pipe_implement != -1)
        //this won't execute unless pipe is called for
        {
            int pipe_error = pipe_function(pipe_implement, input, args, z);
            if (pipe_error != 0){
                fprintf(stderr, "Pipe failed.\n");
                cleanup(input, args, z);
                continue;
            }
        }

        else{
            if (args[0] != NULL){
                if (strcmp(args[0], "exit") == 0){
                    printf("Exit successfully initiated.\n");
                    cleanup(input, args, z);
                    exit(0);
                }
            if (strcmp(args[0], "cd") == 0) {
                char *targetdir = args[1];

                if (targetdir == NULL){
                    targetdir = getenv("HOME");
                }

                if (chdir(targetdir) != 0){
                    perror("cd");
                }
                cleanup(input, args, z);
                continue;
            }

                int pid = fork();
            //fork the process for running the exec() command

            if (pid == -1){
                perror("fork");
                cleanup(input, args, z);
                continue;
            }
            if (pid == 0){
                //child process
                //gets destroyed after exec() runs without error
                run_command(args);
                cleanup(input, args, z);
                exit(0);

            }

            else {
                //parent process
                //if parent process was destroyed instead of the child process, the shell would have destroyed itself as well, and would result in only letting one command run
                int statusofexec;
                wait(&statusofexec);
                if(WIFEXITED(statusofexec)){
                    int statuscode = WEXITSTATUS(statusofexec);
                    //gives status code depending on whether the child process exited or not
                    if (statusofexec != 0){
                        fprintf(stderr, "Command failed with status code %d.\n", statuscode);
                    }
                }
            }

        }
        cleanup(input, args, z);
        //cleans up each time the infinite loop runs
    }
    }
    return 0;
}
