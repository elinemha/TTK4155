
#include "timer.h"
#include "sam.h"

#define MCK 84000000
#define dutyperiode 20e-3
#define pwm_min 9e-4
#define pwm_max 21e-4
#define RC_DUTY 840000
#define RA_MID 63000
#define RA_MIN 37800
#define RA_MAX 88200


void timer_init_0(void){
	PMC->PMC_PCER0 = (1<<ID_TC0);

	
	
	
	
	
	
	
	
	
	
	
	
	/*Clear Wakekey here?SCH
	PMC->PMC_PCER0 = (1<<ID_TC0);
	PMC->PMC_PCER0 |= PMC_PCER0_PID25;	//enable timer0
	while((PMC->PMC_PCER0 & PMC_PCSR0_PID25));
	PIOB->PIO_PDR |= PIO_PDR_P25; //Disable pio controll of PB25, aka TIOA0
	PIOB->PIO_ABSR |= PIO_ABSR_P25;	//Choose B peripheral
	PWM->PWM_WPCR = (PWM_WPCR_WPMD(0) | (0x3F<<1));
	PWM->PWM_DIS = (1<<6);
	PWM->PWM_CLK = (PWM_CLK_DIVA(1) | PWM_CLK_PREA(0x07));
	PWM->PWM_CH_NUM[6].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL;
	
	
	PWM->PWM_CH_NUM[6].PWM_CPRD = PWM_CPRD_CPRD(0x3345);
	PWM->PWM_CH_NUM[6].PWM_CDTY = PWM_CDTY_CDTY(0);
	PWM->PWM_ENA=(1<<6);
	while((PWM->PWM_SR & (1<<6))==0);
	return 0;
	///////////DB
	PWM->PWM_SCM |= PWM_SCM_UPDM_MODE0;
	PWM->PWM_SCM |= PWM_SCM_SYNC0;
	PWM->PWM_ENA |= PWM_ENA_CHID0;
	PWM->PWM_CPRDUPD |= XXX
	PWM->PWM_SCUC |= PWM_SCUC_UPDULOCK;
	
	
		PMC->PMC_PCER0 = (1<<ID_TC0);
		PIOB->PIO_PDR |= PIO_PDR_P25;
		PIOB->PIO_ABSR |= PIO_ABSR_P25;
		
		TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_WAVE;
		TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK1;
		TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVSEL_UPDOWN_RC;
		TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_ACPC_SET;
		TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_ACPA_CLEAR;
		
		TC0->TC_CHANNEL[0].TC_RC = RC_DUTY;
		TC0->TC_CHANNEL[0].TC_RA = RA_MID;
		
		TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPAS | TC_IER_CPCS;
		TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	


	REG_PMC_PCER1 |= PMC_PCER1_PID36;				  // Enable PWM
	REG_PIOC_ABSR |= PIO_ABSR_P19;					  // Set PWM pin perhipheral C
	REG_PIOC_PDR |= PIO_PDR_P19;					  // Set PWM pin to an output1
	REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42); // Set the PWM clock rate to 2MHz (84MHz/42)
	REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;  // Enable dual slope PWM and set the clock source as CLKA
	REG_PWM_CPRD5 = 20000;							  // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz = 20ms
	REG_PWM_CDTY5 = 1500;			  // Set the PWM duty cycle to 1500 - centre the servo
	REG_PWM_ENA = PWM_ENA_CHID5;					  // Enable the PWM channel
	
	*/
		


	

	
}

