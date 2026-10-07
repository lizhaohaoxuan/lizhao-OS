#include "console.h"
#include "print.h"
#include "cursor.h"
#include "keyboard.h"
#include "lineedit.h"

void console_run(void) {
	int cursor_row = get_cursor_row();
	int cursor_col = get_cursor_col();

	while (1) {
		char c = keyboard_getchar();

		if (c == '\n') {
			//TO the lineedit.h
		} else if (c == '\t') {continue;}
		else if (c == '\b') {
			back_space(cursor_row, cursor_col - 1);
            if (cursor_col == 0) {
                cursor_row--;
                cursor_col = 79;
            } else {cursor_col--;}
		}
		else if (c != -1) {
			print_char(cursor_row, cursor_col, c, COLOR_WHITE, COLOR_BLACK);
			cursor_col++;
			if (cursor_col == 80) {
				cursor_row++;
				cursor_col = 0;
			}
		vga_set_cursor(cursor_row, cursor_col);
		}
	}
}
