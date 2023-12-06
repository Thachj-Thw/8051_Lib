#include "delay.h"


static unsigned int _1ms = 1000 / (11.23595 / (XTAL_FREQ / 12000000.0));



void delay(unsigned int ms)
{
	unsigned int i;
	while (ms--)
		for (i=_1ms; i>0; i--);
}
