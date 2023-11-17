#include "systick.h"
#include "LED.h"



int main(){


	init_led();

	while(1){

		systick_delay(1000);   //1000ms = 1sec
		led_toggle();
	}



	return 0;
}
