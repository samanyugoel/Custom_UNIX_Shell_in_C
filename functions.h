#ifndef SHELL_H
#define SHELL_H

#define INPUT_BUFFER 1024

void cleanup(char *input, char **args, int count);
char *getword(int x, char *input);
int pipe_function(int pipe_implement, char *input, char **args, int z);
//z is the total number of arguments
int run_command(char **args);

#endif
