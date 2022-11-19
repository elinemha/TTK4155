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
	USART_Init(MY_UBRR);
	fdevopen(&USART_Transmit,&USART_Receive);
	
	SRAM_INIT();
	can_init();
	adc_init();
	joystick_init();
	oled_init();
	
		
	printf("Starting...\n");
		
	can_message board_positions_c;
	volatile CONTROL_BOARD board_positions, board_positions2;
	volatile JOYSTICK_DIR dir_j;
	int oled_position = 0;
	uint8_t can_id = 0;
	
	while(1)
	{	
		board_positions = read_board_positions();
	//	board_positions = calibrate_positions(board_positions);
		board_positions_c.id = can_id;
		board_positions_c.length = 5;
		board_positions_c.data[0] = board_positions.x;
		board_positions_c.data[1] = board_positions.y;
		board_positions_c.data[2] = board_positions.left;
		board_positions_c.data[3] = board_positions.right;
		board_positions_c.data[4] = board_positions.button;
		printf("x:%d , y: %d, left: %d, right: %d, button: %d", board_positions_c.data[0], board_positions_c.data[1], board_positions_c.data[2], board_positions_c.data[3], board_positions_c.data[4]);
		can_send(&board_positions_c);
		//_delay_ms(200);
		can_id += 1;
		
		board_positions2 = calibrate_positions(board_positions);
		dir_j = input_joystick_dir(board_positions2);
		
		if(dir_j == UP)
		{
			if(oled_position > 0)
			{
				oled_position -= 1;
			}
		}
		else if(dir_j == DOWN)
		{
			if(oled_position < 7)
			{
				oled_position += 1;
			}
		}
		_delay_ms(100);
		
		
		oled_reset();
		
		oled_pos(0x00, 0x00);
		char mystring[] = "OPTIONS  ";
		writing_oled8(mystring);
		
		oled_pos(0x01, 0x00);
		char mystring1[] = "SETTINGS  ";
		writing_oled8(mystring1);
		
		oled_pos(0x02, 0x00);
		char mystring2[] = "SOUND   ";
		writing_oled8(mystring2);
		
		oled_pos(0x03, 0x00);
		char mystring3[] = "START   ";
		writing_oled8(mystring3);
		
		oled_pos(0x04, 0x00);
		char mystring4[] = "EXIT    ";
		writing_oled8(mystring4);
		
		oled_pos(oled_position, 0x00);
		char mystring5[] = "<<-----";
		writing_oled4(mystring5);
	}	
	
return 0;
}

