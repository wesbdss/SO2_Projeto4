#ifndef KB_H
#define KB_H
#include "screen.h"
#include "system.h"
#include "types.h"
string readStr()
{
	char buff[256];
	string buffstr = buff;
	uint8 i = 0;
	uint8 reading = 1;
	while(reading)
	{
		if(inportb(0x64) & 0x1)
		{
			switch(inportb(0x60))
			{
			case 1:

				printch((char)27);
				buffstr[i] =(char)27;
				i++;
				break;

			case 2:
				printch((char)49);
				buffstr[i] =(char)49;
				i++;
				break;

			case 3:
				printch((char)50);
				buffstr[i] =(char)50;
				i++;
				break;

			case 4:
				printch((char)51);
				buffstr[i] =(char)51;
				i++;
				break;

			case 5:
				printch((char)52);
				buffstr[i] =(char)52;
				i++;
				break;

			case 6:
				printch((char)53);
				buffstr[i] =(char)53;
				i++;
				break;

			case 7:
				printch((char)54);
				buffstr[i] =(char)54;
				i++;
				break;

			case 8:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 9:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 10:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 11:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 12:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 13:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 14:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 8:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 8:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 8:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			case 8:
				printch((char)55);
				buffstr[i] =(char)55;
				i++;
				break;

			}
		}
	}
	buffstr[i] = 0;
	return buffstr;
}
#endif