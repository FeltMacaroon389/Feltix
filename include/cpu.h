// For CPU-related information and functionality

#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdlib.h>

// Helper function for CPUID
static inline void cpuid(int code, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    __asm__ volatile("cpuid"
                     : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                     : "a"(code), "c"(0));
}

// Function that returns the number of accessible CPU threads
char* get_cpu_threads() {
    static char threads_str[16];
    uint32_t eax, ebx, ecx, edx;

    // Call CPUID to get the number of threads
    cpuid(0x1, &eax, &ebx, &ecx, &edx);

    // Extract number of logical processors (threads) from bits 23:16 in EBX register
    uint32_t cpu_threads = (ebx >> 16) & 0xFF;

    // If 0, set to 1
    if (cpu_threads == 0) {
        cpu_threads = 1;
    }

    // Convert the number of threads to a string and return it
    int_to_str(cpu_threads, threads_str, 0);

    return threads_str;
}

// Function to check if the CPU supports 64-bit
uint32_t cpu_supports_64bit() {
    uint32_t eax, ebx, ecx, edx;

    // Check CPUID for 64-bit mode support
    cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

    // Check bit 29 of EDX for 64-bit support
    uint32_t is_64bit_supported = (edx >> 29) & 1;

    return is_64bit_supported;
}

#endif // CPU_H

