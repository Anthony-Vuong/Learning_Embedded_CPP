#include <cstdio>
#include "stm32l476xx.h"
#include "ADC.h"
#include "UART.h"


int sensor_value;

int main(){

	pc1_adc_init();
	uart2_tx_rx_init();
	start_conversion();

	while(1){
		sensor_value = adc_read();
		printf("SV: %d\n\r", sensor_value);
	}

	return 0;
}

