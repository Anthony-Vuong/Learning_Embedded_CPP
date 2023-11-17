#include <stdio.h>
#include "stm32l476xx.h"
#include "Timer.h"
#include "UART.h"
#include "LED.h"
#include "EXTI.h"

static void tim2_callback(void);

int main(){

	/*1. Enable clock access to GPIOA*/
	RCC->AHB2ENR |= GPIOAEN;

	/*2. Set PA5 to Output Pin*/
	GPIOA->MODER |= (1U<<10);      // 1 01 is output mode
	GPIOA->MODER &= ~(1U<<11);     // 0

	timer_interrupt_init();

	while(1){}

	return 0;
}


static void tim2_callback(void){
	//printf("BTN Pressed..........\n\r");
	led_toggle();
}


extern "C" {
void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM2_SR_UIF;

	tim2_callback();
}
}
