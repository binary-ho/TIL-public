#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

ISR(INT5_vect)
{
	int T = 2;
	while(T--) {
		PORTC ^= 0x01;
		_delay_ms(500);
	}
}

int main(void)
{
	DDRC = 0x01;	
	
	// Set INT 5
	EIMSK = 0x20;
	
	// PORTE
	EICRB = 0x0C;	// Rising Edge detection N = 5
	
	// Global Interrupt Enable
	SREG |= 0x80;	
	while (1)
	{
	}
}
