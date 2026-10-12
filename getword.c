#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

char *getword(int x, char *input){
    int start = x;
    int len = 0;

    while (input[x] != '\n' && input[x] != '\0' && !isspace((unsigned char)input[x])){
        x++;
        len++;
    }
    char *arr = malloc(sizeof(char) * (len + 1));
    //changed allocation logic since it caused a buffer overflow before and leaves one space for '\0' so the string always ends properly
    if (arr == NULL){
        fprintf(stderr, "Memory Allocation Error\n");
        exit(1);
    }
    memcpy(arr, &input[start], len);
    arr[len] = '\0';
    //sets last character of the array to '\0' so as to end the array containing the string
    return arr;
}
