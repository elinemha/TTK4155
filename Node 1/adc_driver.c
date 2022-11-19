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
	
	DDRD &= ~(1<<PD4);

}

volatile uint8_t adc_read(uint8_t channel){
	// initiate conversion by setting writing to the ADC address space
	volatile char* ext_mem = (char *) BASE_ADDRESS_ADC;
	ext_mem[0] = 0;

	// wait for end of conversion
	_delay_ms(9*NUMBER_OF_CHANNELS*2 / F_CPU);

	uint8_t data;

	// read desired channel
	for (int i = 0; i <= channel; ++i) {
		data = ext_mem[0];
	}
	
	return data;
}


uint8_t ADC_test(uint8_t channel)
{
	volatile char *ext_adc = (char *) 0x1400; // Start address for the SRAM
	uint16_t ext_ram_size = 0x400; // SRAM size
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
}

void ADC_clock(void)
{
	TCCR0 |= (1<<WGM01)|(1<<COM00)|(1<<CS00); // Write to the Timer/Counter Control Register such that it's mode of operation is CTC
	DDRD |= (1<<DDD5); // Set DDD5 as output pin
	OCR0 = 0x04; // Assign Output Compare Register
}


