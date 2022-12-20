#include "xbr820_flash.h"
#include "xbr820.h"

int main()
{
    int a = 0x55AA55AA;
	int b = 0;
	
	flashChipErase();
	
	flashSectErase(0x1000);
	flashProgram(0x1000, (uint8_t*)&a, sizeof(a));
	flashRead((uint8_t*)&b, 0x1000, sizeof(b));
	
}
