#include "../include/kb.h"

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
				printch((char)56);
				buffstr[i] =(char)56;
				i++;
				break;

			case 10:
				printch((char)57);
				buffstr[i] =(char)57;
				i++;
				break;

			case 11:
				printch((char)48);
				buffstr[i] =(char)48;
				i++;
				break;

			case 12:
				printch((char)45);
				buffstr[i] =(char)45;
				i++;
				break;

			case 13:
				printch((char)61);
				buffstr[i] =(char)61;
				i++;
				break;

			case 14:
				printch((char)8);
				buffstr[i] =(char)8;
				i++;
				break;

			case 15:
				printch((char)9);
				buffstr[i] =(char)9;
				i++;
				break;

			case 16:
				printch((char)113);
				buffstr[i] =(char)113;
				i++;
				break;

			case 17:
				printch((char)119);
				buffstr[i] =(char)119;
				i++;
				break;

			case 18:
				printch((char)101);
				buffstr[i] =(char)101;
				i++;
				break;

			case 19:
				printch((char)114);
				buffstr[i] =(char)114;
				i++;
				break;

			case 20:
				printch((char)116);
				buffstr[i] =(char)116;
				i++;
				break;

			case 21:
				printch((char)121);
				buffstr[i] =(char)121;
				i++;
				break;
			case 22:
				printch((char)117);
				buffstr[i] =(char)117;
				i++;
				break;

			case 23:
				printch((char)105);
				buffstr[i] =(char)105;
				i++;
				break;

			case 24:
				printch((char)111);
				buffstr[i] =(char)111;
				i++;
				break;

			case 25:
				printch((char)112);
				buffstr[i] =(char)112;
				i++;
				break;

			case 26:
				printch((char)91);
				buffstr[i] =(char)91;
				i++;
				break;
			case 27:
				printch((char)93);
				buffstr[i] =(char)93;
				i++;
				break;

			case 28:
				printch((char)13);
				buffstr[i] ='\0';
				i++;
				reading = 0;
				break;

			case 29:
				break;

			case 30:
				printch((char)97);
				buffstr[i] =(char)97;
				i++;
				break;

			case 31:
				printch((char)115);
				buffstr[i] =(char)115;
				i++;
				break;

			case 32:
				printch((char)100);
				buffstr[i] =(char)100;
				i++;
				break;

			case 33:
				printch((char)102);
				buffstr[i] =(char)102;
				i++;
				break;

			case 34:
				printch((char)103);
				buffstr[i] =(char)103;
				i++;
				break;

			case 35:
				printch((char)104);
				buffstr[i] =(char)104;
				i++;
				break;

			case 36:
				printch((char)106);
				buffstr[i] =(char)106;
				i++;
				break;

			case 37:
				printch((char)107);
				buffstr[i] =(char)107;
				i++;
				break;

			case 38:
				printch((char)108);
				buffstr[i] =(char)108;
				i++;
				break;

			case 39:
				printch((char)59);
				buffstr[i] =(char)59;
				i++;
				break;

			case 40:
				printch((char)39);
				buffstr[i] =(char)39;
				i++;
				break;

			case 41:
				printch((char)96);
				buffstr[i] =(char)96;
				i++;
				break;

			case 42:
				break;

			case 43:
				printch((char)92);
				buffstr[i] =(char)92;
				i++;
				break;
			case 44:
				printch((char)122);
				buffstr[i] =(char)122;
				i++;
				break;

			case 45:
				printch((char)120);
				buffstr[i] =(char)120;
				i++;
				break;

			case 46:
				printch((char)99);
				buffstr[i] =(char)99;
				i++;
				break;

			case 47:
				printch((char)118);
				buffstr[i] =(char)118;
				i++;
				break;

			case 48:
				printch((char)98);
				buffstr[i] =(char)98;
				i++;
				break;

			case 49:
				printch((char)110);
				buffstr[i] =(char)110;
				i++;
				break;

			case 50:
				printch((char)109);
				buffstr[i] =(char)109;
				i++;
				break;

			case 51:
				printch((char)44);
				buffstr[i] =(char)44;
				i++;
				break;

			case 52:
				printch((char)46);
				buffstr[i] =(char)46;
				i++;
				break;
			case 53:
				printch((char)47);
				buffstr[i] =(char)47;
				i++;
				break;

			case 54:
				break;
				
			case 55:
				printch((char)42);
				buffstr[i] =(char)42;
				i++;
				break;

			case 56:
				break;
			case 57:
				printch((char)32);
				buffstr[i] =(char)32;
				i++;
				break;
			}
		}
	}
	buffstr[i] = 0;
	return buffstr;
}