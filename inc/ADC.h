#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include "stm32f4xx.h"

void ADC_Init() {
    // Enable Clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA0 to Analog Mode
    GPIOA->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1);
    
    // Enable Clock for ADC1
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Select Channel 0 of ADC1
    ADC1->SQR3 &= ~(ADC_SQR3_SQ1);

    // Set Conversion Sequence Length
    ADC1->SQR1 = (0U << ADC_SQR1_L);

    // Enable ADC
    ADC1->CR2 |= ADC_CR2_ADON;

    // Enable Continuous Conversion
    ADC1->CR2 |= ADC_CR2_CONT;

    // Start ADC Conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t ADC_Read(void) {
    // Wait for EOC Flag
    while (!(ADC1->SR & ADC_SR_EOC));

    // Read Converted Value
    return ADC1->DR;
}

#endif