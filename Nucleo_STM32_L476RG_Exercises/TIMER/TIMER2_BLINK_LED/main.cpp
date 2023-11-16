#include <stdio.h>
#include "Timer.h"
#include "UART.h"
#include "LED.h"



int main(){

	timer_init();
	init_led();
	uart2_tx_rx_init();

	unsigned int sec{0};

	while(1){


		while(!(TIM2->SR & TIM2_SR_UIF)){}

		TIM2->SR &= ~(TIM2_SR_UIF);

		printf("Second %d has passed. \n\r", sec);
		led_toggle();
		sec++;


	}



	return 0;
}
