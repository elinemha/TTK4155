/*
 * solenoid.c
 *
 * Created: 17.11.2022 21:59:11
 *  Author: emmalle
 */ 

#include "solenoid.h"
#include "sam.h"

void solenoid_init(){
	REG_PIOC_PER |= PIO_PC9;
	REG_PIOC_OER |= PIO_PC9;
	REG_PIOC_PUDR |= PIO_PC9;
}

void solenoid_punch(){
	if (punch == 1)
	{
		REG_PIOC_CODR |= PIO_PC9;
	}
	else if (punch == 0){
		REG_PIOC_SODR |= PIO_PC9;
	}
}
//Define punch = joy_pos.data[4] in main
//Call function
//Get the button to work. It is still 0 all the time.  from NOde 1. Check with oscilloscope?
