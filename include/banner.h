#ifndef BANNER_H
#define BANNER_H

#include <vga.h>

// Banner lines definitions
// Default banner generated with: https://www.asciiart.eu/text-to-ascii-art
char banner_line_1[50] = "   _____    _ _   _              \n";
char banner_line_2[50] = "  |  ___|__| | |_(_)_  __        \n";
char banner_line_3[50] = "  | |_ / _ \\ | __| \\ \\/ /     \n";
char banner_line_4[50] = "  |  _|  __/ | |_| |>  <         \n";
char banner_line_5[50] = "  |_|  \\___|_|\\__|_/_/\\_\\    \n";

// Print all-white banner
void print_banner_white() {
    print_string(banner_line_1, VGA_COLOR_WHITE);
    print_string(banner_line_2, VGA_COLOR_WHITE);
    print_string(banner_line_3, VGA_COLOR_WHITE);
    print_string(banner_line_4, VGA_COLOR_WHITE);
    print_string(banner_line_5, VGA_COLOR_WHITE);
}

// Print rainbow banner
void print_banner_rainbow() {
    print_string(banner_line_1, VGA_COLOR_RED);
    print_string(banner_line_2, VGA_COLOR_LIGHT_RED);
    print_string(banner_line_3, VGA_COLOR_GREEN);
    print_string(banner_line_4, VGA_COLOR_BLUE);
    print_string(banner_line_5, VGA_COLOR_MAGENTA);
}


/* Please feel free to request other options or color patterns
 * To do so, open an issue or pull request on the project's GitHub:
 * https://github.com/FeltMacaroon389/Feltix
 */


#endif // BANNER_H

