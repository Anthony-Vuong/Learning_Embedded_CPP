/*BSRR - BIT SET RESET REGISTER*/

#include "stm32l476xx.h"

// To enable the GPIOAEN we must set bit 0 to 1
#define GPIOAEN					(1U<<0)
#define PIN5					(1U<<5)
#define LED_PIN					PIN5

#define GPIOCEN					(1U<<2)
#define PIN13					(1U<<13)
#define PUSH_BUTTON				PIN13

int main(void){

	/*1. Enable clock access to GPIOA*/
	RCC->AHB2ENR |= GPIOAEN;

	/*2. Enable clock access to GPIOC*/
	RCC->AHB2ENR |= GPIOCEN;

	/*3. Set PA5 to Output Pin*/
	GPIOA->MODER |= (1U<<10);      // 1 01 is output mode
	GPIOA->MODER &= ~(1U<<11);     // 0

	/*4. Set PC13 to Input Pin*/
	GPIOC->MODER &= ~(1U<<26);     // 0 00 is input mode
	GPIOC->MODER &= ~(1U<<27);     // 0

	// Ensure LED is off prior to running while loop
	GPIOA->BSRR  = (1U<<21);

	while(1){
		// if IDR reads 1 button is not pressed - leave LED off
		if(GPIOC->IDR & PUSH_BUTTON){
			GPIOA->BSRR  = (1U<<21);
			for(int i{0}; i<100000;i++);
		}
		else{
			// if IDR reads 0 button is pressed - turn LED on
			GPIOA->BSRR  = LED_PIN;
			for(int i{0}; i<100000;i++);
		}
	}

	return 0;
}



