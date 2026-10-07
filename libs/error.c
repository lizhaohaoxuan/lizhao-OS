#include "print.h"

void show_error(char *str) {
	clean_screen();

	print_string(0, 0,"#EEEE #RRR  #RRR   #OO  #RRR ", COLOR_WHITE, COLOR_BLUE);
    print_string(1, 0,"E     R   R R   R O   O R   R", COLOR_WHITE, COLOR_BLUE);
    print_string(2, 0,"EEEEE RRRR  RRRR  O   O RRRR ", COLOR_WHITE, COLOR_BLUE);
    print_string(3, 0,"E     R R   R R   O   O R R  ", COLOR_WHITE, COLOR_BLUE);
    print_string(4, 0,"EEEE# R  R# R  R#  OO#  R  R#", COLOR_WHITE, COLOR_BLUE);
	print_string(5, 0, "ERROR REASON:", COLOR_WHITE, COLOR_BLACK);
	print_string(5, 14, str, COLOR_RED,COLOR_BLACK);
	__asm__ ("cli");
	__asm__ ("hlt");
}
