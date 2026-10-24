BUILDS = builds/
LIBS = libs/
DIST = dist/
ISO = iso/
OBJECTS = kernel_asm.o kernel_c.o print.o cursor.o idt.o keyboard.o timer.o console.o lineedit.o error.o

.PHONY: clean all copy

all: clean os.iso copy

os.iso: kernel.elf
	grub-mkrescue -o $(DIST)os.iso $(ISO)

kernel.elf: $(OBJECTS)
	cp linker.ld $(BUILDS); \
	cd $(BUILDS); \
	ld -m elf_i386 -T linker.ld $(OBJECTS) -o kernel.elf; \
	cd ../; \
	cp $(BUILDS)kernel.elf $(ISO)boot/

kernel_c.o: kernel.c
	gcc -ffreestanding -nostdlib -m32 -c kernel.c -o $(BUILDS)kernel_c.o

print.o: $(LIBS)print.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)print.c -o $(BUILDS)print.o

cursor.o: $(LIBS)cursor.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)cursor.c -o $(BUILDS)cursor.o

idt.o: $(LIBS)idt.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)idt.c -o $(BUILDS)idt.o

keyboard.o: $(LIBS)keyboard.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)keyboard.c -o $(BUILDS)keyboard.o

timer.o: $(LIBS)timer.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)timer.c -o $(BUILDS)timer.o

console.o: $(LIBS)console.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)console.c -o $(BUILDS)console.o

lineedit.o: $(LIBS)lineedit.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)lineedit.c -o $(BUILDS)lineedit.o

error.o: $(LIBS)error.c
	gcc -ffreestanding -nostdlib -m32 -c $(LIBS)error.c -o $(BUILDS)error.o

kernel_asm.o: kernel.asm
	nasm -f elf32 kernel.asm -o $(BUILDS)kernel_asm.o

clean:
	cd $(BUILDS); \
	rm -f $(OBJECTS) linker.ld kernel.elf; \
	cd ../; \
	cd $(DIST); \
	rm -f os.iso; \
	cd ../; \
	cd $(ISO)boot/; \
	rm -f kernel.elf

copy:
	cp $(DIST)os.iso /mnt/c/Users/jin/Downloads/isos
