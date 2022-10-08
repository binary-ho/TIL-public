#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <common.h>

ISR(INT0_vect)
{
	PORTG ^= 0x01;
}

int main(void)
{
	DDRG = 0x03;
	EICRA = 0x03;	// Rising Edge detection
	EIMSK = 0x01;	// Set INT0
	
	SREG |= 0x80;	// Global Interrupt Enable
	while (1)
	{
	}
}
