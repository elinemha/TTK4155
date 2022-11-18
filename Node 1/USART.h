

#ifndef USART_H_
#define USART_H_

#define RX_BUFFER_SIZE 128
#define F_CPU 4915200
#define BAUD 9600

#define MY_UBRR ((F_CPU/16)/BAUD)-1

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void USART_Init(unsigned int baud );
int USART_Transmit(char data, FILE* JUSTNAME );
int USART_Receive(FILE* JUSTNAME );

#endif