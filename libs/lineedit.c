#include "lineedit.h"
#include "print.h"
#include "cursor.h"

void back_space(int row, int col) {
	print_char(row, col, ' ', COLOR_WHITE, COLOR_BLACK);
	vga_set_cursor(row, col);
}
