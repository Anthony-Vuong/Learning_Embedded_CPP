/*
 * KEYPAD.cpp
 *
 *  Created on: Nov 22, 2023
 *      Author: antho
 */
#include "KEYPAD.h"
#include "UART.h"

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

char keypad_press(){

	// Create a temp char variable - may not be needed, could just return the desired character in each conditional block
	char temp{' '};

	// Begin by driving all ROW output pins to 0;
	GPIOB->ODR &= ~(ROW1 | ROW2 | ROW3 | ROW4);

	// In each conditional block check that the IDR register for column value are low - indicating button press
	// Search in that row if true, else move to next conditional block
	if((GPIOB->IDR & COL1) == 0){
		temp = search_col1();
	}
	else if((GPIOB->IDR & COL2) == 0){
		temp = search_col2();
	}
	else if((GPIOB->IDR & COL3) == 0){
		temp = search_col3();
	}
	else if((GPIOB->IDR & COL4) == 0){
		temp = search_col4();
	}
	else{
		return temp;
	}
	return temp;
}


// The next 4 functions will do the following
//		Drive the first row low - why? To check that row1 has been pressed when logical AND with GPIOB ODR
//		if true return the desired character
//		if false move to the next conditional block
//		else is reached return an empty character
//		return an empty character at the end to prevent warning of 'no return statement' for a char return type function :)
//
//		The above procedure is repeated when column 2/3/4 are pressed.

static char search_col1(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL1) == 0){
		return '1';
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL1) == 0){
		return '4';
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL1) == 0){
		return '7';
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL1) == 0){
		return '*';
	}

	return ' ';
}

static char search_col2(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL2) == 0){
		return '2';
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL2) == 0){
		return '5';
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL2) == 0){
		return '8';
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL2) == 0){
		return '0';
	}

	return ' ';
}

static char search_col3(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL3) == 0){
		return '3';
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL3) == 0){
		return '6';
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL3) == 0){
		return '9';
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL3) == 0){
		return '#';;
	}

	return ' ';
}

static char search_col4(){

	GPIOB->ODR &= ~(ROW1);
	GPIOB->ODR |= ROW2 | ROW3 | ROW4;

	if((GPIOB->IDR & COL4) == 0){
		return 'A';
	}

	GPIOB->ODR &= ~(ROW2);
	GPIOB->ODR |= ROW1 | ROW3 | ROW4;

	if((GPIOB->IDR & COL4) == 0){
		return 'B';
	}

	GPIOB->ODR &= ~(ROW3);
	GPIOB->ODR |= ROW2 | ROW1 | ROW4;

	if((GPIOB->IDR & COL4) == 0){
		return 'C';
	}

	GPIOB->ODR &= ~(ROW4);
	GPIOB->ODR |= ROW2 | ROW3 | ROW1;

	if((GPIOB->IDR & COL4) == 0){
		return 'D';

	}
	return ' ';

}


