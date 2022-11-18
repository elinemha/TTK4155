/*
 * adc_due.c
 *
 * Created: 15.11.2022 15:03:58
 *  Author: emmalle
 */ 


#include "sam.h"
#include "adc_due.h"
#include <stdio.h>

#define IR_THRESHOLD	100

void adc_init(){
	REG_PMC_PCER1 |= PMC_PCER1_PID37;
	REG_ADC_MR |= ADC_MR_FREERUN_ON;
	REG_ADC_CHER |= ADC_CHER_CH0;
	REG_ADC_CR |= ADC_CR_START;
}

uint16_t read_IR(){
	uint16_t beam = ADC->ADC_CDR[0];
	return beam;
	}

int goal_scored(uint16_t beam){
	if(beam < IR_THRESHOLD){
		return 1;
	}
	else{
		return 0;
	}
}