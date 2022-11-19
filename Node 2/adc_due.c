/*
 * adc_due.c
 *
 * Created: 15.11.2022 15:03:58
 *  Author: emmalle
 */ 


#include "sam.h"
#include "adc_due.h"
#include <stdio.h>

#define IR_THRESHOLD	200

void adc_init(){
	REG_PMC_PCER1 |= PMC_PCER1_PID37;	//Initilaizing clock for ADC with ID 37
	REG_ADC_MR |= ADC_MR_FREERUN_ON;	//Free-run mode, doesn't wait for trigger
	REG_ADC_CHER |= ADC_CHER_CH0;		//Enabling channel 0
	REG_ADC_CR |= ADC_CR_START;		//Starts conversion
}

uint16_t read_IR(){				
	uint16_t beam = ADC->ADC_CDR[0];	//Reads ADC data
	return beam;				//Returns analog value
	}

int goal_scored(uint16_t beam){			//Goal counter
	if(beam < IR_THRESHOLD){		//If the beam goes below a threshold of 200, a goal is registered
		return 1;
	}
	else{
		return 0;
	}
}
