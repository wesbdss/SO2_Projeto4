//#include "../include/screen.h"

// #include "../include/shell.h"

kmain()
{
	isr_install();
	clearScreen();


	char *vidmem = (char*) 0xb8000;
	vidmem[0] = 'T';
	vidmem[1] = 0x02; /* cor do caracter: verde */
	vidmem[2] = 'X';
	vidmem[3] = 0x03; /* cor do caracter: verde */
	clearLine(0,20);
	print("Bem vindo ao B.OS ------->\n\n\n\nEntre um comando\n");
	print("\n");
	launch_shell(0);

	
}
