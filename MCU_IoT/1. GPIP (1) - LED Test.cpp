#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRG = 0x03;	// D0 & D1: OUTPUT, D2 & D3 : INPUT
    /* Replace with your application code */
    while (1) 
    {
		PORTG = 0x01;
		_delay_ms(1000);
		PORTG = 0x02;
		_delay_ms(1000);
	}
}
