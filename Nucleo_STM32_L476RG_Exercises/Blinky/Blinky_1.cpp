#include <stdint.h>

// Location of LED PIN: PA5
// Port: A
// Pin:  5

// To find the starting address of the board peripherals, look in data sheet Fig 17
#define PERIPH_BASE		(0x40000000UL)

// Why do peripherals need a bus - carries clock to the peripheral
// What kind of busses are there? Look on block diagram in the data sheet Fig 1
// APB - Advanced Peripheral Bus
// AHB - Advanced High-Performance Bus - faster than APB
// For GPIOA or Port A we are using AHB2
// After finding the bus for the GPIOA, use the memory map to find the starting
// address for AHB2
// In Table 19 find the starting address for GPIOA in AHB2 section

#define AHB2_PERIPH_OFFSET 		(0x08000000UL)
#define AHB2_PERIPH_BASE 		(PERIPH_BASE + AHB2_PERIPH_OFFSET)

// GPIOA address starts at AHB2 address
#define GPIOA_OFFSET 			(0x000000000UL)
#define GPIOA_BASE				(AHB2_PERIPH_BASE + GPIOA_OFFSET)

// Now we need a clock and be able to enable the clock
// RCC - Reset Clock Control - can be found in
// RCC as seen in memory map and block diagram is AHB1, but should work for AHB2 as well?
#define RCC_OFFSET				(0x00021000UL)
#define RCC_BASE				(PERIPH_BASE + RCC_OFFSET)

// To find the AHB2 enable offset use the reference manual and go to Section 6.14.7
#define AHB2ENR_OFFSET			(0x4CUL)
#define RCC_AHB2EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB2ENR_OFFSET))

#define MODE_R_OFFSET 			(0x00UL)
#define GPIO_MODE_R				(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define ODR_OFFSET				(0x14UL)
#define GPIOA_ODR				(*(volatile unsigned int *)(GPIOA_BASE + ODR_OFFSET))

// To enable the GPIOAEN we must set bit 0 to 1
#define GPIOAEN					(1U<<0)

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t TEMP[4];  // PLACE HOLDER FOR REGISTERS
	volatile uint32_t ODR;

}GPIO_TPYEDEF;

typedef struct{
	volatile uint32_t TEMP[19];  // PLACE HOLDER FOR REGISTERS
	volatile uint32_t AHB2ENR;

}RCC_TYPEDEF;

#define RCC						((RCC_TYPEDEF*) RCC_BASE)
#define GPIOA					((GPIO_TPYEDEF*) GPIOA_BASE)

int main(void){

	/*1. Enable clock access to GPIOA*/
	//RCC_AHB2EN_R |= GPIOAEN;  //w/out struct
	RCC->AHB2ENR |= GPIOAEN;

	/*1. Set PA5 to Output Pin*/
	//GPIO_MODE_R |= (1U<<10); //w/out struct
	//GPIO_MODE_R &= ~(1U<<11); //w/out struct
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	while(1){
		//GPIOA_ODR ^= LED_PIN;
		GPIOA->ODR  ^= LED_PIN;
		for(int i{0}; i<100000;i++);
	}

	return 0;
}



