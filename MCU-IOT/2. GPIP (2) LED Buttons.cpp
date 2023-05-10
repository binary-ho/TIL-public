#define F_CPU 16000000
#include <avr/io.h>


int main(void)
{
	unsigned char keyin = 0;
	DDRG = 0x03;
	
    while (1) 
    {
		keyin = (PING&0x0C) >> 2;
		switch(keyin) 
		{
			case 0:	PORTG = 0x00;
					break;
			case 1: PORTG = 0x01;
					break;
			case 2: PORTG = 0x02;
					break;
			case 3: PORTG = 0x03;
					break;
		}
	}
}

