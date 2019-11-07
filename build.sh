#!/bin/sh
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c -w kernel.c -o kc.o -ffreestanding
ld -m elf_i386 -T link.ld -o kernel.bin kasm.o kc.o
