/*
 * EXTI.h
 *
 *  Created on: Nov 16, 2023
 *      Author: antho
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32l476xx.h"

void button_exti_init();

#define RCC_APB2ENR_SYSCFGN_EN		(1U<<0)
#define SYSCFG_EXTICR4_PC13			(1U<<5)
#define EXTI_IMR1_IM_BIT			(1U<<13)
#define EXTI_FTSR1_FT13_x				(1U<<13)
#define LINE13						(1U<<13)
//#define EXTI_RTSR1_RT13				(1U<<13)

#endif /* EXTI_H_ */
