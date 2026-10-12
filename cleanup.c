#include <stdlib.h>
#include "functions.h"

void cleanup(char *input, char **args, int count){
if (args != NULL) {
        for (int k = 0; k < count; k++) {
            //changed counter since it won't free NULL if it used instead
            free(args[k]);
            //frees each slot of the array
        }
        free(args);
        //frees the array as a whole in structure
    }
    if (input != NULL) {
        free(input);
        //frees the input used to store the arguments
    }
}
