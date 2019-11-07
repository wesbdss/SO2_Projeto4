bash nasm -f elf32 kernel.asm -o kasm.o
bash gcc -m32 -c -w kernel.c -o kc.o
bash ld -m elf_i386 -T link.ld -o kernel.bin kasm.o kc.o
pause