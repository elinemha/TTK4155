/*
 * adc_due.h
 *
 * Created: 15.11.2022 15:02:26
 *  Author: emmalle
 */ 


#ifndef adc_due_H_
#define adc_due_H_

#include <stdint.h>
#include <stdio.h>

uint16_t read_IR();
void adc_init();
int goal_scored(uint16_t beam);

#endif /* adc_due_h_ */