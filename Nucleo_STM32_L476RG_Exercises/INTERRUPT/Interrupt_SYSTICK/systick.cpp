#include "stm32l476xx.h"

#define SYSTICK_LOAD_VAL	4000
#define CTRL_EN			(1U<<0)
#define CTRL_CLCKSR		(1U<<2)
#define CTRL_INT_ENABLE	(1U<<1)
#define CTRL_FLAG		(1U<<16)

#define ONE_SEC_LOAD	4000000

// A function that calculates a delay time using n as the #of cycles executed using 4MHz sys_clk
void systick_delay(int delay){

	/*Load systick value*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*Clear systick current value reg*/
	SysTick->VAL = 0;

	/*Enable systick and internal clk src*/
	SysTick->CTRL = CTRL_CLCKSR | CTRL_EN;

	for(int i{0}; i < delay; i++){
		/*Wait until count flag is set*/
		while((SysTick->CTRL & CTRL_FLAG) == 0){}
	}

	SysTick->CTRL = 0;

}

void systick_interrupt_init(){

	/*Setting Load register with 1sec value*/
	SysTick->LOAD = ONE_SEC_LOAD;

	/*Clear systick current value reg*/
	SysTick->VAL = 0;

	/*Enable systick, interrupt, and internal clk src*/
	SysTick->CTRL = CTRL_CLCKSR | CTRL_EN | CTRL_INT_ENABLE;



}

