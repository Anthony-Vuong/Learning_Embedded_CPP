#include <stdio.h>
#include "stm32l476xx.h"
#include "UART.h"
#include "LED.h"


// Columns are input pins
// Rows are output pins

#define GPIOB_EN			(1U<<1)
// 1, 2, 3, 4
#define GPIOB_IN_MODE		(1U<<9) | (1U<<8) | (1U<<7) | (1U<<6) | (1U<<5) | (1U<<4) | (1U<<3) | (1U<<2)
// 5, 6, 10, 14
#define GPIOB_OUT_MODE_L	(1U<<28) | (1U<<20) | (1U<<12) | (1U<<10)
#define GPIOB_OUT_MODE_H	(1U<<29) | (1U<<21) | (1U<<13) | (1U<<11)

#define GPIOB_TYPE_PU_L		(1U<<8) | (1U<<6) | (1U<<4) | (1U<<2)
#define GPIOB_TYPE_PU_H		(1U<<9) | (1U<<7) | (1U<<5) | (1U<<3)

#define ROW1				(1U<<5)			//PB5
#define ROW2				(1U<<6)			//PB6
#define ROW3				(1U<<10)		//PB10
#define ROW4				(1U<<14)		//PB14

#define COL1				(1U<<1)			//PB1
#define COL2				(1U<<2)			//PB2
#define COL3				(1U<<3)			//PB3
#define COL4				(1U<<4)			//PB4

static void search_col1();
static void search_col2();
static void search_col3();
static void search_col4();
void init_keypad_pins();
void keypad_press();

void init_keypad_pins(){
	// Enable the clocks for GPIOB
	RCC->AHB2ENR |= GPIOB_EN;

	// COLUMN Input pins - PB 1/2/3/4
	GPIOB->MODER &= ~(GPIOB_IN_MODE);

	// Input pins - enable pull-up resistors
	GPIOB->PUPDR |= GPIOB_TYPE_PU_L;
	GPIOB->PUPDR &= ~(GPIOB_TYPE_PU_H);

	// ROW Output pins - PB 5/6/10/14
	GPIOB->MODER |= GPIOB_OUT_MODE_L;
	GPIOB->MODER &= ~(GPIOB_OUT_MODE_H);

}

void keypad_press(){

	// Begin by driving all ROW output pins to 0;
	GPIOB->ODR &= ~(ROW1 | ROW2 | ROW3 | ROW4);

	if((GPIOB->IDR & COL1) == 0){
		search_col1();
	}
	else if((GPIOB->IDR & COL2) == 0){
		search_col2();
	}
	else if((GPIOB->IDR & COL3) == 0){
		search_col3();
	}
	else if((GPIOB->IDR & COL4) == 0){
		search_col4();
	}
	else{

	}

}

static void search_col1(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL1) == 0){
		uart_write('1');
		return;
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL1) == 0){
		uart_write('4');
		return;
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL1) == 0){
		uart_write('7');
		return;
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL1) == 0){
		uart_write('*');
		return;
	}


}

static void search_col2(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL2) == 0){
		uart_write('2');
		return;
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL2) == 0){
		uart_write('5');
		return;
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL2) == 0){
		uart_write('8');
		return;
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL2) == 0){
		uart_write('0');
		return;
	}


}

static void search_col3(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL3) == 0){
		uart_write('3');
		return;
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL3) == 0){
		uart_write('6');
		return;
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL3) == 0){
		uart_write('9');
		return;
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL3) == 0){
		uart_write('#');
		return;
	}


}

static void search_col4(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL4) == 0){
		uart_write('A');
		return;
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL4) == 0){
		uart_write('B');
		return;
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL4) == 0){
		uart_write('C');
		return;
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL4) == 0){
		uart_write('D');
		return;
	}


}

int main(){
	init_keypad_pins();
	uart2_tx_rx_init();
	init_led();

	while(1){
		keypad_press();
	}

	return 0;
}



