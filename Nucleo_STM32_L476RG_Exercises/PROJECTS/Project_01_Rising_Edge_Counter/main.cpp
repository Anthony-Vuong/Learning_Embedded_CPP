#include <stdio.h>
#include "Timer.h"
#include "LED.h"
#include "UART.h"
#include "EXTI.h"


static volatile uint32_t count = 0;

int main(){

	timer_init();
	init_led();
	uart2_tx_rx_init();
	button_exti_init();


	while(1){

		// 1-min timer with TIM2
		while(!(TIM2->SR & TIM2_SR_UIF)){}

		// Reset the UI Flag
		TIM2->SR &= ~(TIM2_SR_UIF);

		// Send the amount of times the button was release through UART to RealTerm
		printf("Button was pressed: %lu ..........\n", count);
		led_toggle();
		count = 0;


	}

	return 0;
}


static void exti_callback(void){
	//printf("BTN Pressed..........\n\r");
	count++;
}

extern "C" {
void EXTI15_10_IRQHandler(void){
		if((EXTI->PR1 & LINE13)){
			/*Clear PR Flag*/
			// Do something - insert desired behavior
			EXTI->PR1 |= LINE13;
			exti_callback();
		}
	}
}

