/*
 * SPI_ATMEGA328.cpp
 *
 * Created: 09.11.2018 11:46:53
 *  Author: Basti
 */ 

#define max_transmit_lenght	100

#include <avr/io.h>
#include <avr/interrupt.h>

// Initialize SPI Master Device (with SPI interrupt)
void spi_init_master (void)
{
	// Set MOSI, SCK and CS (SS) as Output Defining CS (SS) as an Output is NOT Optional when Chip should run in Master mode!!!!!
	DDRB=(1<<5)|(1<<3)|(1<<2);
	
	// Enable SPI, Set as Master
	// Changed to Fosc/2 12.11.2018
	// Prescaler: Fosc/2, Enable Interrupts
	//The MOSI, SCK pins are as per ATMega8
	SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
	// Enable Global Interrupts
	sei();
}


//Function to send and receive data for both master and slave
unsigned char spi_tranceiver (char data)
{
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}

void spi_transmit_string(char *transmitString)
{
	volatile bool EndOfString = false;
	int i = 0;
	while ((i<max_transmit_lenght) && !(EndOfString))
	{
		if (transmitString[i] != '\n')
		{
			spi_tranceiver(transmitString[i]);
			i++;
		} 
		else
		{
			EndOfString = true;
			spi_tranceiver('\n');
		}
	}
}