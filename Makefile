COMPILER = gcc
LINKER = ld
ASSEMBLER = nasm
CFLAGS = -m32 -c -ffreestanding
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T src/link.ld
EMULATOR = qemu-system-i386
EMULATOR_FLAGS = -kernel
SRCS = src/kernel.asm src/kernel.c src/idt.c src/isr.c src/util.c
OBJS = obj/kasm.o obj/kc.o obj/idt.o obj/isr.o obj/util.o
OUTPUT = B.OS/boot/kernel.bin
# run: link 
# 	$(EMULATOR) $(EMULATOR_FLAGS) $(OUTPUT) qemu-system-i386 --kernel B.OS/boot/kernel.bin

run: link

link: compile $(OBJS)
	rm -rf B.OS
	mkdir B.OS
	mkdir B.OS/boot
	$(LINKER) $(LDFLAGS) -o $(OUTPUT) obj/kasm.o obj/kc.o
compile: $(SRCS)
	rm obj/ -rf
	mkdir obj/
obj/kasm.o: src/kernel.asm
	$(ASSEMBLER) $(ASFLAGS) -o obj/kasm.o src/kernel.asm
obj/kc.o: src/kernel.c
	$(COMPILER) $(CFLAGS) src/kernel.c -o obj/kc.o
obj/idt.o: src/idt.c
	$(COMPILER) $(CFLAGS) src/idt.c -o obj/idt.o
obj/isr.o: src/isr.c
	$(COMPILER) $(CFLAGS) src/isr.c -o obj/isr.o
obj/util.o: src/util.c
	$(COMPILER) $(CFLAGS) src/util.c -o obj/util.o
build:
# Activate the install xorr if you do not have it already installed
# sudo apt install xorriso
	rm B.OS/boot/grub/ -rf
	mkdir B.OS/boot/grub
	echo set default=0 >> B.OS/boot/grub/grub.cfg
	echo set timeout=0 >> B.OS/boot/grub/grub.cfg
	echo menuentry "B.OS" { >> B.OS/boot/grub/grub.cfg

	echo set root='(hd96)' >> B.OS/boot/grub/grub.cfg
	echo multiboot /boot/kernel.bin >> B.OS/boot/grub/grub.cfg
	echo } >> B.OS/boot/grub/grub.cfg
	grub-mkrescue -o B.OS.iso B.OS/

all: run build

clean:
	rm -rf obj/
	rm -rf B.OS/
	rm B.OS.iso