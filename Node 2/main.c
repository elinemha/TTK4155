/*
 * GccApplication2.c
 *
 * Created: 03.11.2022 14:07:59
 * Author : elinemha
 */ 

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "sam.h"
#include "sam3x8e.h"

#include "uart.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "printf-stdarg.h"

#define CAN_BR_PRESET 0x00290165

int main(void)
{
   
    SystemInit();
	configure_uart();
	can_init_def_tx_rx_mb(CAN_BR_PRESET);

    while (1) 
    {
CAN_BR_PROPAG
		
	}

}
