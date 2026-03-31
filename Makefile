CFLAGS = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS = -m elf_i386 -Ttext 0x1000
CC = gcc
LD = ld
NASM = nasm

all: kernel.bin

kernel.bin: boot.o kernel.o
	$(LD) $(LDFLAGS) -o kernel.elf $^
	objcopy -O binary kernel.elf $@

boot.o: boot.asm
	$(NASM) -f elf32 boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

clean:
	rm -f *.o *.elf *.bin

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin