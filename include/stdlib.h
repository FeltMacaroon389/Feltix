#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

float atof(const char *str);
int is_valid_float(const char *str);
void reverse_string(char* str, int len);
int int_to_str(int num, char* str, int precision);
void float_to_str(float num, char* str, int precision);

#endif // STDLIB_H

