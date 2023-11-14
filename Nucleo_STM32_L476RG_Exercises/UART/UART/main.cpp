#include <stdio.h>
#include "UART.h"
#include "LED.h"

int main(void){

	char key;
	init_led();

	// Initialize USART2 - set pins, set baudrate, enable uart
	uart2_tx_rx_init();

	while(1){
		key = uart_read();

		if(key == 'o'){
			led_on();
		}
		else{
			led_off();
		}
	}

	return 0;
}



