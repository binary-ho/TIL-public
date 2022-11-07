#define F_CPU 16000000
#include <avr/io.h>

void uart1_init(void);
int Putchar1(char message);
int main(void)
{
	uart1_init();
	
	while(1) {
		Putchar1('.');
	}
}

// UART0 Initialize
// desired baud rate:9600
// actual: baud rate:9615 (0.2%)
// char size: 8 bit
// parity: Disabled
void uart1_init(void)
{
	UCSR1B = 0x00;	// disable while setting baud rate
	UCSR1A = 0x00;
	UCSR1C = 0x06;
	UBRR1L = 0x67;	// set baud rate lo
	UBRR1H = 0x00;	// set baud rate hi
	UCSR1B = 0x18;
}

int Putchar1(char message)
{
	while (((UCSR0A >> UDRE0)&0x01) == 0);
	// UDRE, data register empty
	UDR0 = message;
	return 0;	
}
