
Objects = kernel_asm.o kernel_c.o print.o cursor.o idt.o keyboard.o timer.o console.o lineedit.o error.o

.PHONY: clean all copy

all: clean os.iso copy

os.iso: kernel.elf
	grub-mkrescue -o os.iso iso/

kernel.elf: $(Objects)
	ld -m elf_i386 -T linker.ld $(Objects) -o kernel.elf
	cp kernel.elf iso/boot/

kernel_c.o: kernel.c
	gcc -ffreestanding -nostdlib -m32 -c kernel.c -o kernel_c.o

print.o: libs/print.c
	gcc -ffreestanding -nostdlib -m32 -c libs/print.c -o print.o

cursor.o: libs/cursor.c
	gcc -ffreestanding -nostdlib -m32 -c libs/cursor.c -o cursor.o

idt.o: libs/idt.c
	gcc -ffreestanding -nostdlib -m32 -c libs/idt.c -o idt.o

keyboard.o: libs/keyboard.c
	gcc -ffreestanding -nostdlib -m32 -c libs/keyboard.c -o keyboard.o

timer.o: libs/timer.c
	gcc -ffreestanding -nostdlib -m32 -c libs/timer.c -o timer.o

console.o: libs/console.c
	gcc -ffreestanding -nostdlib -m32 -c libs/console.c -o console.o

lineedit.o: libs/lineedit.c
	gcc -ffreestanding -nostdlib -m32 -c libs/lineedit.c -o lineedit.o

error.o: libs/error.c
	gcc -ffreestanding -nostdlib -m32 -c libs/error.c -o error.o

kernel_asm.o: kernel.asm
	nasm -f elf32 kernel.asm -o kernel_asm.o

clean:
	rm -f $(Objects) kernel.elf os.iso

copy:
	cp os.iso /mnt/c/Users/jin/Downloads/isos
