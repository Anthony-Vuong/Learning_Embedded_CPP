/*
 * UART.h
 *
 *  Created on: Nov 14, 2023
 *      Author: antho
 */

#ifndef UART_H_
#define UART_H_

#include "stm32l476xx.h"
#include <stdint.h>

// Function prototypes
void uart2_tx_rx_init();
void uart_write(int ch);
char uart_read();



#endif /* UART_H_ */
