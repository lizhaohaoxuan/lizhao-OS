#include <stdint.h>
#include "libs/print.h"
#include "libs/cursor.h"
#include "libs/idt.h"
#include "libs/keyboard.h"
#include "libs/console.h"
#include "libs/lineedit.h"
#include "libs/error.h"

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
	vga_set_cursor(2, 17);
	// 检查魔数
    if (magic != 0x2BADB002) {
		show_error("Magic number fualt");  // 红色 X 表示错误
    }
	console_run();
}
