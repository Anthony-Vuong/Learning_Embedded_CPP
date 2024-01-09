/*
 * ADC.h
 *
 *  Created on: Jan 8, 2024
 *      Author: antho
 */

#include "stm32l476xx.h"

#ifndef ADC_H_
#define ADC_H_

uint32_t adc_read();
void start_conversion();
void pc1_adc_init();

#endif /* ADC_H_ */
