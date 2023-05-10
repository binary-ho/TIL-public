#define F_CPU 16000000
#include <avr/io.h>
#include <avr/delay.h>

const unsigned char Segment_Data[] = 
{
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6f
};

int main(void)
{
	DDRC = 0xff;
	DDRA = 0xff;
	PORTC = 0x00;
	
	while (1)
	{
		for (int i = 0; i < 10; i++) 
		{
			PORTA = Segment_Data[i];
			_delay_ms(1000);
		}
	}
}
