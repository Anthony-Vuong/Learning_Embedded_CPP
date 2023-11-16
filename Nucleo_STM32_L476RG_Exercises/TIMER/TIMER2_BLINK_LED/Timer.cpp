#include "stm32l476xx.h"
#include "Timer.h"

#define APB1_TIM2_EN		(1U<<0)
#define TIM2_CR1_EN			(1U<<0)


void timer_init(){
	/*Enable clock access*/
	RCC->APB1ENR1 |= APB1_TIM2_EN;

	/* Calculate 1 second interrupt */
	/* SYS_CLK is 4MHz
	 *
	 * To get Frequency we use this formula:
	 *
	 * (SYS_CLK / (PSC * ARR_VAL))
	 *
	 * T(period) = 1/Frequency
	 *
	 * T = 1 and Freq = 1 to get 1sec interval
	 *
	 * PSC = 400 - 1, ARR = 10000 - 1
	 *
	 * */

	/*Set pre-scaler*/
	TIM2->PSC = 400 - 1;

	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;

	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 |= TIM2_CR1_EN;

}
