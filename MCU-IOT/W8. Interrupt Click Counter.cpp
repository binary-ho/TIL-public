#define F_CPU 16000000
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void ShowDigit(int i, int digit);
void Show4Digit(int number);

const unsigned char Segment_Data[] =
{ 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6f };
char COLUMN[4] = {0, 0, 0, 0};
int SHOW_NUMBER = 1000;

ISR(INT0_vect)
{
	if (SHOW_NUMBER >= 0) SHOW_NUMBER--;
}

ISR(INT1_vect)
{	
	if (SHOW_NUMBER < 9999) SHOW_NUMBER++;
}

int main(void)
{
	DDRC = 0xff;
	DDRA = 0xff;
	EICRA = 0x0F;
	EIMSK = 0x03;
	SREG |= 0x80;
	
	PORTC = 0x00;
	
	while(1)
	{
		Show4Digit(SHOW_NUMBER);
	}
}

void Show4Digit(int number)
{
	COLUMN[0] = number/1000;
	COLUMN[1] = (number%1000)/100;
	COLUMN[2] = (number%100)/10;
	COLUMN[3] = (number%10);
	for(int i = 0; i < 4; i++) {
		ShowDigit(COLUMN[i], i);
		_delay_ms(2);
	}
}

void ShowDigit(int i, int digit)
{
	PORTC = ~(0x01<<digit);
	PORTA = Segment_Data[i];
}
