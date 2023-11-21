/*
 * UART.cpp
 *
 *  Created on: Nov 14, 2023
 *      Author: antho
 */




/*BSRR - BIT SET RESET REGISTER*/
#include <stdio.h>
#include "UART.h"



// To enable the GPIOAEN we must set bit 0 to 1
#define GPIOAEN					(1U<<0)
#define USART2EN  				(1U<<17)


#define SYS_FREQ				4000000   // 4MHz
#define APB1CLK					SYS_FREQ
#define UART_BAUDRATE			115200

#define CR1TE					(1U<<3)
#define CR1RE					(1U<<2)
#define CR1UE  					(1U<<0)
#define SR_TXE					(1U<<7)
#define SR_RXNE					(1U<<5)

int __io_putchar(int ch){

	uart_write(ch);
	return ch;
}

// used for support of printf out of SWD when using C++
//https://electronics.stackexchange.com/questions/573732/stm32cube-printf-to-swd-stops-working-when-c/573959#573959?newreg=1d127d2058164b70a800ebb8109a6d64
extern "C" {
int _write(int file, char *ptr, int len)
    {
        int i = 0;
        for (i = 0; i<len-1; i++)
        	uart_write((*ptr++));
        return len;
    }
}

// Helper function - for Baudrate value
static uint16_t calculate_UART_div(uint32_t PeriphClk, uint32_t baudrate){
	return ((PeriphClk + (baudrate/2U))/baudrate);
}

static void set_uart_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t baudrate){
	USARTx->BRR = calculate_UART_div(PeriphClk, baudrate);
}



void uart2_tx_rx_init(){
	/*1. Enable clock to access to GPIOA*/
	RCC->AHB2ENR |= GPIOAEN;

	/*2. Set PA2 to Alternate Function*/
	GPIOA->MODER &= ~(1U<<4);					//0 10 is alternate function
	GPIOA->MODER |= (1U<<5);					//1

	/*3. Set PA3 to Alternate Function type to UART_TX(AF7)*/
	GPIOA->MODER &= ~(1U<<6);					//0 10 is alternate function
	GPIOA->MODER |= (1U<<7);					//1

	/*4. Set PA2 to Alternate Function type to UART_TX(AF7)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/*5. Set PA3 to Alternate Function type to UART_RX(AF7)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	/*6. Enable Clock Access to UART2*/
	RCC->APB1ENR1 |= USART2EN;

	/*7. Configure Baudrate*/
	set_uart_baudrate(USART2, APB1CLK, UART_BAUDRATE);

	/*8. Configure the transfer function*/
	/*9. Configure the receive function*/
	USART2->CR1 = CR1TE | CR1RE;

	/*10. Enable UART module*/
	USART2->CR1 |= CR1UE;
}

char uart_read(){
	/*1. Make sure recevie register is not empty*/
	while(!(USART2->ISR & SR_RXNE)){}
	return  USART2->RDR;
}

void uart_write(int ch){
	/*1. Make sure transmit register is empty*/
	/*2. Write to transmit data*/
	while(!(USART2->ISR & SR_TXE)){}
	USART2->TDR = (ch & 0xFF);
}
