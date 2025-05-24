// Basic string manipulation library

#include <string.h>

#include <stdint.h>

// Minimal implementation of strchr
char* strchr(const char* str, int c) {
    while (*str) {
        if (*str == (char)c) {
            return (char*)str;
        }
        str++;
    }

    return NULL;
}

// Minimal implementation of strlen
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    return len;
}

// Minimal implementation of memcpy
void memcpy(char* dest, const char* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Minimal implementation of memset
void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }

    return ptr;
}

// Minimal implementation of memcmp
int memcmp(const void* ptr1, const void* ptr2, size_t num) {
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;

    for (size_t i = 0; i < num; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }

    return 0;
}

// Minimal implementation of strcmp
int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

// Minimal implementation of strncmp
int strncmp(const char* s1, const char* s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
        if (s1[i] == '\0') {
            return 0;
        }
    }

    return 0;
}

// Minimal implementation of strtok
char* strtok(char* str, const char* delim) {
    static char* last;
    if (str == NULL) {
        str = last;
    }

    if (str == NULL) {
        return NULL;
    }

    // Skip leading delimiters
    while (*str && strchr(delim, *str)) {
        str++;
    }

    if (*str == '\0') {
        return NULL;
    }

    char* token = str;

    // Find the end of the token
    while (*str && !strchr(delim, *str)) {
        str++;
    }

    if (*str) {
        *str = '\0';
        last = str + 1;

    } else {
        last = NULL;
    }

    return token;
}

// Minimal implementation of strcat
char* strcat(char* dest, const char* src) {
    char* original = dest;

    // Move to the end of dest string
    while (*dest) {
        dest++;
    }

    // Copy src to the end of dest
    while (*src) {
        *dest++ = *src++;
    }

    *dest = '\0'; // Null-terminate the result

    return original;
}

