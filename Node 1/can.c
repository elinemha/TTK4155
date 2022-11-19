/*
 * can.c
 *
 * Created: 20.10.2022 14:03:37
 *  Author: emmalle
 */ 
#include "can.h"

void can_init()
{
	mcp_init();
	mcp2515_write(MCP_CANCTRL, MODE_NORMAL); // Set Normal Mode
	uint8_t value = mcp2515_read(MCP_CANSTAT); // Read Mode
	if (( value & MODE_MASK ) != MODE_NORMAL ) {
		printf (" MCP2515 is NOT in normal mode!\n");
	}
}


void can_send(can_message* cm)
{	
	// First set CAN ID, length and data in appropriate registers
	mcp2515_write(TXB0SIDH, cm->id>>3);
	mcp2515_write(TXB0SIDL, cm->id<<5);
	mcp2515_write(TXB0DLC, cm->length);
	
	for(int i=0; i<cm->length; i++){
		mcp2515_write(TXB0D0 + i, cm->data[i]);
	}
	
	// After setting data in registers, send request-to-send
	mcp2515_request_to_send(MCP_RTS_TX0);
	
}

void can_rec(can_message* cm){
	// Read CAN ID, length and data by reading appropriate registers
	cm->id = (mcp2515_read(MCP_RXB0SIDH)<<3) | (mcp2515_read(MCP_RXB0SIDL)>>5);
	cm->length = mcp2515_read(MCP_RXB0DLC);
	for (int i = 0; i<cm->length; i++){
		cm->data[i] = mcp2515_read(MCP_RXB0D0 + i);
	}
	mcp2515_bit_modify(MCP_CANINTF, 0b00000001, 0); // Clearing receive buffer interrupt flag such that no interrupt is pending
}

// Custom printf function to print CAN values
void print_can(can_message *cm){
	printf("can id %d \n", cm->id);
	printf("can length %d\n", cm->length);
	printf("can data %s \n", cm->data);
}
