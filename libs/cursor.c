#include <stdint.h>
#include "cursor.h"
#include "io.h"

// 设置光标位置
void vga_set_cursor(uint16_t row, uint16_t col) {
    uint16_t pos = row * 80 + col;

    // 高字节 → 寄存器 14
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)(pos >> 8));

    // 低字节 → 寄存器 15
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
}
