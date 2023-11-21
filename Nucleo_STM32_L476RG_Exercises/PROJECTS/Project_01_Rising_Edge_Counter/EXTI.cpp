/*
 * EXTI.cpp
 *
 *  Created on: Nov 16, 2023
 *      Author: antho
 */

#include "EXTI.h"
#include "LED.h"

void button_exti_init(){
	/*Disable global interrupt*/
	__disable_irq();

	/*Enable Clock access for SYSCGF*/
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGN_EN;

	init_button();

	/*Select PORTC for EXTI13*/
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_PC13;

	/*Unmask EXTI13*/
	EXTI->IMR1 |= EXTI_IMR1_IM_BIT;

	/*Select falling edge trigger*/
	EXTI->FTSR1 |= EXTI_FTSR1_FT13_x;

	//EXTI->RTSR1 |= EXTI_RTSR1_RT13;

	/*Enable EXTI13 line in NVIC*/
	//NVIC_SetPriority(EXTI15_10_IRQn, 0x03);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/*Enable global interrupts*/
	__enable_irq();
}
