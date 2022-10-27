#include "spi_driver.h"

void SPI_Init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);
	DDRB &= ~(1<<PB1) & ~(1<<PB2) & ~(1<<PB3) & ~(1<<PB6);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//printf("SPCR: %02X \n", SPCR);
	PORTB |= (1<<PB4);
}
void SPI_write(char cData)
{
	/* Start transmission */
	SPDR = cData;
	//printf("SPI Write: %02X \n", SPDR);
	//printf("SPI Write 2: %02X \n", cData);
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_read(void)
{
	/* Start transmission */
	//SPDR = cData;
	/* Wait for transmission complete */
	SPI_write(0);
	//while(!(SPSR & (1<<SPIF)));
	//printf("SPI Read: %02X \n", SPDR);
	return SPDR;
}

void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDRB = (1<<DDB6);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return data register */
	return SPDR;
}