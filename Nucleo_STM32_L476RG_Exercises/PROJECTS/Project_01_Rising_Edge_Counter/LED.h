/*
 * LED.h
 *
 *  Created on: Nov 14, 2023
 *      Author: antho
 */

#ifndef LED_H_
#define LED_H_

void init_led();
void init_button();
bool button_pressed();
void led_on();
void led_off();
void led_toggle();

// To enable the GPIOAEN we must set bit 0 to 1
#define GPIOAEN					(1U<<0)
#define PIN5					(1U<<5)
#define LED_PIN					PIN5

#define GPIOCEN					(1U<<2)
#define PIN13					(1U<<13)
#define PUSH_BUTTON				PIN13


#endif /* LED_H_ */
