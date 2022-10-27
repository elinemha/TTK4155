/*
 * can.h
 *
 * Created: 20.10.2022 14:03:54
 *  Author: emmalle
 */ 

#include "mcp2515.h"
#include <stdint.h>


#ifndef CAN_H_
#define CAN_H_

typedef struct {
	unsigned short id;
	uint8_t length;
	char data[8];
} can_message ;

void can_init();
void can_send(can_message cm);
void canned(can_message* cm);
void can_rec(can_message* cm);
void print_can(can_message *cm);

#endif /* CAN_H_ */