// For CPU-related information and functionality

#include <cpu.h>

#include <stdint.h>
#include <stdlib.h>

// Helper function for CPUID
void cpuid(int code, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    __asm__ volatile("cpuid"
                     : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                     : "a"(code), "c"(0));
}

// Function that returns the number of accessible CPU threads
char* get_cpu_threads(void) {
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
uint32_t cpu_supports_64bit(void) {
    uint32_t eax, ebx, ecx, edx;

    // Check CPUID for 64-bit mode support
    cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

    // Check bit 29 of EDX for 64-bit support
    uint32_t is_64bit_supported = (edx >> 29) & 1;

    return is_64bit_supported;
}

// Function to get the CPU manufacturer/vendor
void get_cpu_vendor(char *vendor_buffer) {
    uint32_t eax, ebx, ecx, edx;

    cpuid(0, &eax, &ebx, &ecx, &edx);

    // The vendor string is stored in EBX, EDX, ECX in that order
    *(uint32_t *)(vendor_buffer + 0) = ebx;
    *(uint32_t *)(vendor_buffer + 4) = edx;
    *(uint32_t *)(vendor_buffer + 8) = ecx;
    vendor_buffer[12] = '\0';  // Null-terminate string
}

// Function to get the CPU brand (name)
void get_cpu_brand(char *brand_buffer) {
    uint32_t *brand_u = (uint32_t*)brand_buffer;

    cpuid(0x80000002, &brand_u[0], &brand_u[1], &brand_u[2], &brand_u[3]);
    cpuid(0x80000003, &brand_u[4], &brand_u[5], &brand_u[6], &brand_u[7]);
    cpuid(0x80000004, &brand_u[8], &brand_u[9], &brand_u[10], &brand_u[11]);

    brand_buffer[48] = '\0';
}

