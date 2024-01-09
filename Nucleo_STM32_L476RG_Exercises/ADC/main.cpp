#include <cstdio>
#include "stm32l476xx.h"
#include "ADC.h"
#include "UART.h"

static void adc_callback();
int sensor_value;

int main(){

	pc1_adc_init();
	uart2_tx_rx_init();
	start_conversion();

	while(1){

	}

	return 0;
}

static void adc_callback(){
	sensor_value = ADC1->DR;
	printf("SV: %d\n\r", sensor_value);

}

extern "C" {
void ADC1_2_IRQHandler(){
	if(ADC1->ISR & ADC_EOC){
		ADC1->ISR &= ~(ADC_EOC);
		adc_callback();
	}

}
}
