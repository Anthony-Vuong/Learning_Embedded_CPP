#include <stdio.h>
#include "Timer.h"
#include "UART.h"
#include "LED.h"

unsigned int timestamp{0};

int main(){

	// Initialize system components
	timer_output_compare_init();
	timer_input_capture_init();


	while(1){

		while(!(TIM3->SR & TIM3_SR_CCIF)){}
		timestamp = TIM3->CCR1;

	}

	return 0;
}
