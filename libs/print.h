#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>

enum vga_color {
    COLOR_BLACK = 0,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHT_GREY,
    COLOR_DARK_GREY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_LIGHT_BROWN,
    COLOR_WHITE,
};

// VGA 文本模式显存
extern volatile uint16_t* vga_buffer;

void clean_screen(void);

static inline uint16_t get_vga_char_entry(char c, uint8_t fg, uint8_t bg);

void print_char(uint16_t row, uint16_t col, char c, uint8_t fg, uint8_t bg);

void print_string(uint16_t row, uint16_t col, const char *str,
                  uint8_t fg, uint8_t bg);
#endif
