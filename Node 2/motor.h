/*
 * motor.h
 *
 * Created: 19.11.2022 11:07:11
 *  Author: emmal
 */ 


#include "sam.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum {
	LEFT,
	RIGHT
} MOTOR_DIRECTION;

void dac_init();
void motor_init();
void set_direction(MOTOR_DIRECTION dir);
int16_t read_encoder();
void set_speed(int16_t speed_joystick);
void reset_encoder();


#endif /* MOTOR_H_ */