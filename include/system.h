#ifndef SYSTEM_H
#define SYSTEM_H
#include "types.h"
uint8 inportb (uint16 _port)
{
uint8 rv;
__asm__ __volatile__ ("inb %1, %0"
: "=a" (rv) /* operando de saída */
: "dN" (_port)); /* operando de entrada */

return rv;
}
void outportb (uint16 _port, uint8 _data)
{
__asm__ __volatile__ ("outb %1, %0"
: /* operando de saída */
: "dN" (_port), "a" (_data));/* operando de entrada */

}
#endif
