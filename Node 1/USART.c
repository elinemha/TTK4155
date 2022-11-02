
#include "USART.h"

volatile static uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};
volatile static uint16_t rx_count = 0;


void USART_Init(unsigned int baud )
{
	/*
	Set baud rate
	*/
	UBRR0H = (unsigned char)((baud & 0x0F00)>>8);
	UBRR0L = (unsigned char)(baud & 0x00FF);
	/*
	Enable receiver and transmitter
	*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
	/*
	Set frame format: 8data, 1stop bit
	*/
	UCSR0C = (1<<URSEL0) | (1<<UCSZ01) | (1<<UCSZ00) ;
}

int USART_Transmit(char data, FILE* JUSTNAME )
{
	/*
	Wait for empty transmit buffer
	*/
	while( !( UCSR0A & (1<<UDRE0)) )
	;
	/*
	Put data into buffer, sends the data
	*/
	UDR0 = data;
	return 0;
}

int USART_Receive(FILE* JUSTNAME )
{
	/*
	Wait for data to be received
	*/
	while( !(UCSR0A & (1<<RXC0)) )
	;
	/*
	Get and return received data from buffer
	*/
	return UDR0;
}

/*
ISR(USART_RX_vect){
	
	volatile static uint16_t rx_write_pos = 0;
	
	rx_buffer[rx_write_pos] = UDR0;
	rx_count++;
	rx_write_pos++;
	if(rx_write_pos >= RX_BUFFER_SIZE){
		rx_write_pos = 0;
	}
	
}
*/