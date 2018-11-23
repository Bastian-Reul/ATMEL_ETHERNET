/*
 * SPI_ATMEGA328.h
 *
 * Created: 09.11.2018 11:46:17
 *  Author: Basti
 */ 


#ifndef SPI_ATMEGA328_H_
#define SPI_ATMEGA328_H_

#include "Pin_ATMEGA328.h"

void spi_init_master (void);
unsigned char spi_tranceiver (char data);
void spi_transmit_string(char *transmitString);


#endif /* SPI_ATMEGA328_H_ */