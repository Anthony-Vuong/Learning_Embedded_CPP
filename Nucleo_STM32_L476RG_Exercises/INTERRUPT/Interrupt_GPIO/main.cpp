#include <stdio.h>
#include "stm32l476xx.h"
#include "Timer.h"
#include "UART.h"
#include "LED.h"
#include "EXTI.h"




int main(){

	// Initialize system components

	button_exti_init();
	init_button();
	init_led();
	//init_button();
	//uart2_tx_rx_init();

	while(1){

		//if(button_pressed()){
		//	led_toggle();
		//}

	}

	return 0;
}


static void exti_callback(void){
	//printf("BTN Pressed..........\n\r");
	led_toggle();
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
