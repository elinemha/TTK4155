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
#include <stdlib.h>
//#include "systic_lib.h"

typedef enum {
	LEFT,
	RIGHT
} MOTOR_DIRECTION;

void systick_setup(uint32_t sys_freq);
void SysTick_Handler(void);
uint32_t getMillis(void);
void ms_delay(uint16_t delay);

void dac_init();
void motor_init();
void set_direction(MOTOR_DIRECTION dir);
int16_t read_encoder();
void set_speed(int16_t speed_joystick);
void reset_encoder();
void controller_init();
int16_t position_controller(int16_t enc_data, uint8_t slider_pos);
//void remote_kp(float new_kp);
float pid_generate(float r, float y, float dt);
int16_t MOTOR_PIDcontroller_Pos(uint8_t pos);
void motorSpeedPos(uint16_t pos);

#endif /* CONTROLLER_H_ */