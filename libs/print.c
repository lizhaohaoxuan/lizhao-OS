#include <stdint.h>
#include "print.h"

// VGA 文本模式显存
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

void clean_screen(void){
    for (int i = 0; i < 80*25; i++) {
    vga_buffer[i] = (0x07 << 8) | ' ';
    }
}

static inline uint16_t get_vga_char_entry(char c, uint8_t fg, uint8_t bg){
    //Get the vga-char entry
    uint8_t attr = fg | (bg << 4);
    return (uint16_t)c | ((uint16_t)attr << 8);
}

void print_char(uint16_t row, uint16_t col, char c, uint8_t fg, uint8_t bg){
    //Print the char
    vga_buffer[row * 80 + col] = get_vga_char_entry(c, fg, bg);
}

void print_string(uint16_t row, uint16_t col, const char *str,
                  uint8_t fg, uint8_t bg){
    while (*str) {
        if (*str == '\n') {
            row++;
            col = 0;
        }
        else {
            print_char(row, col, *str, fg, bg);
            col++;
            if (col >= 80) {   // 一行写满，换行
                col = 0;
                row++;
            }
        }
        str++;
    }
}

void print_hex(uint16_t row, uint16_t col, uint32_t n, uint8_t fg, uint8_t bg) {
    const char *hex = "0123456789ABCDEF";
    print_string(0, 0, "0x", COLOR_WHITE, COLOR_BLACK);
    for (int i = 28; i >= 0; i -= 4) {
        char c = hex[(n >> i) & 0xF];
        print_char(row, col, c, COLOR_WHITE, COLOR_BLACK);
        col++;
    }
}
