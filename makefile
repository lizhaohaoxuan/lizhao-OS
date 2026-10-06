.PHONY: clean all copy

all: clean os.iso copy

os.iso: kernel.elf
	grub-mkrescue -o os.iso iso/

kernel.elf: linker.ld kernel_asm.o kernel_c.o print.o cursor.o idt.o keyboard.o timer.o
	ld -m elf_i386 -T linker.ld kernel_asm.o kernel_c.o print.o cursor.o idt.o keyboard.o timer.o -o kernel.elf
	cp kernel.elf iso/boot/

kernel_c.o: kernel.c
	gcc -ffreestanding -nostdlib -m32 -c kernel.c -o kernel_c.o

print.o: libs/print.c libs/print.h
	gcc -ffreestanding -nostdlib -m32 -c libs/print.c -o print.o

cursor.o: libs/cursor.c libs/cursor.h libs/io.h
	gcc -ffreestanding -nostdlib -m32 -c libs/cursor.c -o cursor.o

idt.o: libs/idt.c libs/idt.h
	gcc -ffreestanding -nostdlib -m32 -c libs/idt.c -o idt.o

keyboard.o: libs/keyboard.c libs/keyboard.h libs/io.h
	gcc -ffreestanding -nostdlib -m32 -c libs/keyboard.c -o keyboard.o

timer.o: libs/timer.c libs/timer.h libs/io.h
	gcc -ffreestanding -nostdlib -m32 -c libs/timer.c -o timer.o

kernel_asm.o: kernel.asm
	nasm -f elf32 kernel.asm -o kernel_asm.o

clean:
	rm -f kernel_c.o kernel_asm.o print.o kernel.elf cursor.o

copy:
	cp os.iso /mnt/c/Users/jin/Downloads/isos
