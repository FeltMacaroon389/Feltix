#ifndef VGA_H
#define VGA_H

#define VGA_BASE_ADDRESS 0xb8000

void print_string(char *message, short color, int message_length) {
  short *vga = (short *)VGA_BASE_ADDRESS;
  for (int i = 0; i < message_length; i++) {
    vga[i + 80] = color | message[i];
  }
}

#endif // VGA_H

