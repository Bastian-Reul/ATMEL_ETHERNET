/*
selbst erstellte Library
zur Ansteuerung eines Pins an einem ATMEGA328
Version 0.1		04.11.2018		Erstellung der Klasse
Version 1.0		05.11.2018		Fertigstellung der rudimentären Funktionen der Klasse Pin


Notes:
Der Atmega 328 hat keinen Port A, an Port C fehlt Pin 7 bei der DIP (Arduino UNO) Version des ICs!!!
*/
#include "Pin_ATMEGA328.h"
#include <stdint-gcc.h>
#include <avr/io.h>

Pin::Pin()
{
	//Standardkonstruktor
}

Pin::Pin(char PublicPort, uint8_t Public_Nummer_Pin, bool Eingang)
{
	//ctor
	setze_Port(PublicPort);
	setze_PinNummer(Public_Nummer_Pin);
	setze_Richtung(Eingang);
	initialisierePin();  
}

void Pin::merke_status(bool status)
{
	status_intern = status;
}

void Pin::toggle_Pin()
{
	if (lese_status())
	{
		setze_Status(false);
	} 
	else
	{
		setze_Status(true);
	}
}

bool Pin::lese_status()
{

		if (private_Port == 'B')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (PINB & (1<<PINB0))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 1:	if (PINB & (1<<PINB1))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 2:	if (PINB & (1<<PINB2))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 3:	if (PINB & (1<<PINB3))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
					
				case 4:	if (PINB & (1<<PINB4))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 5:	if (PINB & (1<<PINB5))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
				
				case 6:	if (PINB & (1<<PINB6))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;
					
				case 7:	if (PINB & (1<<PINB7))
					{merke_status(true);}
				else
					{merke_status(false);}
				break;		
													
				default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port B"
				break;
				
			}
		}

		if (private_Port == 'C')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (PINC & (1<<PINC0))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 1:	if (PINC & (1<<PINC1))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 2:	if (PINC & (1<<PINC2))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 3:	if (PINC & (1<<PINC3))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 4:	if (PINC & (1<<PINC4))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 5:	if (PINC & (1<<PINC5))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 6:	if (PINC & (1<<PINC6))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
			}
		}
		
		if (private_Port == 'D')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (PIND & (1<<PIND0))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 1:	if (PIND & (1<<PIND1))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 2:	if (PIND & (1<<PIND2))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 3:	if (PIND & (1<<PIND3))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 4:	if (PIND & (1<<PIND4))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 5:	if (PIND & (1<<PIND5))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 6:	if (PIND & (1<<PIND6))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;
				
				case 7:	if (PIND & (1<<PIND7))
				{merke_status(true);}
				else
				{merke_status(false);}
				break;			}
		}
	return status_intern;
}	
	


char Pin::lese_Port()
{
	return private_Port;
}

uint8_t Pin::lese_PinNummer()
{
	return private_Nummer_Pin;
}

void Pin::setze_Port(char PortBuchstabe)
{
	private_Port = PortBuchstabe;
}

void Pin::setze_PinNummer(uint8_t Pin_Nummer)
{
	private_Nummer_Pin = Pin_Nummer;
}

void Pin::setze_Richtung(bool is_Eingang)
{
	private_Eingang = is_Eingang;
}

