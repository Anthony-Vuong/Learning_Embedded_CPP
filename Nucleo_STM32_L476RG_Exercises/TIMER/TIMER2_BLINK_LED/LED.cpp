/*
 * LED.cpp
 *
 *  Created on: Nov 14, 2023
 *      Author: antho
 */

#include "stm32l476xx.h"

// To enable the GPIOAEN we must set bit 0 to 1
#define GPIOAEN					(1U<<0)
#define PIN5					(1U<<5)
#define LED_PIN					PIN5

#define GPIOCEN					(1U<<2)
#define PIN13					(1U<<13)
#define PUSH_BUTTON				PIN13

void init_led(){

	/*1. Enable clock access to GPIOA*/
	RCC->AHB2ENR |= GPIOAEN;

	/*2. Set PA5 to Output Pin*/
	GPIOA->MODER |= (1U<<10);      // 1 01 is output mode
	GPIOA->MODER &= ~(1U<<11);     // 0

}

void init_button(){
	/*1. Enable clock access to GPIOC*/
	RCC->AHB2ENR |= GPIOCEN;

	/*2. Set PC13 to Input Pin*/
	GPIOC->MODER &= ~(1U<<26);     // 0 00 is input mode
	GPIOC->MODER &= ~(1U<<27);     // 0

}

void led_on(){
	GPIOA->BSRR  = LED_PIN;
}

void led_off(){
	GPIOA->BSRR  = (1U<<21);
}

void led_toggle(){
	GPIOA->ODR ^= LED_PIN;
}

bool button_pressed(){
	if(GPIOC->IDR & PUSH_BUTTON){
		return false;
	}
	return true;
}

