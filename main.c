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
#include "adc_driver.h"
#include "joystick.h"
#include <util/delay.h>
#include <avr/interrupt.h>



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
	
	adc_init();
	
	printf("Starting...\n");

	while(1)
	{
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
		*/
		
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
	}

return 0;
}

void SRAM_INIT(void)
{
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
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