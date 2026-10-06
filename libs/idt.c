#include "idt.h"
#include "io.h"

/* 全局 IDT 和指针 */
static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr   idtp;

/* 汇编桩，定义在 kernel.asm 里 */
extern void keyboard_handler_asm(void);
extern void timer_handler_asm(void);

void idt_set_gate(uint8_t num, uint32_t handler,
                  uint16_t selector, uint8_t flags) {
    idt[num].offset_low  = handler & 0xFFFF;
    idt[num].selector    = selector;
    idt[num].zero        = 0;
    idt[num].type_attr   = flags;
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_load(struct idt_ptr *ptr) {
    __asm__ volatile ("lidt %0" : : "m"(idtp));
}

void idt_init(void) {
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    /* 先全部清零 */
    for (int i = 0; i < IDT_ENTRIES; i++)
        idt_set_gate(i, 0, 0, 0);

    /* 注册中断 */
    idt_set_gate(IRQ0,  (uint32_t)timer_handler_asm,    KERNEL_CS, IDT_GATE_KERNEL);
    idt_set_gate(IRQ1,  (uint32_t)keyboard_handler_asm, KERNEL_CS, IDT_GATE_KERNEL);

    /* 加载 IDT */
    idt_load(&idtp);
}

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

void pic_remap(void) {
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);
    outb(PIC1_DATA, 0x20);   // 主 PIC 起始中断号 32
    outb(PIC2_DATA, 0x28);   // 从 PIC 起始中断号 40
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, 0x00);
    outb(PIC2_DATA, 0x00);
}
