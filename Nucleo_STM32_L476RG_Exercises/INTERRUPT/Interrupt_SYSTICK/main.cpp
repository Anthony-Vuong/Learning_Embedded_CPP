#include <stdio.h>
#include "systick.h"
#include "LED.h"
#include "UART.h"



int main(){

	init_led();
	systick_interrupt_init();
	uart2_tx_rx_init();

	while(1){}

	return 0;
}


static void systick_callback(){
	printf("Systick Callback function...........\n\r");
	led_toggle();
}


extern "C" {
	void SysTick_Handler(void){
		systick_callback();
	}
}
