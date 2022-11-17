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
#include "timer.h"
#include "pwm.h"
#include "adc_due.h"
#include "controller.h"
#include "sam3x8e.h"


#define CAN_BR_1 0x00290165

#define LED1 PIO_PA19
#define LED2 PIO_PA20

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
	//timer_init_0();
	PWM_init();
	adc_init();
	
	dac_init();
	motor_init();
	controller_init();
	
	int16_t enc_pos;
	int16_t motor_pos;
	uint8_t expected_pos = 0;
	
	MOTOR_DIRECTION md = RIGHT;
	
	int score = 0;
	
	uint8_t pos, pos_pre;
	
	printf("STARTING... ");
	/*
	CAN_MESSAGE cm;
	uint8_t tx_mb_id = 0x00;
	uint8_t rx_mb_id = 0x01;*/

    /* Replace with your application code */
	//char b = "b";
	
	//CAN_MESSAGE cm;
	//set_speed(0x08F0);
	
    while (1) 
    {
		CAN0_Handler();
		//can_receive(&cm, 1);
		pos = message.data[2];
		int joy_value = map(message.data[0], 0, 255, 920, 2080);
		int16_t joy_speed = map(message.data[0]-50, 0, 255, 0x0100, 0xFFF);
		
		PWM_setDC(joy_value);
			
		if (pos < pos_pre-5)
		{
			md = LEFT;
			set_direction(md);
			expected_pos -= 1;
			if (expected_pos < 0)
			{
				expected_pos = 0;
			}
		}
		else if (pos > pos_pre+5)
		{
			md = RIGHT;
			set_direction(md);
			expected_pos += 1;
			if (expected_pos >= 255)
			{
				expected_pos = 255;
			}
		}
		
		enc_pos = read_encoder();
		
		motor_pos = position_controller(enc_pos,pos);
		//motor_init();
		set_speed(motor_pos/8);
		
		//motorSpeedPos(message.data[2]);
		
		
		printf("Expected Position: %d \n", message.data[2]);
		printf("Encoder Position: %d \n", enc_pos);
		printf("Motor Position: %d \n", motor_pos);
		
		
		pos_pre = pos;
		
		ms_delay(100000);	
				
		//can_receive(&cm, rx_mb_id);
		//can_send(&cm, tx_mb_id);
		//print_can(&cm);
		//printf("Node 2");
		uint16_t a = read_IR();
		int b = goal_scored(a);
		/*
		if(b==1){
			printf("         GOALLL!!!     ");
			score += 1;
		}
		printf("Score: %d \n", score);
		*/
		
    }
}
