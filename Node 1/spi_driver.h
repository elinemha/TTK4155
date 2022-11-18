#ifndef spi_driver_h_
#define spi_driver_h_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "USART.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "basic_defs.h"
//#include "SSD1308.h"

void SPI_Init(void);
void SPI_write(char cData);
uint8_t SPI_read(void);
void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);

#endif