/*
 * Node_2.c
 *
 * Created: 10.11.2022 14:24:54
 * Author : rohank
 */ 


#include "sam.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "uart.h"
#include "printf-stdarg.h"

#define CAN_BR_1 0x00290165

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	can_init_def_tx_rx_mb(CAN_BR_1);
	/*
	CAN_MESSAGE cm;
	uint8_t tx_mb_id = 0x00;
	uint8_t rx_mb_id = 0x01;*/

    /* Replace with your application code */
	//char b = "b";
	
	CAN0_Handler();
	
	
    while (1) 
    {
		
	
		//can_receive(&cm, rx_mb_id);
		//can_send(&cm, tx_mb_id);
		//print_can(&cm);
		//printf("Node 2");
    }
}
