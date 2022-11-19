/*
 * motor.c
 *
 * Created: 19.11.2022 11:07:27
 *  Author: emmal
 */ 
#include "motor.h"
#include <stdint.h>


#define DIR PIO_PD10				// PD10 = MJ1 DIR
#define EN PIO_PD9					// PD9 = MJ1 EN
#define SEL PIO_PD2					// PD2 = MJ1 SEL
#define NOT_OE PIO_PD0				// PD0 = MJ1 !OE
#define NOT_RST PIO_PD1				// PD1 = MJ1 !RST

// D0-D7 ARE PC1-8
#define MJ2_PORT 0x1FE

void dac_init(){
	REG_PMC_PCER1 |= PMC_PCER1_PID38;
	REG_DACC_MR |= DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF | DACC_MR_STARTUP_0 |DACC_MR_TRGEN_DIS;
	REG_DACC_CHER = DACC_CHER_CH1;
}

void motor_init(){
	PIOD->PIO_PER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	PIOD->PIO_OER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	
	PIOC->PIO_PER |= MJ2_PORT;
	PIOC->PIO_ODR |= MJ2_PORT;
	
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER0 |= 1 << (ID_PIOC);
	
	PIOD->PIO_SODR |= EN;
	PIOD->PIO_SODR |= DIR;
	
	REG_PIOC_IFER = (0xFF<<1);
	REG_PIOC_PUDR = (0xFF)<<1;
	
}

void set_direction(MOTOR_DIRECTION direction)
{
	if(direction == LEFT)
	{
		PIOD->PIO_CODR |= (DIR);										// LEFT direction = 0
	}
	else
	{
		PIOD->PIO_SODR |= DIR;											// RIGHT direction = 1
	}
}

int16_t read_encoder()
{
	int16_t enc_data;
	REG_PIOD_CODR = NOT_OE;												//Set !OE low, to sample and hold the encoder value
	REG_PIOD_CODR = SEL;												//Set SEL low to output high byte
	us_delay(25);														//Wait approx. 20 microseconds for output to settle
	uint8_t high_byte = (uint8_t) ((REG_PIOC_PDSR & MJ2_PORT) >> 1);	//Read MJ2 to get high byte
	REG_PIOD_SODR = SEL;												//Set SEL high to output low byte
	us_delay(25);														//Wait approx. 20 microseconds
	uint8_t low_byte = (uint8_t) ((REG_PIOC_PDSR & MJ2_PORT) >> 1);		//Read MJ2 to get low byte
	
	REG_PIOD_CODR |= PIO_CODR_P1;
	REG_PIOD_SODR |= PIO_SODR_P1;
	PIOD->PIO_SODR = NOT_OE;											//Set !OE to high
	
	enc_data = ((high_byte<<8) | low_byte);
	
	if (enc_data & (1<<15)){
		enc_data = -((uint16_t)(~enc_data)+1);
	}
	
	//limit encoder to not go outside of range 0-255
	enc_data = (int16_t) (((enc_data*255)/9000));
	if (enc_data>0)
	{
		enc_data = 0;
		reset_encoder();
	}
	else if (enc_data < -255)
	{
		enc_data = -255;
	}
	return enc_data;
}


void set_speed(int16_t speed_joystick)
{
	REG_DACC_CDR = speed_joystick;
}

//the encoder reset pin (MJ1 !RST) will reset the internal counter to 0 when pulled low.
void reset_encoder(){
	PIOD->PIO_CODR |= NOT_RST;
	us_delay(100);
	PIOD->PIO_SODR |= NOT_RST;
}
