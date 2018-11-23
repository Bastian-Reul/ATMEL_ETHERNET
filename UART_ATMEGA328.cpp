/*
 * UART_ATMEGA328.cpp
 *
 * Created: 09.11.2018 11:30:39
 *  Author: Basti
 */ 

#define max_transmit_lenght	100

#include <avr/io.h>

// function to initialize UART
void uart_init (unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	/* Set frame format: 8data, 2stop bit 
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);*/
	
	/* Set frame format: 8data, 1stop bit 12.11.2018*/
	UCSR0C = (3<<UCSZ00);
}

// function to send data
void uart_transmit (char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;                                  // load data in the register
}

// function to receive data
unsigned char uart_recieve (void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;                                 // return 8-bit data
}

void uart_transmit_string(char *transmitString)
{
	volatile bool EndOfString = false;
	int i = 0;
	while ((i<max_transmit_lenght) && !(EndOfString))
	{
		if (transmitString[i] != '\n')
		{
			uart_transmit(transmitString[i]);
			i++;
		}
		else
		{
			EndOfString = true;
			uart_transmit('\n');
		}
	}
}

