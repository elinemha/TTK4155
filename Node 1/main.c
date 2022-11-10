/*
 * Byggern2.c
 *
 * Created: 01.09.2022 14:32:48
 * Author : emmal
 */ 

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "basic_defs.h"
#include "USART.h"
#include "oled.h"
#include "adc_driver.h"
#include "joystick.h"
#include "mcp2515.h"
#include "spi_driver.h"
#include "can.h"
#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{	
	volatile JOYSTICK_POS pos_j;
	volatile SLIDER_POS pos_s;
	volatile JOYSTICK_DIR dir_j;
	 
	USART_Init(MY_UBRR);
	fdevopen(&USART_Transmit,&USART_Receive);
	
	SRAM_INIT();
	can_init();
	adc_init();
	joystick_init();
	//oled_init();
	
	DDRB &= ~(1<<PB1);
	DDRB &= ~(1<<PB2);	

	DDRD &= ~(1<<PD4);
		
	printf("Starting...\n");
	uint8_t address_spi = 0x05;
	uint8_t data_spi;
	uint8_t status;
	ADC_read();
	/*
		
		can_message cm;
		cm.id = 77;
		cm.length = 2;
		cm.data[0] = 'a';
		cm.data[1] = 'b';
		*/
	
	can_message can_joy;
	JOYSTICK_POS joy_pos;
	uint8_t id = 0;
	while(1)
	{	
		joy_pos = read_joystick_pos();
		can_joy.id = id;
		can_joy.length = 2;
		can_joy.data[0] = joy_pos.x;
		can_joy.data[1] = joy_pos.y;
		printf("x:%d , y: %d", can_joy.data[0], can_joy.data[1]);
		canned(&can_joy);
		_delay_ms(200);
		id += 1;
	}	
	
return 0;
}

