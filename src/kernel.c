// #include "../include/shell.h"

kmain()
{
	isr_install();
	clearScreen();


	char *vidmem = (char*) 0xb8000;
	print("Bem vindo ao B.OS ------->\n\n\n\nEntre um comando\n");
	print("\n");
	launch_shell(0);

	
}
