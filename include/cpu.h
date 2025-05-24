#ifndef CPU_H
#define CPU_H

#include <stdint.h>

void cpuid(int code, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);
char* get_cpu_threads(void);
uint32_t cpu_supports_64bit(void);
void get_cpu_vendor(char *vendor_buffer);
void get_cpu_brand(char *brand_buffer);

#endif // CPU_H

