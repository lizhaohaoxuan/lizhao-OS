#include "keyboard.h"
#include "io.h"
#include "print.h"

#define BUF_SIZE 256
static volatile char kbd_buf[BUF_SIZE];
static volatile int  kbd_head = 0;
static volatile int  kbd_tail = 0;
static int shift_pressed = 0;

static const char keymap[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,  'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,  '\\','z','x','c','v','b','n','m',',','.','/',
    0,  '*', 0, ' ',
};

void keyboard_handler(void) {
    uint8_t sc = inb(0x60);

    if (sc == 0x2A || sc == 0x36) { shift_pressed = 1; outb(0x20,0x20); return; }
    if (sc == 0xAA || sc == 0xB6) { shift_pressed = 0; outb(0x20,0x20); return; }
    if (sc & 0x80) { outb(0x20,0x20); return; }   // 松开

    char c = keymap[sc];
    if (shift_pressed && c >= 'a' && c <= 'z') c -= 32;
    if (c) {
        int next = (kbd_head + 1) % BUF_SIZE;
        if (next != kbd_tail) {
            kbd_buf[kbd_head] = c;
            kbd_head = next;
        }
    }
    print_char(5, 30, 'c', COLOR_WHITE, COLOR_BLACK);
	outb(0x20, 0x20);   // EOI
}

int keyboard_getchar(void) {
    if (kbd_head == kbd_tail) return -1;
    char c = kbd_buf[kbd_tail];
    kbd_tail = (kbd_tail + 1) % BUF_SIZE;
    return c;
}
