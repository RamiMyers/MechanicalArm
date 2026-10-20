#ifndef PWM_H
#define PWM_H

#include "stm32f446xx.h"

#define CLOCK_FREQUENCY 16000000UL
#define ARR_VALUE       999U

static inline void PWM_Init(unsigned freq) {
    // Enable RCC on GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // Enable RCC on TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Set AF2 (TIM3_CH1) on PA6
    GPIOA->MODER &= ~GPIO_MODER_MODE6_0;
    GPIOA->MODER |=  GPIO_MODER_MODE6_1;
    GPIOA->AFR[0] |= (2U << (4 * 6));

    // Set Auto-Reload Preload bits
    TIM3->CR1 |=  TIM_CR1_ARPE;
    // Clear Dir bit so timer acts as an up-counter
    TIM3->CR1 &= ~TIM_CR1_DIR;

    // Set Timer Values
    TIM3->PSC = (CLOCK_FREQUENCY / ((ARR_VALUE + 1) * freq)) - 1; // Calculates prescaler based on internal clock & ARR
    TIM3->ARR = ARR_VALUE;
    TIM3->CNT = 0;

    // Set PWM Mode 1
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M_0;
    TIM3->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
    // Set Output Compare 1 Preload Enable
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;

    // Set Duty Cycle to 0
    TIM3->CCR1 = 0;

    // Enable Capture/Compare Output
    TIM3->CCER |= TIM_CCER_CC1E;
    // Enable the Counter
    TIM3->CR1 |= TIM_CR1_CEN;
    // Generate update event to load buffered values
    TIM3->EGR |= TIM_EGR_UG;
}

static inline void PWM_Set(unsigned value) {
    TIM3->CCR1 = value;
}

#endif