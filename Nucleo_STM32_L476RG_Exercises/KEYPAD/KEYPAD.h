/*
 * KEYPAD.h
 *
 *  Created on: Nov 22, 2023
 *      Author: antho
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

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

// ROW values for writing to appropriate GPIOB Output Data Register(ODR) values
#define ROW1				(1U<<5)			//PB5
#define ROW2				(1U<<6)			//PB6
#define ROW3				(1U<<10)		//PB10
#define ROW4				(1U<<14)		//PB14

// COLUMN values for reading from appropriate GPIOB Input Data Register(IDR) values
#define COL1				(1U<<1)			//PB1
#define COL2				(1U<<2)			//PB2
#define COL3				(1U<<3)			//PB3
#define COL4				(1U<<4)			//PB4

// Function prototypes - each search_colx() function reads the character of the key pressed or empty character key is not pressed
static char search_col1();
static char search_col2();
static char search_col3();
static char search_col4();

// Initialize COLUMN input pins(PB 1/2/3/4) and ROW output pins (PB 5/6/10/14)
// Ensure COLUMN input pins are PULL UP type(PUPDR)
void init_keypad_pins();

// Function that detects key press - returns a character if button press is detected
char keypad_press();



#endif /* KEYPAD_H_ */
