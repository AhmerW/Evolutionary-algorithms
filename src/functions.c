#include <stdio.h>
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

int fromBinary(const char* str) {
    return (int)strtol(str, NULL, 2);
}