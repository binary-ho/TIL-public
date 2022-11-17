#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void uart0_init(void);
int Putchar(char message);
int Print(char *str, char length);

int main(void)
{
	char *str = "\r\nUART_Test:";
	char length = strlen(str);
	
	uart0_init();
	Print(str, length);
	
	while (1) {
		Putchar('.');
	}
}

void uart0_init() 
{
	UCSR0B = 0x00;	// disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x06;
	UBRR0L = 0x67;	// set baud rate lo
	UBRR0H = 0x00;	// set baud rate hi
	UCSR0B = 0x18;
}

int Putchar(char message)
{
	while (((UCSR0A >> UDRE0)&0x01) == 0);
	// UDRE, data register empty
	UDR0 = message;
	return 0;
}

int Print(char *str, char length)
{
	for (int i = 0; i < length; i++)
	{
		Putchar(*str++);
	}
	return 0;
}
