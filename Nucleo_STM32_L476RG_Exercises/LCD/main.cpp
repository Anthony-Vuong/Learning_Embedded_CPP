#include "stm32l476xx.h"
#include "systick.h"
#include <stdint.h>

#define GPIOC_EN			(1U<<2)
#define GPIOA_EN			(1U<<0)
#define GPIO_DATA_OUT_L		(1U<<6) | (1U<<4) | (1U<<2) | (1U<<0)
#define GPIO_DATA_OUT_H		(1U<<7) | (1U<<5) | (1U<<3) | (1U<<1)

// The next 2 definitions are to setup the STATE pins as output
#define	STATE_MODE_L		(1U<<10) | (1U<<12) | (1U<<14)
#define	STATE_MODE_H		(1U<<11) | (1U<<13) | (1U<<15)


// The next 3 definitions are for STATE pins Output Data Register
#define	RS_PIN				(1U<<5)
#define	RW_PIN				(1U<<6)
#define	EN_PIN				(1U<<7)

// The next 4 definitions are for DATA pins Output Data Register
#define D7_OUT				(1U<<3)
#define D6_OUT				(1U<<2)
#define D5_OUT				(1U<<1)
#define D4_OUT				(1U<<0)


void init_lcd_gpio_pins(){

	// Enable clock access for GPIOC
	RCC->AHB2ENR |= GPIOC_EN;

	// Setup data pins as output PC 0/1/2/3
	GPIOC->MODER |= GPIO_DATA_OUT_L;
	GPIOC->MODER &= ~(GPIO_DATA_OUT_H);

	// Setup STATE pins as output PC 5/6/7
	GPIOC->MODER &= ~(STATE_MODE_H);
	GPIOC->MODER |= (STATE_MODE_L);


}

void send_command(uint8_t cmd){

	// Take top 4 bits and write to the command register
	GPIOC->ODR = ((cmd >> 4) & 0x0F);

	GPIOC->ODR &= ~(RS_PIN | RW_PIN);
	// Enable chip signal R or W
	GPIOC->ODR |= EN_PIN;
	systick_ms_delay(1);
	GPIOC->ODR &= ~(EN_PIN);

	systick_ms_delay(10);

	// Take bottom 4 bits and write to the command register
	GPIOC->ODR = cmd & 0x0F;

	// Enable chip signal R or W
	GPIOC->ODR |= EN_PIN;
	systick_ms_delay(1);
	GPIOC->ODR &= ~(EN_PIN);

	GPIOC->ODR = 0;

}

void init_lcd(){

	systick_ms_delay(100);
	send_command(0x30);
	systick_ms_delay(5);
	send_command(0x30);
	systick_us_delay(100);
	send_command(0x30);
	systick_us_delay(100);
	send_command(0x20);
	systick_us_delay(100);


	send_command(0x28);
	systick_us_delay(55);
	send_command(0x0E);
	systick_us_delay(55);
	send_command(0x01);
	systick_ms_delay(5);
	send_command(0x06);
	systick_us_delay(55);
	send_command(0x0F);
	systick_ms_delay(1000);


	send_command(0xC0);
}


int main(){

	init_lcd_gpio_pins();

	init_lcd();

	while(1){}

	return 0;
}
