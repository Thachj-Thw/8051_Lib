#include <REGX51.H>
#include "UART.h"


static const unsigned int code COEFFICIENT = XTAL_FREQ / 384;


void UART_init(unsigned int baud_rate)
{
	SCON = 0x50;														// set uart mode 1, receive enable; SM0=0 SM1=1 REN=1
	TMOD = (TMOD & 0x0F) | 0x20;						// set timer1 mode 2 and keep mode of timer0
	// caculate timer overflow
	if (COEFFICIENT % baud_rate != 0)
	{
		PCON |= 0x80;													// PCON.7(SMOD) = 1 for baud_rate * 2
		TH1 = 256 - (2 * COEFFICIENT) / baud_rate;				// 256 - (2 * crystal / (12 * 32))/baud
	}
	else
	{
		PCON &= 0x7F;													// PCON.7 (SMOD) = 0
		TH1 = 256 - COEFFICIENT / baud_rate;				// 256 - (crystal / (12 * 32))/baud
	}
	TR1 = 1;																// Start timer1
}

void UART_putchar(char c)
{
	SBUF = c;
	while (!TI);
	TI = 0;
}

void UART_getchar(char* c)
{	
	while (!RI);
	*c = SBUF;
	RI = 0;
}

void UART_print(char* str)
{
	while (*str)
		UART_putchar(*str++);
}

void UART_println(char* str)
{
	UART_print(str);
	UART_putchar('\r');
	UART_putchar('\n');
}

int _UART_read(char buffer[], int maxlen)
{
	int i, cd;
	for (i = 0; i < maxlen; i++)
	{
		cd = 12300;
		while (!RI)
			if (!--cd)
			{
				buffer[i] = '\0';
				return i;
			}
		buffer[i] = SBUF;
		RI = 0;
	}
	return i;
}

int _UART_read_until(char buffer[], int maxlen, char end)
{
	int i;
	char c;
	for (i = 0; i < maxlen; i++)
	{
		UART_getchar(&c);
		if (c == end)
		{
			buffer[i] = '\0';
			return i;
		}
		buffer[i] = c;
	}
	return i;
}

bit UART_available()
{
	return RI;
}

void UART_clear()
{
	while (RI)
		RI = 0;
}
