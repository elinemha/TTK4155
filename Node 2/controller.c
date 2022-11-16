/*
 * controller.c
 *
 * Created: 16.11.2022 13:19:44
 *  Author: emmalle
 */ 



#include "controller.h"

#define DIR PIO_PD10
#define EN PIO_PD9
#define SEL PIO_PD2
#define NOT_OE PIO_PD0
#define NOT_RST PIO_PD1

// D0-D7 ARE PC1-8
#define MJ2_PORT 0x1FE

float kp;
float ki;

float reference;
float integral;
float prev_error;

int16_t maxOutput = 8800; //fact check
uint8_t minOutput = 0;

void dac_init(){

	REG_PMC_PCER1 |= PMC_PCER1_PID38;
	
	//REG_DACC_CR |= DACC_CR_SWRST;
	REG_DACC_MR |= DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF | DACC_MR_STARTUP_0;
	//REG_DACC_CHDR = DACC_CHDR_CH1; 
	REG_DACC_CHER = DACC_CHER_CH1;
	//REG_DACC_CDR = 0;
	//REG_PMC_PCER0 |= NOT_OE
}

void motor_init(){
	//REG_PIOD_PER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	PIOD->PIO_PER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	//REG_PIOD_OER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	PIOD->PIO_OER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	
	//REG_PIOC_PER |= MJ2_PORT;
	PIOC->PIO_PER |= MJ2_PORT;
	//REG_PIOC_ODR |= MJ2_PORT;
	PIOC->PIO_ODR |= MJ2_PORT;
	
	//REG_PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	//REG_PMC_PCER0 |= 1 << (ID_PIOC);
	PMC->PMC_PCER0 |= 1 << (ID_PIOC);
	
	//REG_PIOD_SODR |= EN;
	PIOD->PIO_SODR |= EN;
	//REG_PIOD_SODR |= SEL;
	//REG_PIOD_SODR |= DIR;
	PIOD->PIO_SODR |= DIR;	
	
	REG_PIOC_PUDR |= MJ2_PORT;
}

void set_direction(MOTOR_DIRECTION dir)
{
	if(dir == LEFT)
	{
		PIOD->PIO_ODSR &= ~(DIR);
	}
	else
	{
		PIOD->PIO_ODSR |= DIR;
	}
}

int16_t read_encoder()
{
	REG_PIOD_ODSR &= ~(NOT_OE);
	REG_PIOD_ODSR &= ~(SEL);
	//PIOD->PIO_ODSR &= ~(NOT_OE);
	//PIOD->PIO_ODSR &= ~(SEL);
	//delay
	uint8_t high_byte = (uint8_t) ((REG_PIOC_PDSR & MJ2_PORT) >> 1);
	REG_PIOD_ODSR |= SEL;
	//delay
	uint8_t low_byte = (uint8_t) ((PIOC->PIO_PDSR & MJ2_PORT) >> 1);
	PIOD->PIO_ODSR |= NOT_OE;
	return (int16_t) ((high_byte << 8) | low_byte);
}

void set_speed(uint8_t speed_joystick)
{
	REG_DACC_CDR = speed_joystick;
	while(!REG_DACC_ISR & DACC_ISR_EOC);
}

void controller_init(float _kp, float _ki)
{
	kp = 1.5;
	ki = 2.4;

	reference   = 0;
	integral    = 0;
	prev_error  = 0;

}

// PI controller for motor position
/*
void position_controller(float r, float y, float dt, uint8_t position)
{
	float error = r - y;
	integral += error * dt;
	prev_error = error;         //stores error for next run

	// Read measurement from encoder

	//Convert joystick position to valid range
	int16_t reference = maxOutput * 0.01 * position;
	
	int16_t sum_error += error;
	if((abs(sum_error) > maxOutput) && sum_error >= 0)
	sum_error = maxOutput;

	else if ((abs(sum_error) > maxOutput) && sum_error <= 0)
	sum_error = -maxOutput;

	int16_t output = kp*error + ki*integral;
	if ((abs(output) > maxOutput) && output >= 0)
	output = maxOutput;
	else if ((abs(output) > maxOutput) && output <= 0)
	output = -maxOutput;

	return output;
}
*/

// method for setting kp value from node 1 (needs more implementation in node 1)
void remote_kp(uint8_t new_kp)
{
	kp = new_kp;
}
