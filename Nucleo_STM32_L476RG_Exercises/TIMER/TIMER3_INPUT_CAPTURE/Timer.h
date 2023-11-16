/*
 * Timer.h
 *
 *  Created on: Nov 15, 2023
 *      Author: antho
 */

#ifndef TIMER_H_
#define TIMER_H_


void timer_init();
void timer_output_compare_init();
void timer_input_capture_init();

#define TIM2_SR_UIF				(1U<<0)
#define RCC_APB1ENR1_TIM3_EN	(1U<<1)
#define TIM3_CCMR1_CC1S			(1U<<0)
#define TIM3_CCER_CC1E			(1U<<0)
#define TIM3_SR_CCIF			(1U<<1)


#endif /* TIMER_H_ */
