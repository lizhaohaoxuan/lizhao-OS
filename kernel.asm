; kernel.asm —— Multiboot + 简单 VGA 输出
bits 32

section .multiboot
    align 4
    dd 0x1BADB002
    dd 0x00000003
    dd -(0x1BADB002 + 0x00000003)

section .bss
    align 16
stack_bottom:
    resb 16384
stack_top:

section .data
align 8
gdt_start:
    dq 0x0000000000000000        ; 空描述符
gdt_code:
    dq 0x00CF9A000000FFFF        ; 代码段：base=0, limit=4G, 32位, ring0
gdt_data:
    dq 0x00CF92000000FFFF        ; 数据段：base=0, limit=4G, 32位, ring0
gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start - 1
    dd gdt_start

section .text
global _start
extern kernel_main
extern keyboard_handler
extern timer_handler
_start:
    cli

    ; 加载自己的 GDT
    lgdt [gdt_ptr]

    ; 远跳转设置 CS = 0x08
    jmp 0x08:.reload_cs
.reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, stack_top

    push ebx
    push eax
    call kernel_main

.hang:
    hlt
    jmp .hang

; ============ 中断汇编桩 ============
global keyboard_handler_asm
extern keyboard_handler
keyboard_handler_asm:
    pusha
    call keyboard_handler
    popa
    iret

global timer_handler_asm
extern timer_handler
timer_handler_asm:
    pusha
    call timer_handler
    popa
    iret
