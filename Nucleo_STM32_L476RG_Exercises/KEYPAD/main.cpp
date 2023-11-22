#include <stdio.h>
#include "stm32l476xx.h"
#include "UART.h"
#include "LED.h"
#include "KEYPAD.h"
#include "systick.h"



int main(){

	// Initialize system components
	init_keypad_pins();
	uart2_tx_rx_init();
	init_led();

	// Button press variable
	char key_val{};

	while(1){

		// The next 4 lines are needed to mitigate debounce issue - button press may cause multiple events to occur
		// Wait 50ms after first press, scan for button press again, wait another 50ms - more than likely one key is read
		key_val = keypad_press();
		// 50ms Timer
		systick_delay(50);
		key_val = keypad_press();
		systick_delay(50);

		// Check that if the key scan does not read an empty character, then write key to uart
		if(key_val != ' ')
			uart_write(key_val);
	}

	return 0;
}



