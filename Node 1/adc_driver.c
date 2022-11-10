#include "adc_driver.h"



void adc_config_clock() {
	// set PB0 to output PWM timer signal
	DDRB |= 1;

	// set to CTC mode
	TCCR0 |= (1 << WGM01);
	TCCR0 &= ~(1 << WGM00);
	
	// set PWM toggle on match with internal clock
	TCCR0 &= ~(1 << COM01);
	TCCR0 |= (1 << COM00);

	// set PWM signal to match with internal clock, no prescale
	TCCR0 &= ~(1 << CS02);
	TCCR0 &= ~(1 << CS01);
	TCCR0 |= (1 << CS00);

	// frequency set to 0.5 x F_CPU
	OCR0 = 0;
}

void adc_init() {
	adc_config_clock();
}

volatile uint8_t adc_read(uint8_t channel){
	// initiate conversion by setting writing to the ADC address space
	volatile char* ext_mem = (char *) BASE_ADDRESS_ADC;
	ext_mem[0] = 0;

	// wait for end of conversion
	_delay_ms(9*NUMBER_OF_CHANNELS*2 / F_CPU);

	// read desired channel
	uint8_t data;

	for (int i = 0; i <= channel; ++i) {
		data = ext_mem[0];
	}
	
	return data;
}


uint8_t ADC_test(uint8_t channel)
{
	volatile char *ext_adc = (char *) 0x1400; // Start address for the SRAM
	uint16_t ext_ram_size = 0x400;
	//uint16_t write_errors = 0;
	printf("Starting ADC test...\n");
	uint8_t offset_adc = 0x01;
	uint8_t value = 0;
	uint8_t adc_mode = (1<<7)|(channel);
	ext_adc[offset_adc] = adc_mode;
	_delay_us(5000);
	value = ext_adc[offset_adc];
	if (value > 255)
		value = 255;
	else if (value <= 0)
		value = 1;
	printf("Retrieval Value2: %02X \n", value);
	return value;
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	/*uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
		uint8_t some_value = rand();
		uint8_t value = 129;
		ext_ram = value;
		_delay_us(30);
		volatile uint8_t retreived_value;
		//for (uint16_t i = 0; i < 4; i++) {
			retreived_value = ext_ram[0];
			printf("Retrieval Value: %02X \n", retreived_value);
			
			retreived_value = ext_ram[1];
			printf("Retrieval Value: %02X \n", retreived_value);
		//}
	printf("Retrieval Value2: %02X \n", retreived_value);
		//_delay_ms(200);*/

	// Retrieval phase: Check that no values were changed during or after the write phase
	
	//printf("ADC test completed with \n%4d errors in write phase \n", write_errors);
}

void ADC_clock(void)
{
	TCCR0 |= (1<<WGM01)|(1<<COM00)|(1<<CS00);
	DDRD |= (1<<DDD5);
	OCR0 = 0x04;
}

uint8_t ADC_read()
{
	volatile char *ext_ram = (char *) 0x1400; // Start address for the SRAM
	return ext_ram[0];
	//uint16_t ext_ram_size = 0x400;
	//for (uint16_t i = 0; i < ext_ram_size; i++) {
	//	uint8_t retreived_value = ext_ram[i]; }
}

uint8_t ADC_tester(uint8_t channel)
{
	volatile char *ext_adc = (char *) 0x1400; // Start address for the SRAM
	uint16_t ext_ram_size = 0x400;
	//uint16_t write_errors = 0;
	printf("Starting ADC test...\n");
	uint8_t offset_adc = 0x01;
	uint8_t value = 0;
	uint8_t adc_mode = (1<<7)|(channel);
	ext_adc[offset_adc] = adc_mode;
	_delay_us(5000);
	value = ext_adc[offset_adc];
	if (value > 255)
		value = 255;
	else if (value <= 0)
		value = 1;
	printf("Retrieval Value2: %02X \n", value);
	return value;
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	/*uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
		uint8_t some_value = rand();
		uint8_t value = 129;
		ext_ram = value;
		_delay_us(30);
		volatile uint8_t retreived_value;
		//for (uint16_t i = 0; i < 4; i++) {
			retreived_value = ext_ram[0];
			printf("Retrieval Value: %02X \n", retreived_value);
			
			retreived_value = ext_ram[1];
			printf("Retrieval Value: %02X \n", retreived_value);
		//}
	printf("Retrieval Value2: %02X \n", retreived_value);
		//_delay_ms(200);*/

	// Retrieval phase: Check that no values were changed during or after the write phase
	
	//printf("ADC test completed with \n%4d errors in write phase \n", write_errors);
}

