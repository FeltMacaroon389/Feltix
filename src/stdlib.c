// Minimal standard C library

#include <stdlib.h>

#include <stdint.h>

// Custom atof function as inline
float atof(const char *str) {
    float result = 0.0f;
    float divisor = 1.0f;
    int sign = 1;

    // Handle leading whitespace
    while (*str == ' ') {
        str++;
    }

    // Handle optional sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Process integer part
    while (*str >= '0' && *str <= '9') {
        result = result * 10.0f + (*str - '0');
        str++;
    }

    // Process fractional part
    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            result = result * 10.0f + (*str - '0');
            divisor *= 10.0f;
            str++;
        }
    }

    return sign * result / divisor;
}

// Function to check if a string can be can be converted to a float
int is_valid_float(const char *str) {
    const char *p = str;
    if (p == 0) {
        return 1;
    }

    while (*p == ' ' || *p == '\t' || *p == '\n' ||
           *p == '\r' || *p == '\f' || *p == '\v') {
        p++;
    }

    if (*p == '+' || *p == '-') {
        p++;
    }

    int has_digits = 0;
    while (*p >= '0' && *p <= '9') {
        has_digits = 1;
        p++;
    }

    if (*p == '.') {
        p++;
        while (*p >= '0' && *p <= '9') {
            has_digits = 1;
            p++;
        }
    }

    if (!has_digits) {
        return 1;
    }

    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') {
            p++;
        }

        int exp_digits = 0;
        while (*p >= '0' && *p <= '9') {
            exp_digits = 1;
            p++;
        }

        if (!exp_digits) {
            return 1;
        }
    }

    while (*p == ' ' || *p == '\t' || *p == '\n' ||
           *p == '\r' || *p == '\f' || *p == '\v') {
        p++;
    }

    return *p != '\0';
}

// Function to reverse a string
void reverse_string(char* str, int len) {
    int i = 0, j = len - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Function to convert an integer to a string
int int_to_str(int num, char* str, int precision) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
    } else {
        while (num) {
            str[i++] = (num % 10) + '0';
            num /= 10;
        }
    }

    // Reverse the string since we build it backwards
    reverse_string(str, i);
    str[i] = '\0';
    return i;
}

// Function to convert a float to a string
void float_to_str(float num, char* str, int precision) {
    // Handle sign
    int i = 0;
    if (num < 0) {
        str[i++] = '-';
        num = -num;
    }

    // Extract integer part
    int int_part = (int)num;

    // Extract fractional part
    float frac_part = num - (float)int_part;

    // Convert integer part to string
    i += int_to_str(int_part, str + i, 0);

    // Add decimal point
    str[i++] = '.';

    // Process fractional part
    for (int p = 0; p < precision; p++) {
        frac_part *= 10;
    }
    int frac_as_int = (int)(frac_part + 0.5f); // Round the fractional part
    int_to_str(frac_as_int, str + i, precision);
}

