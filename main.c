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
//#include "fonts.h"
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <iostream>
//using namespace std;



void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
		//	printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

void SRAM_INIT(void)
{
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}




int main()
{
	volatile JOYSTICK_POS pos_j;
	volatile SLIDER_POS pos_s;
	volatile JOYSTICK_DIR dir_j;
	 
	USART_Init(MY_UBRR);
	fdevopen(&USART_Transmit,&USART_Receive);
	
	SRAM_INIT();
	
	
	DDRB &= ~(1<<PB1);
	DDRB &= ~(1<<PB2);	
	
	DDRD &= ~(1<<PD4);
	
	adc_init();
	//oled_init();
	//oled_reset();
	//_delay_ms(1000);
	//display_on();
	//_delay_ms(1000);
	//oled_reset();
	
	mcp_init();
	SPI_Init();
		
	printf("Starting...\n");
	
	uint8_t address_spi = 0x05;
	uint8_t data_spi;
	
	
	
	//uint8_t oled_data = 0xFF;
	//uint8_t pos = 0x04;
	/*
	for (uint8_t i=0; i<10; i++)
	{
		mcp_write_tx0_buffer(i);
	}
	
	for (uint8_t i=0; i<10; i++)
	{
		data_spi = mcp_read_rx0_buffer();	
		printf("Trial and error: %02X \n", data_spi);
	}
	*/
	PORTB &= ~(1 << CAN_CS );
	
	while(1)
	{	
		
		//mcp2515_write(MCP_CNF1, 0x04 );
		//data_spi = mcp2515_read(MCP_CNF1);
		//printf("Trial and error  %02X \n", data_spi);	
		SPI_write(0xAA);
		data_spi = SPI_read();	
		//printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0xA0);
		data_spi = SPI_read();
		//printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0xA2);
		data_spi = SPI_read();
		//printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0xA4);
		data_spi = SPI_read();
		//printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);

/*
		mcp_write_tx0_buffer(0x0F);
		data_spi = mcp_read_rx0_buffer();
		
		printf("Trial and error: %02X \n", data_spi);
		_delay_ms(100);
		*/
			//writing_oled(mystring);

		//////////////////////////////////
		///////// JOYSTICK ///////////////
		//////////////////////////////////
		
		/*
		volatile uint8_t a = adc_read(0);
		volatile uint8_t b = adc_read(1);
		volatile uint8_t c = adc_read(2);
		volatile uint8_t d = adc_read(3);
		
		// printf("hey", ADC_test(1));
		printf("Pos X: %02X \n", a);
		printf("Pos Y: %02X \n", b);
		printf("Left Slider Value: %02X \n", c);
		printf("Right Slider Value: %02X \n", d);
		_delay_ms(1000);
		//SRAM_test();
		
		
		pos_s = read_slider_pos();
		pos_s = calibrate_slider_pos(pos_s);
		print_slider_pos(pos_s);

		pos_j = read_joystick_pos();
		pos_j = joystick_analog_pos(pos_j);
		print_joystick_pos(pos_j);

		dir_j = input_joystick_dir(pos_j);
		print_joystick_dir(dir_j);
		
		right_button_press();
		left_button_press();
		
		_delay_ms(1000);
		*/
		
		
		/////////////////////////////////
		////////////// OLED /////////////
		/////////////////////////////////
		/*
		pos_j = read_joystick_pos();
		pos_j = joystick_analog_pos(pos_j);
		dir_j = input_joystick_dir(pos_j);
		
		if(dir_j == UP)
		{
			if(position > 0)
			{
				position = position - 1;
			}
		}
		else if(dir_j == DOWN)
		{
			if(position < 7)
			{
				position = position + 1;
			}
		}
		_delay_ms(300);
		
		
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
		
		oled_pos(position, 0x00);
		char mystring5[] = "<<-----";
		writing_oled4(mystring5);
		
		//printf("Menu Position: %4d\n ", position);
		
		//display_on();
		//oled_reset();
		//int joy = 0;
		int joy = joystick_button_press();
		if (joy==0)
		{
			printf("Button is pressed!  %4d\n", joy);
			printf("Menu Position: %4d\n ", position);
		}
		*/
		
/*
		for (uint8_t page = 0; page <= 7; page++) {
			oled_pos(page,0);
			for (uint8_t col = 0; col <= 127; col++) {
				//oled_pos(page, col);
				oled_write_data(oled_data);
				//oled_data += 1;
				_delay_ms(100);
			}
			//_delay_ms(5000);
		}*/

	//writing('P');
	//writing('M');
	}	
	
return 0;
}


/*


//	unsigned char data;
//sei();
//ADC_clock();	//USART_Transmit('A');
//DDRA = 0xFF;
//PORTA = 0x00;

//printf("hello");
//printf(stdin);

//for (int i = 0; i < 1; ++i)
//printf("Starting Clock\n");
//ADC_clock();
//printf("Ending Clock\n");
*/