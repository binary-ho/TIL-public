#define F_CPU 16000000
#define STOP 0
#define START 1
#define INIT 2

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void ShowDigit(int i, int digit);
void Show4Digit();
int Run(void);

const unsigned char Segment_Data[] =
{ 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6f };
char COLUMN[4] = {0, 0, 0, 0};
int SHOW_NUMBER = 0;
int SHOW_NUMBER12 = 0;
int SHOW_NUMBER34 = 0;
int state = STOP;

ISR(INT0_vect)
{
	if (state == STOP) state = START;
	else state = STOP;
}

ISR(INT1_vect)
{
	state = INIT;
}

ISR(INT2_vect)
{
	if (SHOW_NUMBER12 < 50) SHOW_NUMBER12 += 10;
	else SHOW_NUMBER12 -= 50;
}

int main(void)
{
	DDRC = 0xff;
	DDRA = 0xff;
	DDRG = 0x03;	// LED용
	EICRA = 0x3F;	// 인터럽트 버튼 0 ~ 2를 상승 에지에서 사용하기 위해 64 - 1을 넣어준 것.
	EIMSK = 0x07;
	SREG |= 0x80;
	
	PORTC = 0x00;
	state = STOP;
	
	while(1)
	{
		Show4Digit();
	}
}

int Run(void)
{
	switch (state)
	{
		case STOP:	break;
		case START: SHOW_NUMBER34++;
		if (SHOW_NUMBER34 > 99)
		{
			SHOW_NUMBER12++;
			if(SHOW_NUMBER12 >= 60) SHOW_NUMBER12 = 0;
			SHOW_NUMBER34 = 0;
		}
		break;
		case INIT: SHOW_NUMBER12 = SHOW_NUMBER34 = 0; state = STOP;
	}
	if (20 <= SHOW_NUMBER12 && SHOW_NUMBER12 <= 25) PORTG = 0x03;
	else if (50 <= SHOW_NUMBER12) PORTG = 0x00;
	return SHOW_NUMBER = SHOW_NUMBER12*100 + SHOW_NUMBER34;
}

void Show4Digit()
{
	int number = Run();
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
	if (digit == 1) PORTA = Segment_Data[i]|0x80;
	else PORTA = Segment_Data[i];
}
