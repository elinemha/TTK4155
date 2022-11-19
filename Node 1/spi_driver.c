#include "spi_driver.h"

void SPI_Init(void) // Initialize SPI in Master mode
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);
	DDRB &= ~(1<<PB1) & ~(1<<PB2) & ~(1<<PB3) & ~(1<<PB6);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	PORTB |= (1<<PB4);
}
void SPI_write(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_read(void)
{
	SPI_write(0); // Reading SPI is same as writing it. You just have to wait for transmission to complete
	return SPDR;
}

void SPI_SlaveInit(void) // Initializing function for SPI in Slave mode
{
	/* Set MISO output, all others input */
	DDRB = (1<<DDB6);
	/* Enable SPI */
	SPCR = (1<<SPE);
}

char SPI_SlaveReceive(void) // Receive function for SPI in Slave mode
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return data register */
	return SPDR;
}