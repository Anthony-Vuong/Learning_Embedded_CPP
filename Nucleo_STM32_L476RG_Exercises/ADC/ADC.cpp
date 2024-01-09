#include "ADC.h"

#define GPIOAEN_CLK			(1U<<0)
#define ANALOG_MODE 		(1U<<8) | (1U<<9)
#define ANALOG_SWITCH_PA4	(1U<<4)

#define ADCEN_CLK 			(1U<<13)

#define ADC_DEEPPWD			(1U<<29)
#define ADC_ADDIS			(1U<<1)
#define ADC_CNFG_CONT		(1U<<13)
#define ADC_CNFG_DISCEN		(1U<<16)

#define ADC_CH1 			(1U<<6) | (1U<<9)
#define ADC_LENGTH 			(1U<<0)

#define ADC_VREG			(1U<<28)
#define ADC_CALIB			(1U<<31)
#define ADC_EN				(1U<<0)
#define ADC_START			(1U<<2)
#define ADC_EOC 			(1U<<3)


void pc1_adc_init(){

	/*Enable clock access to GPIO A*/
	RCC->AHB2ENR |= GPIOAEN_CLK;

	/*Set the mode of PA1 to analog*/
	GPIOA->MODER |= ANALOG_MODE;

	/*Set analog connection to Port A Channel 1*/
	GPIOA->ASCR |= ANALOG_SWITCH_PA4;

	/*Configure the ADC module*/
	/*Enable clock access to ADC*/
	RCC->AHB2ENR |= ADCEN_CLK;

	/*Set the clock for ADC*/
	ADC123_COMMON->CCR &= ~(1U<<16);
	ADC123_COMMON->CCR |= 1U<<17;

	/*Single Mode - Not continuous*/
	//ADC1->CFGR &= ~(ADC_CNFG_CONT);
	/*Continuous Mode - Not single*/
	ADC1->CFGR &= ~(ADC_CNFG_DISCEN);
	ADC1->CFGR |= ADC_CNFG_CONT;

	/*Set sequence length to 0*/
	ADC1->SQR1 &= ~(ADC_LENGTH);

	/*Configure ADC parameters*/
	ADC1->SQR1 |= ADC_CH1;

	/*Set deep power down to 0*/
	ADC1->CR &= ~(ADC_DEEPPWD);

	/*Disable the ADC for calibration w/ ADDIS bit*/
	ADC1->CR |= ADC_ADDIS;

	/*Enable the voltage regulator*/
	ADC1->CR |= ADC_VREG;

	/*Start the calibration*/
	ADC1->CR |= ADC_CALIB;

	/*Enable the ADC*/
	ADC1->CR |= ADC_EN;
}


void start_conversion(){

	ADC1->CR |= ADC_START;

}

uint32_t adc_read(){

	while(!(ADC1->ISR & ADC_EOC)) {}

	// Comment out to run single conversion
	ADC1->ISR |= ADC_EOC;

	return (ADC1->DR);
}

