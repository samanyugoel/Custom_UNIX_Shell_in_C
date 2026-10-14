# A Custom UNIX Shell in C

## Overview

A custom-built shell created in C as a learning project which demonstrates dynamic memory allocation, memory management, piping, error and signal handling, modular programming, tokenization and string parsing.

### Features

* **Dynamic Memory Allocation** - Allocates memory for commands and argument lists of varying lengths using `malloc` and dynamic `realloc` arrays.

* **Memory Management** - Safely handles the allocated memory and freeing it wherever required using a `cleanup()` function for easy memory cleaup.
 
* **Command Execution** - Safely forks child processes and executes system executables (e.g., `ping`, `grep`, `mkdir`, etc).

* **Signal Handling** - Manages signals (like catching SIGINT for `Ctrl+C`) so that pressing it doesn't accidentally kill your main shell process while it's waiting for commands.

* **Built-in Commands** - 
  * `echo`: Prints the arguments typed by the user through the terminal screen.
  * `cd`: Changes directories natively in the parent process, falling back to the `HOME` environment variable if no path is provided.
  * `ls`: Custom directory reader that lists files cleanly and automatically filters out hidden files.
  * `pwd`: Displays the current working directory i.e. the current location of user in the system.
  * `exit`: Safely frees all dynamically allocated memory before terminating.

* **Error Handling** - Properly exits or gives proper error message when some error occurs.

* **Tokenization and String Parsing** - User arguments are tokenized and parsed using `getword()` function.

* **Pipe (`|`)** - Connects two distinct commands using UNIX pipes. Safely reaps child processes using targeted `waitpid()` calls. 

* **Modular Architecture** - Functions are separated out into distinct files for their particular uses, in order to improve readability, maintainance, and structure of the code.

### The Files

* `main.c` - The main C file containing the source code.

* `cleanup.c` - The file contains the function that is called to free the allocated memory.

* `command.c` - File containing the function called when User passes arguments by typing inside the terminal.

* `getword.c` - Function inside this file extracts a single word and returns the array.

* `pipe.c` - The file containing the implementation for UNIX pipes, allowing user to redirect output of one command to the input of another command.

* `functions.h` - This header file contains the declarations of the functions used throughout the program as well as defined constants.

* `Makefile` - Easy building of the code for easy compiling, cleaning and memory testing.

* `.gitignore` - Ignores the executable from tracking.

* `README.md` - Project Documentation.


## How to Compile and Run

Make sure you have `gcc`, `make` and `valgrind` installed on your Linux environment.

### Compile the Shell

* Type `make` to generate the `shell` executable.

* Run the shell with `./shell`.

* Test memory leaks and errors with `make valgrind`.

* Use `make clean` to remove the compiled executable.


## Lesson Learned

The development of this shell has provided a deep insight on how the UNIX shell actually functions, majorly the functionality of `fork()`,`pipe()`, `dup2()` and `exec()` commands. This also allowed me to understand the drawbacks and advantages of dynamic memory allocation as well as securely applying it. 

## References & Acknowledgments

- **Linux Manual Pages**: `man 2 fork`, `man 2 execvp`, `man 2 waitpid`, `man 2 pipe`, `man 3 ctype`.
- **General Concepts & Tutorials**: Conceptual guidance on UNIX system calls, process management, and POSIX shell mechanics from various online C programming resources and system programming tutorials.
