/*
 * UART_ATMEGA328.h
 *
 * Created: 09.11.2018 11:30:53
 *  Author: Basti
 */ 


/************************************************************************/
/* Please make sure you defined the necessary Macros in main.cpp

#ifndef F_CPU
#define F_CPU 16000000UL				// CPU Takt
#endif

// UART Defines
#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR
#define MYUBRR F_CPU/16/BAUD-1



using the UART could look like this:
int main(void)
{
	uart_init(MYUBRR);
	
	while (1)
	{
		uart_transmit('t');
		_delay_ms(100);
		uart_transmit('e');
		_delay_ms(100);
		uart_transmit('s');
		_delay_ms(100);
		uart_transmit('t');
		_delay_ms(100);
		uart_transmit(' ');
		_delay_ms(100);
	}
}

                                          */
/************************************************************************/

#ifndef UART_ATMEGA328_H_
#define UART_ATMEGA328_H_



void uart_init (unsigned int ubrr);
void uart_transmit (char data);
unsigned char uart_recieve (void);
void uart_transmit_string(char *transmitString);



#endif /* UART_ATMEGA328_H_ */