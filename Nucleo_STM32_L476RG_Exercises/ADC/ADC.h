/*
 * ADC.h
 *
 *  Created on: Jan 8, 2024
 *      Author: antho
 */



#ifndef ADC_H_
#define ADC_H_
#include "stm32l476xx.h"

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
#define ADC_EOC 			(1U<<2)
#define ADC_EOCIE 			(1U<<2)

uint32_t adc_read();
void start_conversion();
void pc1_adc_init();

#endif /* ADC_H_ */
