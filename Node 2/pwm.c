
#include "pwm.h"
#include "sam.h"

void PWM_init()
{
	REG_PMC_PCER1 |= PMC_PCER1_PID36;					//Enable clock
	REG_PIOC_PDR |= PIO_PDR_P19;						
	REG_PIOC_ABSR |= PIO_ABSR_P19;						
	REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);			//Divide the MCK by 42 making the clock 2Mhz
	REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPOL | PWM_CMR_CPRE_CLKA;		//Left/Center allign channel, waveform starts at low/high level, Clock A
	REG_PWM_CPRD5 = 20000;							//Length of periode 20ms
	REG_PWM_CDTY5 = 1500; 							//Set initial pulse length to 1500 (neutral)
	REG_PWM_ENA = PWM_ENA_CHID5;						//Enable PWM output on channel 5
}


void PWM_setDC(int value) //Set length of pulse
{
   if(value < 900){
	   value = 900;		//Min length of pulse 900
   }
   if(value > 2100){		//Max length of pulse 2100
	   value = 2100;
   }
   REG_PWM_CDTY5 = value;	//Set 
	
}
