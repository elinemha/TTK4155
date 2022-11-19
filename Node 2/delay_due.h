/*
 * delay_due.h
 *
 * Created: 19.11.2022 11:03:08
 *  Author: emmal
 */ 


#ifndef DELAY_DUE1_H_
#define DELAY_DUE1_H_

#include "sam.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void systick_setup(uint32_t sys_freq);
void SysTick_Handler(void);
uint32_t getMillis(void);
void us_delay(uint32_t delay);

#endif /* DELAY_DUE_H_ */