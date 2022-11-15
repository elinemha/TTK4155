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

#define CAN_BR_1 0x00290165


int map(int x, int in_min, int in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR |= WDT_MR_WDDIS;
	configure_uart();
	can_init_def_tx_rx_mb(CAN_BR_1);
	//timer_init_0();
	PWM_init();
	adc_init();
	
	int score = 0;

	/*
	CAN_MESSAGE cm;
	uint8_t tx_mb_id = 0x00;
	uint8_t rx_mb_id = 0x01;*/

    /* Replace with your application code */
	//char b = "b";
	
	//CAN_MESSAGE cm;
	
	
    while (1) 
    {
		CAN0_Handler();
		//can_receive(&cm, 1);
		
		int joy_value = map(message.data[0], 0, 255, 920, 2080);
		
		PWM_setDC(joy_value);
	
		//can_receive(&cm, rx_mb_id);
		//can_send(&cm, tx_mb_id);
		//print_can(&cm);
		//printf("Node 2");
		uint16_t a = read_IR();
		int b = goal_scored(a);
		if(b==1){
			printf("         GOALLL!!!     ");
			score += 1;
		}
		printf("Score: %d \n", score);
		
    }
}
