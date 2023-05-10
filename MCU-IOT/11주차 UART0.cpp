#define F_CPU 16000000
#include <avr/io.h>

void uart0_init(void);
int Putchar(char message);
int main(void)
{
	uart0_init();
	
	while(1) {
		Putchar('.');
	}
}

// UART0 Initialize
// desired baud rate:9600
// actual: baud rate:9615 (0.2%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
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
	while (((UCSR1A >> UDRE1)&0x01) == 0);
	// UDRE, data register empty
	UDR1 = message;
	return 0;	
}