void Pin::initialisierePin()
{
	if (private_Port == 'A')
	{
		
	}

	if (private_Port == 'B')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB0);}
			else
			{DDRB |= (1 << DDB0);}
			break;
			
			case 1:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB1);}
			else
			{DDRB |= (1 << DDB1);}
			break;
			
			case 2:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB2);}
			else
			{DDRB |= (1 << DDB2);}
			break;
			
			case 3:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB3);}
			else
			{DDRB |= (1 << DDB3);}
			break;
			
			case 4:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB4);}
			else
			{DDRB |= (1 << DDB4);}
			break;
			
			case 5:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB5);}
			else
			{DDRB |= (1 << DDB5);}
			break;
			
			case 6:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB6);}
			else
			{DDRB |= (1 << DDB6);}
			break;
			
			case 7:	if (private_Eingang == true)
			{DDRB &= ~(1 << DDB7);}
			else
			{DDRB |= (1 << DDB7);}
			break;
			
			default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port B"
			break;
			
		}
	}

	if (private_Port == 'C')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC0);}
			else
			{DDRC |= (1 << DDC0);}
			break;
			
			case 1:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC1);}
			else
			{DDRC |= (1 << DDC1);}
			break;
			
			case 2:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC2);}
			else
			{DDRC |= (1 << DDC2);}
			break;
			
			case 3:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC3);}
			else
			{DDRC |= (1 << DDC3);}
			break;
			
			case 4:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC4);}
			else
			{DDRC |= (1 << DDC4);}
			break;
			
			case 5:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC5);}
			else
			{DDRC |= (1 << DDC5);}
			break;
			
			case 6:	if (private_Eingang == true)
			{DDRC &= ~(1 << DDC6);}
			else
			{DDRC |= (1 << DDC6);}
			break;
			
			default: //# warning "The choosen pin number is not valid. Only 0-6 are allowed on Port C"
			break;
			
		}
	}
	
	if (private_Port == 'D')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD0);}
			else
			{DDRD |= (1 << DDD0);}
			break;
			
			case 1:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD1);}
			else
			{DDRD |= (1 << DDD1);}
			break;
			
			case 2:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD2);}
			else
			{DDRD |= (1 << DDD2);}
			break;
			
			case 3:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD3);}
			else
			{DDRD |= (1 << DDD3);}
			break;
			
			case 4:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD4);}
			else
			{DDRD |= (1 << DDD4);}
			break;
			
			case 5:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD5);}
			else
			{DDRD |= (1 << DDD5);}
			break;
			
			case 6:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD6);}
			else
			{DDRD |= (1 << DDD6);}
			break;
			
			case 7:	if (private_Eingang == true)
			{DDRD &= ~(1 << DDD7);}
			else
			{DDRD |= (1 << DDD7);}
			break;
			
			default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port D"
			break;						
		}
	}


}

void Pin::setze_Status(bool Status)
{

		if (private_Port == 'B')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{ PORTB |= (1<< PINB0);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB0);
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{ PORTB |= (1<< PINB1);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB1);
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{ PORTB |= (1<< PINB2);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB2);
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{ PORTB |= (1<< PINB3);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB3);
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{ PORTB |= (1<< PINB4);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB4);
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{ PORTB |= (1<< PINB5);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB5);
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{ PORTB |= (1<< PINB6);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB6);
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{ PORTB |= (1<< PINB7);
					merke_status(true);}
				else
				{PORTB &= ~(1<<PINB7);
					merke_status(false);}
				break;
				
				default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port B"
				break;
				
			}
		}

		if (private_Port == 'C')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{ PORTC |= (1<< PINC0);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC0);
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{ PORTC |= (1<< PINC1);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC1);
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{ PORTC |= (1<< PINC2);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC2);
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{ PORTC |= (1<< PINC3);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC3);
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{ PORTC |= (1<< PINC4);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC4);
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{ PORTC |= (1<< PINC5);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC5);
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{ PORTC |= (1<< PINC6);
					merke_status(true);}
				else
				{PORTC &= ~(1<<PINC6);
					merke_status(false);}
				break;
				
				default: //# warning "The choosen pin number is not valid. Only 0-6 are allowed on Port C"
				break;
							}
		}
		
		if (private_Port == 'D')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{ PORTD |= (1<< PIND0);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND0);
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{ PORTD |= (1<< PIND1);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND1);
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{ PORTD |= (1<< PIND2);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND2);
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{ PORTD |= (1<< PIND3);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND3);
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{ PORTD |= (1<< PIND4);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND4);
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{ PORTD |= (1<< PIND5);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND5);
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{ PORTD |= (1<< PIND6);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND6);
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{ PORTD |= (1<< PIND7);
					merke_status(true);}
				else
				{PORTD &= ~(1<<PIND7);
					merke_status(false);}
				break;
				
				default: //# warning "The choosen pin number is not valid. Only 0-7 are allowed on Port D"
				break;
			}
		}

}
/*
Pin::~Pin()
{
	//dtor
}
*/