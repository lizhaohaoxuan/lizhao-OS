#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* IDT 表项数量 */
#define IDT_ENTRIES 256

/* 段选择子：内核代码段（GRUB multiboot 下通常是 0x08） */
#define KERNEL_CS   0x08

/* 门类型属性 */
#define IDT_FLAG_PRESENT   0x80   // bit7: 存在
#define IDT_FLAG_RING0     0x00   // bit5-6: 特权级 0
#define IDT_FLAG_RING3     0x60   // 特权级 3（用户态可调用）
#define IDT_FLAG_INT_GATE  0x0E   // 32 位中断门
#define IDT_FLAG_TRAP_GATE 0x0F   // 32 位陷阱门

/* 常用组合：存在 + ring0 + 32位中断门 = 0x8E */
#define IDT_GATE_KERNEL    (IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_INT_GATE)
/* 用户态可调用：存在 + ring3 + 32位中断门 = 0xEE */
#define IDT_GATE_USER      (IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INT_GATE)

/* 中断号常量 */
#define IRQ0  32    // 时钟
#define IRQ1  33    // 键盘
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44    // 鼠标
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

/* IDT 表项结构（8 字节，必须 packed） */
struct idt_entry {
    uint16_t offset_low;    // 处理函数地址低 16 位
    uint16_t selector;      // 代码段选择子
    uint8_t  zero;          // 保留，填 0
    uint8_t  type_attr;     // 属性
    uint16_t offset_high;   // 处理函数地址高 16 位
} __attribute__((packed));

/* IDTR 寄存器加载用的结构 */
struct idt_ptr {
    uint16_t limit;         // IDT 大小 - 1
    uint32_t base;          // IDT 起始地址
} __attribute__((packed));

/* 函数声明 */
void idt_init(void);

void idt_set_gate(uint8_t num, uint32_t handler,
                  uint16_t selector, uint8_t flags);

void idt_load(struct idt_ptr *ptr);

void pic_remap(void);
#endif
