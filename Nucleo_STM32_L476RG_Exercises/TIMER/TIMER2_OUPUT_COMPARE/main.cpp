#include <stdio.h>
#include "Timer.h"
#include "UART.h"
#include "LED.h"



int main(){

	// Initialize system components
	timer_init();
	init_led();
	uart2_tx_rx_init();

	timer_output_init();

	while(1){}

	return 0;
}
