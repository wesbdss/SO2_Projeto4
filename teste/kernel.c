#include "include/screen.h"
kmain()
{
	char *vidmem = (char*) 0xb8000;
	vidmem[0] = '\'T\'';
	vidmem[1] = 0x02; /* cor do caracter: verde */
	vidmem[2] = '\'X\'';
	vidmem[3] = 0x03; /* cor do caracter: verde */
	clearLine(0,20);
	print("1vamo jogar HABBO!\n ");
	print("2vamo jogar HABBO!");
}
