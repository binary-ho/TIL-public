#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define C1 523
#define C1_ 554
#define D1 587
#define D1_ 622
#define E1 659
#define F1 699
#define F1_ 740
#define G1 784
#define G1_ 831
#define A1 880
#define A1_ 932
#define B1 988
#define C2 C1 * 2
#define C2_ C1_ * 2
#define D2 D1 * 2
#define D2_ D1_ * 2
#define E2 E1 * 2
#define F2 F1 * 2
#define F2_ F1_ * 2
#define G2 G1 * 2
#define G2_ G1_ * 2
#define A2 A1 * 2
#define A2_ A1_ * 2
#define B2 B1 * 2
#define DLY_0 32
#define DLY_1 16
#define DLY_2 8
#define DLY_4 4
#define DLY_8 2
#define DLY_16 1

volatile int school[100] = {G1, G1, A1, A1, G1, G1, E1, G1, G1, E1, E1, D1, G1, G1, A1, A1, G1, G1, E1, G1, E1, D1, E1, C1};
volatile int school_length[100] = {DLY_4, DLY_4, DLY_4, DLY_4, DLY_4, DLY_4, DLY_1, DLY_4, DLY_4, DLY_4, DLY_4, DLY_0, DLY_4, DLY_4, DLY_4, DLY_4, DLY_4, DLY_4, DLY_1, DLY_4, DLY_4, DLY_4, DLY_4, DLY_0};
volatile int SanToKi[100] = {G1, E1, E1, G1, E1, C1, D1, E1, D1, C1, E1, G1, C2, G1, C2, G1, E1, G1, D1, F1, E1, D1, C1};
volatile int SanToKi_length[100] = {DLY_1, DLY_4, DLY_4, DLY_4, DLY_4, DLY_1, DLY_1, DLY_4, DLY_4, DLY_4, DLY_4, DLY_1, DLY_2, DLY_4, DLY_2, DLY_4, DLY_4, DLY_4, DLY_1, DLY_1, DLY_4, DLY_4, DLY_4, DLY_4, DLY_1};

volatile unsigned char TIMERvalue = 0xFF;
volatile int freq = 1000, i;

void Shimpyo(int time);
void Cutoff_Play(void);

ISR(TIMER0_OVF_vect)
{
  TCNT0 = TIMERvalue;
  PORTC ^= 0x80;
}

int main(void)
{
  DDRC = 0x80;
  TCCR0 = 0x04;
  TCNT0 = 0x05;
  TIMSK = 0x01;
  SREG |= 0x80;

  while (1)
  {
    schoolsong();
    _delay_ms(1000);
    SanToKisong();
    _delay_ms(1000);
  }
}

void schoolsong()
{
  for (int = 0; i < 24; i++)
  {
    freq = school[i];
    TIMERvalue = 255 - (1000000 / (8 * freq));
    Shimpyo(school_length[i]);
    Cutoff_Play();
  }
}

void SanToKisong()
{
  for (int = 0; i < 24; i++)
  {
    freq = SanToKi[i];
    TIMERvalue = 255 - (1000000 / (8 * freq));
    Shimpyo(SanToKi_length[i]);
    Cutoff_Play();
  }
}

void Shimpyo(int time)
{

  for (int i = 0; i < time; i++)
  {
    _delay_ms(50);
  }
}

void Cutoff_Play(void)
{
  _delay_ms(300);
  TIMERvalue = 255;
  _delay_ms(20);
}
