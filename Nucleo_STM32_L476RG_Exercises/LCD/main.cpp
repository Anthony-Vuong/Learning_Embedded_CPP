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


void init_cmd_gpio_pins(){

	// Enable clock access for GPIOC
	RCC->AHB2ENR |= GPIOC_EN;

	// Setup data pins as output PC 0/1/2/3
	GPIOC->MODER |= GPIO_DATA_OUT_L;
	GPIOC->MODER &= ~(GPIO_DATA_OUT_H);

	// Setup STATE pins as output PA 13/14/15
	GPIOC->MODER &= ~(STATE_MODE_H);
	GPIOC->MODER |= (STATE_MODE_L);


}

void send_command(uint8_t cmd){

	// Take top 4 bits and write to the DR data register
	GPIOC->ODR |= D4_OUT & ((cmd>>4) & 1);
	GPIOC->ODR |= D5_OUT & (1<<((cmd>>5) & 1));
	GPIOC->ODR |= D6_OUT & (2<<((cmd>>6) & 1));
	GPIOC->ODR |= D7_OUT & (3<<((cmd>>7) & 1));

	// Enable chip signal R or W
	GPIOC->ODR |= EN_PIN;
	systick_delay(5);
	GPIOC->ODR &= ~(EN_PIN);
	systick_delay(5);

	GPIOC->ODR = 0;

	// Take bottom 4 bits and write to the DR data register
	GPIOC->ODR |= D4_OUT & (cmd & 1);
	GPIOC->ODR |= D5_OUT & (1<<((cmd>>1) & 1));
	GPIOC->ODR |= D6_OUT & (2<<((cmd>>2) & 1));
	GPIOC->ODR |= D7_OUT & (3<<((cmd>>3) & 1));

	// Enable chip signal R or W
	GPIOC->ODR |= EN_PIN;
	systick_delay(5);
	GPIOC->ODR &= ~(EN_PIN);
	systick_delay(5);

}

void init_lcd(){
	// Instructions say 15ms but 30ms to make sure
	systick_delay(30);
	send_command(0x30);
	systick_delay(10);
	send_command(0x30);
	systick_delay(10);
	send_command(0x30);
	systick_delay(10);

	send_command(0x20);		// Function set - set interface 4 bits long

	send_command(0x28);		// Function set -
	send_command(0x08);
	send_command(0x01);
	send_command(0x06);
	send_command(0x0f);
}


int main(){

	init_cmd_gpio_pins();

	init_lcd();

	while(1){}

	return 0;
}
