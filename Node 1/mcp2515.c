
#include "mcp2515.h"
#include "spi_driver.h"

#define can_cpu 16000000
#define number_tq 16
#define baudrate 250000

void mcp_init()
{
	uint8_t value ;
	SPI_Init();
	mcp2515_reset();
	//mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);
	value = mcp2515_read( MCP_CANSTAT);
	printf("%x \n", value);
	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configs mode after reset !\n");
	}
	uint8_t BRP = can_cpu / (2* number_tq * baudrate);
	mcp2515_bit_modify(MCP_CANINTE, 0b00000001, 0);
	mcp2515_bit_modify(MCP_CANINTF, 0b00000001, 0);
}

uint8_t mcp2515_read(uint8_t address)
{
	uint8_t result ;
	PORTB &= ~(1 << PB4 ); // Select CAN - controller
	SPI_write( MCP_READ ); // Send read instruction
	SPI_write( address ); // Send address
	result = SPI_read () ; // Read result
	PORTB |= (1 << PB4 ); // Deselect CAN - controller
	return result ;
}

void mcp2515_write(uint8_t address, uint8_t data)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller
	SPI_write( MCP_WRITE ); // Send read instruction
	SPI_write( address ); // Send address
	SPI_write( data ); // Send data
	PORTB |= (1 << PB4 ); // Deselect CAN - controller
}

void mcp2515_request_to_send(uint8_t buffer)
{
	PORTB &= ~(1 << CAN_CS );
	SPI_write(buffer);
	PORTB |= (1 << CAN_CS );
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	PORTB &= ~(1 << CAN_CS );
	SPI_write(MCP_BITMOD);
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);
	PORTB |= (1 << CAN_CS );
	
}

void mcp2515_reset()
{
	PORTB &= ~(1 << PB4 );
	SPI_write(MCP_RESET);
	PORTB |= (1 << PB4 );
	_delay_ms(10);
		
}

uint8_t mcp2515_read_status()
{
	PORTB &= ~(1 << CAN_CS );
	SPI_write(MCP_READ_STATUS);
	uint8_t status = SPI_read();
	PORTB |= (1 << CAN_CS );
	return status;
}

uint8_t mcp2515_rx_status()
{
	PORTB &= ~(1 << CAN_CS );
	SPI_write(MCP_RX_STATUS);
	uint8_t status = SPI_read();
	PORTB |= (1 << CAN_CS );
	return status;
}

uint8_t mcp_read_rx0_buffer()
{
	uint8_t result ;
	PORTB &= ~(1 << PB4 );
	SPI_write(MCP_READ_RX0);
	result = SPI_read () ; // Read result
	PORTB |= (1 << PB4 );
	return result;
}

void mcp_write_tx0_buffer(uint8_t data)
{
	PORTB &= ~(1 << PB4 );
	SPI_write(MCP_LOAD_TX0);
	SPI_write(data); // Send data
	PORTB |= (1 << PB4 );
}