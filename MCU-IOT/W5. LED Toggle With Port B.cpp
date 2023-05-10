#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x01;
	DDRG = 0x00;
	// PORTB = 0x00;
	unsigned char keyin;
	while (1)
	{
		keyin = (PING&0x0C) >> 2;
		if(keyin) {
			PORTB^= 0x01;
			_delay_ms(500);	
		}
	}
}
