// Simple power control

#include <power.h>

#include <io.h>

// Trigger a hardware reboot via the PS/2 controller
void reboot_system(void) {
    outb(0x64, 0xFE);

    // If that fails, try unknown instruction to force a triple fault
    __asm__ __volatile__("ud2");

    // If that *still* doesn't work, settle with a halt
    __asm__ __volatile__("hlt");
}

