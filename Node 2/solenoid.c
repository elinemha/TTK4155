/*
 * solenoid.c
 *
 * Created: 17.11.2022 21:59:11
 *  Author: emmalle
 */ 

#include "solenoid.h"
#include "sam.h"

void solenoid_init(){		
	REG_PIOC_PER |= PIO_PC9;	//Enabling pin PC9
	REG_PIOC_OER |= PIO_PC9;	//Enabling PC9 as output
	REG_PIOC_PUDR |= PIO_PC9;	//Disables the pullup
}

void solenoid_punch(int punch){
	if (punch == 0)			//If joystick button on Node 1 is pressed
	{
		REG_PIOC_CODR |= PIO_PC9;	//Extend the solenoid (punch)
	}
	else if (punch != 0){		//If joystick is not pressed
		REG_PIOC_SODR |= PIO_PC9;	//No extention of the solenoid
	}
}
