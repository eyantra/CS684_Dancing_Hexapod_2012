#include "communication.h"

SIGNAL(SIG_USART3_RECV) // ISR for receive complete interrupt
{
	unsigned char data = UDR3; //making copy of data from UDR1 in 'data' variable

	// output[count] = data;
	// output[count + 1] = '\0';
	// count = count + 1;
	// if (count == LENGTH - 1)
	// {
		// count = 0;
		// output[count] = '\0';
	// }
}

void uart3_init(void)
{
	UCSR3B = 0x00; //disable while setting baud rate
	UCSR3A = 0x00;
	UCSR3C = 0x07;
	UBRR3L = 0x47; //set baud rate lo
	UBRR3H = 0x00; //set baud rate hi
	UCSR3B = 0x98;
}