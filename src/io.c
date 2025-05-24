// Simple Input/Output port access

#include <io.h>

#include <stdint.h>

// Function to read a byte from an I/O port
uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Function to write a byte to an I/O port
void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

