/*
 * controller.c
 *
 * Created: 16.11.2022 13:19:44
 *  Author: emmalle
 */ 

#include "controller.h"
#include <stdint.h>

//PID parameters
float Time_sample = 0.0001;
float kp;
float ki;
float kd;

float reference;
float integral;
float prev_error;
float derivative;
float sum_error;

int16_t maxOutput = 15000; 

//storing initial values for PID controller
void controller_init()
{
	kp = 6;
	ki = 8;
	kd = 0.8;

	reference   = 0;
	integral    = 0;
	prev_error  = 0;
	//sum_error = 0;
}

// PID controller for motor position
int16_t position_controller(int16_t enc_pos, uint8_t slider_pos)
{
	reference = slider_pos;
	int16_t error = reference - abs(enc_pos);		// error = (slider position) - (encoder position), e = r - y
	sum_error += error;
	integral = sum_error * Time_sample;
	derivative = (error-prev_error)/Time_sample;
	
	printf("Error: %d \n", error);
	
	if (error<1)
	{
		integral = 0;
	}
	
	int32_t u_p = kp*error;
	int32_t u_i = ki*integral;
	int32_t u_d = kd*derivative;
	//u_t output from PI sum operation
	int16_t u_t = u_p + u_i + u_d;					// u[n] = Kp*e[n]+T*Ki*sum_error+Kd*(error-error_prev)/T
	
	// avoiding integral windup
	if((abs(sum_error) > maxOutput) && sum_error >= 0){
		sum_error = maxOutput;
	}
	else if ((abs(sum_error) > maxOutput) && sum_error <= 0){
		sum_error = -maxOutput;
	}
	
	// avoiding gain windup
	if ((abs(u_t) > maxOutput) && u_t >= 0){
		u_t = maxOutput;
	}
	else if ((abs(u_t) > maxOutput) && u_t <= 0){
		u_t = -maxOutput;
	}
	//stores error for next run
	prev_error = error;         
		
	return abs(u_t);
}
