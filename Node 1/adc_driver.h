#ifndef adc_driver_h_
#define adc_driver_h_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "USART.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "basic_defs.h"

#define BASE_ADDRESS_ADC 0x1400
#define NUMBER_OF_CHANNELS 4

void adc_config_clock();
void adc_init();
volatile uint8_t adc_read(uint8_t channel);

uint8_t ADC_test(uint8_t channel);
void ADC_clock(void);
void ADC_read(void);
uint8_t ADC_tester(uint8_t channel);


#endif