/*
 * Node_2.c lab7_test
 *
 * Created: 10.11.2022 14:24:54
 * Author : rohank
 */ 


#include "sam.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "pwm.h"
#include "adc_due.h"
#include "controller.h"
#include "sam3x8e.h"
#include "solenoid.h"
#include "motor.h"
#include "delay_due.h"

#define CAN_BR_1 0x00290165

#define NOT_RST PIO_PD1

int map(int x, int in_min, int in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(void)
{
    /* Initialize the SAM system */
	systick_setup(84000000);
    SystemInit();
	WDT->WDT_MR |= WDT_MR_WDDIS;
	configure_uart();
	can_init_def_tx_rx_mb(CAN_BR_1);
	PWM_init();
	adc_init();
	
	dac_init();
	motor_init();
	controller_init();
	solenoid_init();
	
		
	int16_t enc_pos;
	int16_t motor_pos;
	
	MOTOR_DIRECTION md = LEFT;
	
	int score = 0;
	uint8_t left_slider_pos, left_slider_pos_previous;
	
	printf("STARTING... ");
	
	set_direction(LEFT);
	set_speed(0x0F00);
	us_delay(2000000);
	
    while (1) 
    {
		CAN0_Handler();
		
		int punch = message.data[4];
		solenoid_punch(punch);
		
		left_slider_pos = message.data[2];
		int joy_value_x = map(message.data[0]-5, 0, 255, 2080, 920);
		// int16_t joy_speed = map(message.data[0]-50, 0, 255, 0x0100, 0xFFF);
		
		PWM_setDC(joy_value_x);
		
		if (left_slider_pos - abs(enc_pos) < 0)
		{
			md = LEFT;
			set_direction(md);
		}
		else if (left_slider_pos - abs(enc_pos) >= 0)
		{
			md = RIGHT;
			set_direction(md);
		}
		
		printf("Position is: %d \n", left_slider_pos);
		
		enc_pos = read_encoder();	
		motor_pos = position_controller(enc_pos,left_slider_pos);
		
		if (abs(abs(enc_pos)-left_slider_pos) < 10)
		{
			set_speed(0);
		}
		else{
			set_speed(motor_pos/8);
		}
		
		
		printf("Expected Position: %d \n", left_slider_pos);
		printf("Encoder Position: %d \n", abs( enc_pos));
		printf("Motor Position: %d \n", motor_pos);	
		
		left_slider_pos_previous = left_slider_pos;
		
		us_delay(100000);	
				
		uint16_t IR_value = read_IR();
		int goal = goal_scored(IR_value);
		/*
		if(goal==1){
			printf("         GOALLL!!!     ");
			score += 1;
		}
		printf("Score: %d \n", score);
		*/	
   }	
}
