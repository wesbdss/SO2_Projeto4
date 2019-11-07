#!/bin/sh

echo ---Gerando Bibliotecas Include-- 
mkdir include
echo "#ifndef TYPES_H
#define TYPES_H
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long int64;
typedef unsigned long uint64;
typedef char* string;
#endif" > include/types.h
echo "#ifndef STRING_H
#define STRING_H
#include \"types.h\"
uint16 strlength(string ch)
{
uint16 i = 1;
while(ch[i++]);
return --i;
}
#endif" > include/string.h
echo "#ifndef SYSTEM_H
#define SYSTEM_H
#include \"types.h\"
uint8 inportb (uint16 _port)
{
uint8 rv;
__asm__ __volatile__ (\"inb %1, %0\"
: \"=a\" (rv) /* operando de saída */
: \"dN\" (_port)); /* operando de entrada */

return rv;
}
void outportb (uint16 _port, uint8 _data)
{
__asm__ __volatile__ (\"outb %1, %0\"
: /* operando de saída */
: \"dN\" (_port), \"a\" (_data));/* operando de entrada */

}
#endif" > include/system.h
echo "#ifndef SCREEN_H
#define SCREEN_H
#include \"types.h\"
#include \"system.h\"
#include \"string.h\"
int32 cursorX = 0, cursorY = 0;
int32 color = 0x02;
const uint8 sw = 80, sh = 25, sd = 2;
void clearLine(uint8 from, uint8 to)
{
	uint16 i = sw * from * sd;
	string vidmem = (string)0xb8000;
	for (i; i < (sw * (to + 1) * sd); i+=2)
	{
		vidmem[i] = 0x0;
		vidmem[i+1]= 0x02;
		// if(color <= 0xF)
		// 	vidmem[i+1] = color+0x01;
		// else
		// 	color = 0x01;
	}
}
void updateCursor()
{
	unsigned temp;
	temp = cursorY * sw + cursorX;
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}
void clearScreen()
{
	clearLine(0,sh-1);
	cursorX = 0;
	cursorY = 0;
	updateCursor();
}
void scrollUp(uint8 lineNumber)
{
	string vidmem = (string)0xb8000;
	uint16 i = 0;
	for (i; i < sw * (sh - 1) * sd; i++)
	{
		vidmem[i] = vidmem[i + sw * sd * lineNumber];
	}
	clearLine(sh - 1 - lineNumber, sh - 1);
	if ((cursorY - lineNumber) < 0)
	{
		cursorY = 0;
		cursorX = 0;
	}
	else
	{
		cursorY -= lineNumber;
	}
	updateCursor();
}
void newLineCheck()

{
	if(cursorY >= sh-1)
	{
		scrollUp(1);
	}
	}
void printch(char c)
	{
		string vidmem = (string)0xb8000;
		switch(c)
	{
	case (0x08):
	if(cursorX > 0)
	{
		cursorX--;
		vidmem[(cursorY * sw + cursorX)*sd] = 0x00;
	}
	break;
	case (0x09): // Representa a tecla TAB
		cursorX = (cursorX + 8) & ~(8 - 1);
		break;
	case ("\''\\r'\'"):
		cursorX = 0;
		break;
	case ("\''\\n'\'"):
		cursorX = 0;
		cursorY++;
		break;
	default:
		vidmem[((cursorY * sw + cursorX)) * sd] = c;
		if(color <= 0x0F){
			color = color + 0x01;
			vidmem[((cursorY * sw + cursorX)) * sd + 1] = color;
		}
		else{
			color= 0x01;
			vidmem[((cursorY * sw + cursorX)) * sd + 1] = color;
		}
		cursorX++;
		break;
	}
	if (cursorX >= sw)
	{
		cursorX = 0;
		cursorY++;
	}
	newLineCheck();
	updateCursor();
}
void print(string ch)
{
	uint16 i = 0;
	for(i; i < strlength(ch); i++)
	{
		printch(ch[i]);
	}
}

#endif" > include/screen.h

echo ---Criando Arquivos---
echo "OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
	. = 0x100000;
	.text : { *(.text) }
	.data : { *(.data) }
	.bss : { *(.bss) }
}
" > link.ld
echo "bits 32
section 	.text
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002+0x00)
global 		start
extern 		kmain
start:
	cli
	call kmain
	hlt
" > kernel.asm
echo "#include \"include/screen.h\"
kmain()
{
	char *vidmem = (char*) 0xb8000;
	vidmem[0] = '\'T\'';
	vidmem[1] = 0x02; /* cor do caracter: verde */
	vidmem[2] = '\'X\'';
	vidmem[3] = 0x03; /* cor do caracter: verde */
	clearLine(0,20);
	print(\"1vamo jogar HABBO!"'\\n'" \");
	print(\"2vamo jogar HABBO!\");
}" > kernel.c

echo ---Gerando Kernel.bin---
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c -w kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel.bin kasm.o kc.o
echo ---Abrindo kernel.bin com qemu---
qemu-system-i386 --kernel kernel.bin
echo ---Criando estrutura para gerar ISO---
mkdir simple
mkdir simple/boot
cp kernel.bin simple/boot
mkdir simple/boot/grub
echo "set default = 0
set timeout = 0
menuentry \"simpleOS\" {
set root='(hd96)'
multiboot /boot/kernel.bin
}
" > simple/boot/grub/grub.cfg
echo ---Gerando Iso---
grub-mkrescue -o simple.iso simple