#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void uart0_init(void);
int Putchar(char message, FILE *str);

int main(void)
{
  uart0_init();
  fdevopen(Putchar, 0);
  _delay_ms(5000);
  printf("Hongik University/ B715152/ Lee Jinho");
}

void uart0_init(void)
{
  UCSR0B = 0x00; // disable while setting baud rate
  UCSR0A = 0x00;
  UCSR0C = 0x06;
  UBRR0L = 0x67; // set baud rate lo
  UBRR0H = 0x00; // set baud rate hi
  UCSR0B = 0x18;
}

int Putchar(char message, FILE *str)
{
  while (((UCSR0A >> UDRE0) & 0x01) == 0)
    ;
  UDR0 = message;
  return 0;
}
