#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

int random(const int lower, const int upper);
float random_float(const float lower, const float upper);
int from_binary(const char* str);
char** split_string(char* str, const int n);

#endif