#ifndef STRING_H
#define STRING_H

#include <stddef.h>

char* strchr(const char* str, int c);
size_t strlen(const char* str);
void memcpy(char* dest, const char* src, size_t n);
void* memset(void* ptr, int value, size_t num);
int memcmp(const void* ptr1, const void* ptr2, size_t num);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strtok(char* str, const char* delim);
char* strcat(char* dest, const char* src);

#endif // STRING_H

