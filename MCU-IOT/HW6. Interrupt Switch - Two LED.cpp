#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

ISR(INT1_vect)
{
	int T = 2;
	while(T--) {
		for(PORTG = 0x00; PORTG < 0x04; PORTG++) {
			_delay_ms(1000);
		}
	}
}
ISR(INT3_vect)
{
	PORTB ^= 0x02;
}

int main(void)
{
	DDRG = DDRB = 0x03;
	
	// Set INT1, INT 3
	EIMSK = (0x02|0x08);
	
	// PORTD
	EICRA = (0x0C|0xC0);	// Rising Edge detection N = 1, N = 3
	
	// Global Interrupt Enable
	SREG |= 0x80;	
	while (1)
	{
	}
}
