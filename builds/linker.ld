ENTRY(_start)

SECTIONS
{
    . = 0x100000;                /* GRUB 加载到 1MB */

    .text ALIGN(4K) : {
        *(.multiboot)           /* 必须最前 */
        *(.text)
    }

    .rodata ALIGN(4K) : {
        *(.rodata)
        *(.rodata.*)
    }

    .data ALIGN(4K) : {
        *(.data)
        *(.data.*)
    }

    .bss ALIGN(4K) : {
        *(COMMON)               /* 未初始化全局变量 */
        *(.bss)
        *(.bss.*)
    }

    kernel_end = .;             /* 内核结束地址，备用 */
}
