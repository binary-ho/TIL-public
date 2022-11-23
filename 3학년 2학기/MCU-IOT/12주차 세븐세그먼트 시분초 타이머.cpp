#define F_CPU 16000000

#define INIT_SEC 0
#define INIT_MIN 0
#define INIT_HOUR 0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char count_int = 0;
char count = 0, Seconds = INIT_SEC, Minutes = INIT_MIN, Hours = INIT_HOUR;

ISR(TIMER0_OVF_vect)
{
  count_int++;
  if (count_int == 244)
  {
    PORTG ^= 0x03;
    Seconds++;
    count_int = 0;
  }
}

int main(void)
{
  const unsigned char Segment_Data[] =
      {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F};

  unsigned int COLUMN[4] = {0, 0, 0, 0};

  DDRA = 0xff;
  DDRC = 0xff;

  DDRG = 0x03;

  TCCR0 = 0x06;
  TCNT0 = 0x00;
  TIMSK = 0x01;
  SREG |= 0x80;

  while (1)
  {
    COLUMN[0] = (Minutes % 100) / 10;
    COLUMN[1] = (Minutes % 10);
    COLUMN[2] = (Seconds % 100) / 10;
    COLUMN[3] = (Seconds % 10);

    for (int i = 0; i < 4; i++)
    {
      PORTC = ~(0x01 << i);
      PORTA = Segment_Data[COLUMN[i]];
      _delay_ms(2);
    }
    if (Seconds >= 60)
    {
      Seconds = 0;
      Minutes++;
    }
    if (Minutes >= 60)
    {
      Minutes = 0;
      Hours++;
    }
    if (Hours >= 24)
    {
      Hours = 0;
    }
  }
}
