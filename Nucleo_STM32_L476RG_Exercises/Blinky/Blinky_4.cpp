/*BSRR - BIT SET RESET REGISTER*/

#include "stm32l476xx.h"

// To enable the GPIOAEN we must set bit 0 to 1
#define GPIOAEN					(1U<<0)
#define PIN5					(1U<<5)
#define LED_PIN					PIN5

int main(void){

	/*1. Enable clock access to GPIOA*/
	RCC->AHB2ENR |= GPIOAEN;


	/*1. Set PA5 to Output Pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	while(1){
		GPIOA->BSRR  = LED_PIN;
		for(int i{0}; i<100000;i++);

		GPIOA->BSRR  = (1U<<21);
		for(int i{0}; i<100000;i++);
	}

	return 0;
}



