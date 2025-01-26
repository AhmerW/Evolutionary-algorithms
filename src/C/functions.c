#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int random(const int lower, const int upper) {
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

char* split_string(char* str, int index){
    char* output = (char*)malloc((strlen(str) + 1) * sizeof(char));
    return output;
    
}