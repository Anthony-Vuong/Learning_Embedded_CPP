#include "stm32l476xx.h"
#include "systick.h"

//
#define RCC_GPIOA_EN			(1U<<0)
#define RCC_GPIOB_EN			(1U<<1)
#define RCC_TIM1_EN				(1U<<11)

//
#define GPIOA_PA8_MODE_L		(1U<<16)
#define GPIOA_PA8_MODE_H		(1U<<17)
#define GPIOA_PA8_AFR_L			(1U<<3) | (1U<<2) | (1U<<1)
#define GPIOA_PA8_AFR_H			(1U<<0)

//
#define GPIOB_PB8_MODE_L		(1U<<16)
#define GPIOB_PB8_MODE_H		(1U<<17)
#define GPIOB_PB9_MODE_L		(1U<<18)
#define GPIOB_PB9_MODE_H		(1U<<19)

//
#define TIM1_CCER_CC1P			(1U<<1)
#define TIM1_CCER_CC1E			(1U<<0)
#define TIM1_CCMR1_CC1S			(1U<<1) | (1U<<0)
#define TIM1_CCMR1_OC1M_L		(1U<<4)
#define TIM1_CCMR1_OC1M_H		(1U<<5) | (1U<<6)
#define TIM1_CCMR1_OC1PE		(1U<<3)
#define TIM1_EGR_UG				(1U<<0)
#define TIM1_BDTR_MOE			(1U<<15)
#define TIM1_CR1_CEN			(1U<<0)



/* The following function will set up PA8 pin to output mode, Alternate Function 1*/
void init_pwm_pin(void){
	// Enable clock to Port A
	RCC->AHB2ENR |= RCC_GPIOA_EN;

	// Set PA8 bits to OUTPUT mode - 10
	GPIOA->MODER |= GPIOA_PA8_MODE_H;
	GPIOA->MODER &= ~(GPIOA_PA8_MODE_H);

	// Set PA8 bits to AF mode - AF1: 0001
	GPIOA->AFR[1] |= GPIOA_PA8_AFR_H;
	GPIOA->AFR[1] &= ~(GPIOA_PA8_AFR_L);
}

/* The following function will set up PB8/PB9 pin to output mode*/
void init_output_direction_pins(void){

	RCC->AHB2ENR |= RCC_GPIOB_EN;
	GPIOB->MODER |= GPIOB_PB9_MODE_L;
	GPIOB->MODER |= GPIOB_PB8_MODE_L;
	GPIOB->MODER &= ~(GPIOB_PB9_MODE_H);
	GPIOB->MODER &= ~(GPIOB_PB8_MODE_H);
}

/* The following function will set up PWM on Timer1 Channel 1 through the PA8 pin */
void init_timer1_pwm(void){
	// Enable clock access to Timer1
	RCC->APB2ENR |= RCC_TIM1_EN;

	// Set the prescaler to 4MHz / 4 = 1MHz
	TIM1->PSC = 40;

	// Auto-Reload Register - Frequency
	TIM1->ARR = 100;

	// Timer1 Channel1 Capture Compare Value - Duty Cycle : 50%
	TIM1->CCR1 = 75;

	// Set channel 1 as output
	TIM1->CCMR1 &= ~(TIM1_CCMR1_CC1S);

	// Set polarity to active high
	TIM1->CCER &= ~(TIM1_CCER_CC1P);

	// Set timer1 to PWM Mode1
	TIM1->CCMR1 |= TIM1_CCMR1_OC1M_H;
	TIM1->CCMR1 &= ~(TIM1_CCMR1_OC1M_L);

	// Enable preload output compare
	TIM1->CCMR1 |= TIM1_CCMR1_OC1PE;

	// Enable output compare on channel1
	TIM1->CCER |= TIM1_CCER_CC1E;

	// Initialize the registers - event generation
	TIM1->EGR |= TIM1_EGR_UG;

	// Main output enable
	TIM1->BDTR |= TIM1_BDTR_MOE;

	// Enable timer
	TIM1->CR1 |= TIM1_CR1_CEN;

}

/* For this function, set one pin high and the other low - spin one direction*/
void set_pin_output_spin_1(void){
	GPIOB->ODR &= ~(1U<<9);
	GPIOB->ODR |= (1U<<8);

}

/* For this function, set both pins low - stop spin */
void set_pin_output_stop(void){
	GPIOB->ODR = 0;
}

/* For this function, set one pin high and the other low - spin one direction*/
void set_pin_output_spin_2(void){
	GPIOB->ODR &= ~(1U<<8);
	GPIOB->ODR |= (1U<<9);
}



int main(){

	// Initialize PB8 and PB9
	init_output_direction_pins();

	// Initialize PA8
	init_pwm_pin();

	// Initialize Timer1 Channel1 PWM
	init_timer1_pwm();



	// Loop forever
	while(1){
		systick_ms_delay(3000);

		// Spin one direction
		set_pin_output_spin_1();

		systick_ms_delay(2000);

		// Stop spin
		set_pin_output_stop();

		systick_ms_delay(1000);

		// Spin one direction
		set_pin_output_spin_2();

		systick_ms_delay(5000);

		// Stop spin
		set_pin_output_stop();
	}

	return 0;
}
