#include "stm32l476xx.h"
#include "Timer.h"
#include "LED.h"

#define APB1_TIM2_EN		(1U<<0)
#define TIM2_CR1_EN			(1U<<0)
#define TIM3_CR1_EN			(1U<<0)
#define OC_TOGGLE			(1U<<4) | (1U<<5)
#define TIM2_CCER_CCIE		(1U<<0)


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

void timer_interrupt_init(){
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

	TIM2->DIER |= TIM2_DIER_UIE;

	NVIC_EnableIRQ(TIM2_IRQn);

}


void timer_output_compare_init(){

	/*Enable clock access for GPIOA*/
	RCC->AHB2ENR |= GPIOAEN;

	/*Set PA5 to AF mode*/
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	/*Set PA5 to AF mode to TIM2_CH1*/
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] &= ~(1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	/*Enable clock access*/
	RCC->APB1ENR1 |= APB1_TIM2_EN;

	/*Set pre-scaler*/
	TIM2->PSC = 400 - 1;

	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;

	/*Set output compare toggle mode*/
	TIM2->CCMR1 = OC_TOGGLE;

	/*Enable tim2 ch1 in compare mode*/
	TIM2->CCER |= TIM2_CCER_CCIE;

	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 |= TIM2_CR1_EN;

}

void timer_input_capture_init(){

	/*Enable clock access to GPIOA*/
	RCC->AHB2ENR |= GPIOAEN;

	/*Set PA6 to AF mode - look on datasheet for Tim3_CH1*/
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	/*Set PA6  AF type to Tim3_CH1 AF2	 */
	GPIOA->AFR[0] &= ~(1U<<24);
	GPIOA->AFR[0] |= (1U<<25);
	GPIOA->AFR[0] &= ~(1U<<26);
	GPIOA->AFR[0] &= ~(1U<<27);

	/*Enable clock access to Tim3*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3_EN;

	/*Set prescaler*/
	TIM3->PSC = 4000 - 1;

	/*Set CH1 to input capture*/
	TIM3->CCMR1 |= TIM3_CCMR1_CC1S;

	/*Set CH1 to capture at every rising edge*/
	TIM3->CCER |= TIM3_CCER_CC1E;

	/*Enable Tim3*/
	TIM3->CR1 |= TIM3_CR1_EN;

}

