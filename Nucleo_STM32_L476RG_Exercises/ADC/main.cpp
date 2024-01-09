#include "stm32l476xx.h"
#include "ADC.h"
#include "UART.h"


uint32_t sensor_value;

int main(){

	pc1_adc_init();
	uart2_tx_rx_init();

	while(1){
		start_conversion();

		sensor_value = adc_read();
		uart_write(sensor_value);
	}

	return 0;
}

