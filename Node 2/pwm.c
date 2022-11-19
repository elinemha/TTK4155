
#include "pwm.h"
#include "sam.h"

#define RC_DUTY 840000
#define RA_MID 63000
#define RA_MIN 47800 //37800
#define RA_MAX 57200 //88200

#define duty_slpe 504
#define duty_intercept 37800


void PWM_init()
{
	REG_PMC_PCER1 |= PMC_PCER1_PID36;
	REG_PIOC_PDR |= PIO_PDR_P19;
	REG_PIOC_ABSR |= PIO_ABSR_P19;
	REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);//2Mhz
	REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPOL | PWM_CMR_CPRE_CLKA;
	REG_PWM_CPRD5 = 20000;
	REG_PWM_CDTY5 = 1500; 
	REG_PWM_ENA = PWM_ENA_CHID5;
}


// set PWM duty cycle 20%
void PWM_setDC(int value) // value should be between 900 and 2100
{
   if(value<900){
	   value = 900;
   }
   if(value>2100){
	   value = 2100;
   }
   REG_PWM_CDTY5 = value;
	
}