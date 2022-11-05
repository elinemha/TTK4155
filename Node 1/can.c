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
	mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);	
	
}

void can_send(can_message cm)
{
	mcp2515_write(0xaa, (uint8_t) cm.id);
	
	for (uint8_t i=0; i<cm.length; i++)
	{
		mcp2515_write(0xaa, (uint8_t) cm.data[i]);
	}
}

void canned(can_message* cm)
{
	//ID: TXBnSIDH & TXBnSIDL
	//Length: TXBnDLC
	//Data: TXBnDm
	//+ RTS (TXBnCTRL.TXREQ)
	
	mcp2515_write(TXB0SIDH, cm->id>>3);
	mcp2515_write(TXB0SIDL, cm->id<<5);
	mcp2515_write(TXB0DLC, cm->length);
	
	for(int i=0; i<cm->length; i++){
		mcp2515_write(TXB0D0 + i, cm->data[i]);
	}
	
	mcp2515_request_to_send(MCP_RTS_TX0);
	
}

void can_rec(can_message* cm){
	
	//uint8_t var1 =  mcp2515_read(MCP_RXB0SIDH)>>3;
	//uint8_t var2 =  mcp2515_read(MCP_RXB0SIDL)>>5;
	cm->id = (mcp2515_read(MCP_RXB0SIDH)<<3) | (mcp2515_read(MCP_RXB0SIDL)>>5);
//	cm->id = mcp2515_read(MCP_RXB0SIDH);
	cm->length = mcp2515_read(MCP_RXB0DLC);
	for (int i = 0; i<cm->length; i++)
	{
		cm->data[i] = mcp2515_read(MCP_RXB0D0 + i);
	}
	mcp2515_bit_modify(MCP_CANINTF, 0b00000001, 0);
}

void print_can(can_message *cm){
	printf("can id %d \n", cm->id);
	printf("can length %d\n", cm->length);
	printf("can data %s \n", cm->data);
	
}