#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count_int = 0;

ISR(TIMER0_OVF_vect)
{
	count_int++;
	if (count_int == 244) {
		PORTG ^= 0x03;
		count_int = 0;
	}
}

int main(void)
{
	DDRG = 0x03;
	
	TCCR0 = 0x06;
	TCNT0 = 0x00;
	TIMSK = 0x01;
	SREG |= 0x80;

	while (1)
	{
	}
}
