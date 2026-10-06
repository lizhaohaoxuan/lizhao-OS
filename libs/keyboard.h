#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

void keyboard_handler(void);        // C 处理函数
extern void keyboard_handler_asm(void);  // 汇编桩

#endif
