// For CPU-related information

#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdlib.h>
#include <vga.h>

// Helper function for CPUID
static inline void cpuid(int code, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    __asm__ volatile("cpuid"
                     : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                     : "a"(code), "c"(0));
}

// Function to print all accessible CPU threads
void print_cpu_threads() {
    uint32_t eax, ebx, ecx, edx;

    // Call CPUID to get the number of threads
    cpuid(0x1, &eax, &ebx, &ecx, &edx);

    // Extract number of logical processors (threads) from bits 23:16 in EBX register
    uint32_t cpu_threads = (ebx >> 16) & 0xFF;

    // Convert the number of threads to a string and print it
    char thread_str[16];
    int_to_str(cpu_threads, thread_str, 0);

    print_string("CPU threads: ", VGA_COLOR_WHITE);
    print_string(thread_str, VGA_COLOR_LIGHT_GREY);
    print_string("\n", VGA_COLOR_WHITE);
}

// Function to print the CPU mode (architecture)
void print_cpu_mode() {
    uint32_t eax, ebx, ecx, edx;

    // Check CPUID for 64-bit mode support
    cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

    // Check bit 29 of EDX for 64-bit support
    uint32_t is_64bit_supported = (edx >> 29) & 1;

    // Print result
    print_string("CPU architecture: ", VGA_COLOR_WHITE);

    if (is_64bit_supported) {
        print_string("x86_64\n\n", VGA_COLOR_LIGHT_GREY);
    } else {
        print_string("x86\n\n", VGA_COLOR_LIGHT_GREY);
    }
}

#endif
