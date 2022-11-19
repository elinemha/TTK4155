/*
 * delay_due.c
 *
 * Created: 19.11.2022 11:01:52
 *  Author: emmal
 */ 

#include "delay_due.h"
#include <stdint.h>

volatile uint32_t ms_ticks = 0;

void systick_setup(uint32_t sys_freq) {
	SysTick->LOAD = (sys_freq / 1000000U) - 1U; 											//1ms tick
	SysTick->VAL = 0x00; 																	//explicitly set start value (undefined on reset)
	SysTick->CTRL |= (1U << SysTick_CTRL_TICKINT_Pos) | (1U << SysTick_CTRL_CLKSOURCE_Pos); //enable systick interrupt, source processor clock
	SCB->SHP[8] = 0U;																		//set SysTick interrupt priority (default: 0, the highest)
	SysTick->CTRL |= (1U << SysTick_CTRL_ENABLE_Pos); 										//enable SysTick
}

void SysTick_Handler(void)
{
	ms_ticks++;
}

uint32_t getMillis(void)
{
	return ms_ticks;
}

void us_delay(uint32_t delay)
{
	uint32_t prevMillis = getMillis() + delay;
	while (getMillis() != prevMillis);
}