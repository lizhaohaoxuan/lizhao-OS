#ifndef CURSOR_H
#define CURSOR_H
#include <stdint.h>

// 设置光标位置
void vga_set_cursor(uint16_t row, uint16_t col) ;

int get_cursor_row(void) ;

int get_cursor_col(void) ;
#endif
