/*
 * controller.h
 *
 * Created: 16.11.2022 13:20:17
 *  Author: emmalle
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "sam.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	LEFT,
	RIGHT
} MOTOR_DIRECTION;

// For delay
void systick_setup(uint32_t sys_freq);
void SysTick_Handler(void);
uint32_t getMillis(void);
void ms_delay(uint32_t delay);

void dac_init();
void motor_init();
void set_direction(MOTOR_DIRECTION dir);
int16_t read_encoder();
void set_speed(int16_t speed_joystick);
void reset_encoder();
void controller_init();
int16_t position_controller(int16_t enc_data, uint8_t slider_pos);

#endif /* CONTROLLER_H_ */