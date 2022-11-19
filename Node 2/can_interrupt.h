/*
 * can_interrupt.h
 *
 * Author: Gustav O. Often and Eivind H. Jølsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 
#include "can_controller.h"


#ifndef CAN_INTERRUPT_H_
#define CAN_INTERRUPT_H_

// Defining CAN message here so that it can be used in main.c after it is read by CAN0_Handler
CAN_MESSAGE message;

void CAN0_Handler( void );


#endif /* CAN_INTERRUPT_H_ */