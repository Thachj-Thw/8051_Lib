#include "delay.h"

static unsigned int _1ms;


void delay_init(unsigned long crystal)
{
	// Machine cycle time =  1/(cystal / 12e6) (us)
	// for 1ms need 1000 / (11.494 * machine cycle time)
	// 11.494 is constant tested on simulation
	_1ms = 1000 / (11.494 / (crystal / 12000000.0));
}

void delay(unsigned int ms)
{
	unsigned int i;
	while (ms--)
		for (i=_1ms; i>0; i--);
}