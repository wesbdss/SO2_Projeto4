#ifndef SCREEN_H
#define SCREEN_H
#include "types.h"
#include "system.h"
#include "string.h"
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
	case ('\r'):
		cursorX = 0;
		break;
	case ('\n'):
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

#endif
