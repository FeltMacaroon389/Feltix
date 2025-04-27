#include <vga.h>

void kernel_main() {
  clear_screen();
  print_string("Welcome to Feltix!", 0x0F00, 18);
}
