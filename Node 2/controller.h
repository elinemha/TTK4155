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
//#include <util/delay.h>
#include <stdio.h>

typedef enum {
	LEFT,
	RIGHT
} MOTOR_DIRECTION;

void dac_init();
void motor_init();
void set_direction(MOTOR_DIRECTION dir);
int16_t read_encoder();
void set_speed(uint8_t speed_joystick);
void controller_init(float _kp, float _ki);
//void position_controller(float r, float y, float dt, uint8_t position);
void remote_kp(uint8_t new_kp);


#endif /* CONTROLLER_H_ */