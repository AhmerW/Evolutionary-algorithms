#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "functions.h"

int random_value(const int lower, const int upper) {
    return rand() % (upper - lower + 1) + lower;
}
float random_float(const float lower, const float upper )
{
    float scale = rand() / (float) RAND_MAX; 
    return lower + scale * ( upper - lower );     
}

int from_binary(const char* str) {
    return (int)strtol(str, NULL, 2);
}


char** split_string(char* str, int index){
    /*Splits string at index and returns two strings (pointer to char*)*/
    int size = strlen(str);
    char* first = (char*)malloc((index + 5) * sizeof(char));
    char* second = (char*)malloc((size - index + 1) * sizeof(char));
    for (int i = 0; i < index + 1; i++) {
        first[i] = str[i];
    }
    first[index + 1] = '\0';
    int c = 0;
    for (int j = index + 1; j < size; j++) {
        second[c] = str[j];
        c++;
    }
    second[c] = '\0';
    char** output = (char**)malloc(2 * sizeof(char*));
    output[0] = first;
    output[1] = second;
    return output;
    
}
