/*
 * controller.c
 *
 * Created: 16.11.2022 13:19:44
 *  Author: emmalle
 */ 


//#include <stdlib.h>
#include "controller.h"

#define DIR PIO_PD10
#define EN PIO_PD9
#define SEL PIO_PD2
#define NOT_OE PIO_PD0
#define NOT_RST PIO_PD1

// D0-D7 ARE PC1-8
#define MJ2_PORT 0x1FE


///PI defs

float Time_sample = 0.0001;
float kp;
float ki;
float kd;

float reference;
float integral;
float prev_error;
float derivative;

int16_t maxOutput = 15000; //fact check
uint8_t max_u = 51200;

volatile uint32_t ms_ticks = 0;

void systick_setup(uint32_t sys_freq) {
	SysTick->LOAD = (sys_freq / 1000000U) - 1U; //1ms tick
	SysTick->VAL = 0x00; //explicitly set start value (undefined on reset)
	SysTick->CTRL |= (1U << SysTick_CTRL_TICKINT_Pos) | (1U << SysTick_CTRL_CLKSOURCE_Pos); //enable systick interrupt, source processor clock
	SCB->SHP[8] = 0U; //set SysTick interrupt priority (default: 0, the highest)
	SysTick->CTRL |= (1U << SysTick_CTRL_ENABLE_Pos); //enable SysTick
}

void SysTick_Handler(void)
{
	ms_ticks++;
}
uint32_t getMillis(void)
{
	return ms_ticks;
}
void ms_delay(uint16_t delay)
{
	uint32_t prevMillis = getMillis() + delay;
	//while (getMillis() <= prevMillis + delay){}
	while (getMillis() != prevMillis);
}


void dac_init(){

	REG_PMC_PCER1 |= PMC_PCER1_PID38;
	//REG_DACC_CR |= DACC_CR_SWRST;
	REG_DACC_MR |= DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF | DACC_MR_STARTUP_0 |DACC_MR_TRGEN_DIS;
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
	//REG_PIOD_SODR |= DIR;	
	
	REG_PIOC_IFER = (0xFF<<1);
	REG_PIOC_PUDR = (0xFF)<<1;
	
	
	//PIOD->PIO_CODR |= NOT_RST;
	//PIOD->PIO_SODR |= NOT_RST;
	
}

void set_direction(MOTOR_DIRECTION direction)
{
	if(direction == LEFT)
	{
		PIOD->PIO_CODR |= (DIR);
	}
	else
	{
		PIOD->PIO_SODR |= DIR;
	}
}

int16_t read_encoder()
{
	int16_t enc_data;
	//REG_PIOD_CODR |= (NOT_OE);
	//REG_PIOD_CODR |= (SEL);
	//PIOD->PIO_ODSR &= ~(NOT_OE);
	//PIOD->PIO_ODSR &= ~(SEL);
	REG_PIOD_CODR = NOT_OE;
	REG_PIOD_CODR = SEL;
	ms_delay(25);

	//enc_byte |= ((REG_PIOC_PDSR & 0xFF) << 8);
	uint8_t high_byte = (uint8_t) ((REG_PIOC_PDSR & MJ2_PORT) >> 1);
	REG_PIOD_SODR = SEL;
	
	
	ms_delay(25);
	
	//enc_byte |= ((REG_PIOC_PDSR >> 1) & 0xFF);
	uint8_t low_byte = (uint8_t) ((REG_PIOC_PDSR & MJ2_PORT) >> 1);
	
	REG_PIOD_CODR |= PIO_CODR_P1;
	REG_PIOD_SODR |= PIO_SODR_P1;
	PIOD->PIO_SODR = NOT_OE;
	
	enc_data = ((high_byte<<8) | low_byte);
	
	if (enc_data & (1<<15)){
		enc_data = -((uint16_t)(~enc_data)+1);
	}
	
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
	
	//while(!REG_DACC_ISR & DACC_ISR_EOC);
}

void reset_encoder(){
	PIOD->PIO_CODR |= NOT_RST;
	ms_delay(100);
	PIOD->PIO_SODR |= NOT_RST;
}

/*
void calibrate_encoder(){
	
}*/


void controller_init()
{
	kp = 1;
	ki = 2;
	kd = 0.1;

	reference   = 0;
	integral    = 0;
	prev_error  = 0;

}


// PI controller for motor position
int16_t position_controller(int16_t enc_data, uint8_t slider_pos)
{
	reference = slider_pos;
	float error = reference - abs(enc_data);				// position = y
	integral += error * Time_sample;
	derivative = -(error-prev_error)/Time_sample;
	
	int16_t sum_error = 0;
	sum_error += error;
	
	if (error<1)
	{
		integral = 0;
	}
	
	int32_t u_p = kp*error;
	int32_t u_i = ki*integral;
	int32_t u_d = kd*derivative;
	
	int16_t u_t = u_p + u_i + u_d;				//u_t output from PI sum operation, u[n] = Kp*e[n]+T*Ki*sum_error
	
	// avoiding integral windup
	if((abs(sum_error) > maxOutput) && sum_error >= 0){
		sum_error = maxOutput;
	}
	else if ((abs(sum_error) > maxOutput) && sum_error <= 0){
		sum_error = -maxOutput;
	}
	
	// avoiding gain windup
	if ((abs(u_t) > maxOutput) && u_t >= 0){
		u_t = maxOutput;
	}
	else if ((abs(u_t) > maxOutput) && u_t <= 0){
		u_t = -maxOutput;
	}
	
	prev_error = error;         //stores error for next run
	
	return abs(u_t);
}




/**
// PID controller for motor position
int16_t position_controller(int16_t enc_data, uint8_t joystick_pos)
{
	int16_t sum_error = 0;
	//float reference =  joystick_pos;					// r = joystick position
	float error = abs(joystick_pos) - abs(enc_data);				// encoder position = y
	printf("reference: %d \n", joystick_pos);
	printf("encoder: %d \n", enc_data);
	sum_error += error;
	integral = sum_error * Time_sample;
	derivative = (error-prev_error)/Time_sample;
	
	//Convert joystick position to valid range
	//reference = enc_data;
	
	
	if (error<1)
	{
		integral = 0;
	}
	
	int32_t u_p = kp*error;
	int32_t u_i = ki*integral;
	int32_t u_d = kd*derivative;
	
	int16_t u_t = u_p + u_i; // + u_d;				//u_t output from PI sum operation, u[n] = Kp*e[n]+T*Ki*sum_error
	
	printf("u_t: %d \n", u_t);
	prev_error = error;							//stores error for next run
	
	// limit total gain
	if (u_t > max_u)
	{
		u_t = max_u;
	}
	
	if (u_t < -max_u)
	{
		u_t = -max_u;
	}
	
	// avoiding gain windup
	// avoiding integral windup
	if((abs(sum_error) > maxOutput) && sum_error >= 0){
		sum_error = maxOutput;
	}
	else if ((abs(sum_error) > maxOutput) && sum_error <= 0){
		sum_error = -maxOutput;
	}
	
	return abs(u_t);
}
*/
