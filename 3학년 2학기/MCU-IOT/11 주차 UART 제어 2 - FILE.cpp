#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>

void uart0_init(void);
int Putchar(char message, FILE *str);
int Print(char *str, char length);

int main(void)
{
	uart0_init();
	fdevopen(Putchar, 0);
	printf("\n\rUART_Test");
	
	while (1) 
	{
		for (int i = 0; i < 100; i++)
		{
			printf("UART TEST: %d\r\n", i);
		}
	}
}

void uart0_init(void) 
{
	UCSR0B = 0x00;	// disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x06;
	UBRR0L = 0x67;	// set baud rate lo
	UBRR0H = 0x00;	// set baud rate hi
	UCSR0B = 0x18;
}

int Putchar(char message, FILE *str)
{
	while (((UCSR0A >> UDRE0)&0x01) == 0);
	// UDRE, data register empty
	UDR0 = message;
	return 0;
}
