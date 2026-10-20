#ifndef UART_H
#define UART_h

#include <stdint.h>
#include "stm32f446xx.h"

#define CLOCK_FREQUENCY 16000000UL
#define BAUD_RATE       115200UL

int __io_putchar(int ch) {
    UART_Write(ch);
    return ch;
}

void UART_Init(void) {
    // Enable GPIOA Clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA2 Alternate Function: USART2 TX
    GPIOA->MODER &= ~GPIO_MODER_MODE2_0;
    GPIOA->MODER |=  GPIO_MODER_MODE2_1;

    GPIOA->AFR[0] &= ~(0xFU << (4 * 2));
    GPIOA->AFR[0] |=  (7U << (4 * 2));

    // Enable USART2 Clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Set Baud Rate
    USART2->BRR = (CLOCK_FREQUENCY + (BAUD_RATE / 2)) / BAUD_RATE;

    // Enable TX
    USART2->CR1 |= USART_CR1_TE;

    // Enable UART
    USART2->CR1 |= USART_CR1_UE;
}

void UART_Write(int ch) {
    // Wait Until Transmitter is Empty
    while (!(USART2->SR & USART_SR_TXE));

    // Write to Data Register
    USART2->DR = (ch & 0xFF);
}

#endif