#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRG = 0x03;
	PORTG = 0x00;
	unsigned char keyin = 0;

	while (1)
	{
		keyin = (PING&0x0C)>>2;
		if (keyin != 0) {
      PORTG++;
      if (PORTG > 0x03) PORTG = 0x01;
      _delay_ms(500);
    }
	}
}
