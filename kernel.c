#include <stdint.h>
#include "libs/print.h"
#include "libs/cursor.h"
#include "libs/idt.h"
#include "libs/keyboard.h"

static uint8_t cursor_row;
static uint8_t cursor_col;

void setup() {
    // 清屏（黑底白字）
    clean_screen();

    pic_remap();
	idt_init();

	__asm__ volatile ("sti");   //开中断
}

void kernel_main(uint32_t magic, uint32_t* mbd) {
	setup();
    // 显示
    print_string(0, 0, "Lizhaoli OS", COLOR_WHITE, COLOR_BLACK);
	print_string(2, 0, "kernel@computer# ", COLOR_WHITE, COLOR_BLACK);

	cursor_row = 2;
	cursor_col = 17;

	while (1) {
		int c = keyboard_getchar();
		if (c != -1) {
			print_char(cursor_row, cursor_col, c, COLOR_WHITE, COLOR_BLACK);

		if (cursor_col == 80) {cursor_row++; cursor_col = 0; }
		else cursor_col++;

		} else{
		__asm__ volatile ("hlt");
		}
	}
	// 检查魔数
    if (magic != 0x2BADB002) {
    print_char(0, 0, 'X', COLOR_RED, COLOR_BLACK);  // 红色 X 表示错误
    }
}
