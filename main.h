/* main.h */
#ifndef __MAIN_H
#define __MAIN_H

#include "iostm8l.h"

#define CONCAT(a, b) a##_##b
#define PORT(a, b) CONCAT(a, b)

// Pins
#define PIN0 (1 << 0)
#define PIN1 (1 << 1)
#define PIN2 (1 << 2)
#define PIN3 (1 << 3)
#define PIN4 (1 << 4)
#define PIN5 (1 << 5)
#define PIN6 (1 << 6)
#define PIN7 (1 << 7)

// Named pins and their ports
#define BUZZER_Pin PIN1
#define BUZZER_GPIO_Port PB

#define LED_GREEN_Pin PIN3
#define LED_GREEN_GPIO_Port PB

#define LED_RED_Pin PIN4
#define LED_RED_GPIO_Port PB

#define TRIAC_1_Pin PIN7
#define TRIAC_1_GPIO_Port PB

#define TRIAC_0_Pin PIN0
#define TRIAC_0_GPIO_Port PC

#define TILT_SWITCH_Pin PIN1
#define TILT_SWITCH_GPIO_Port PC

// ADC1_CR1
#define ADC1_CR1_OVERIE (1 << 7)
#define ADC1_CR1_AWDIE (1 << 4)
#define ADC1_CR1_EOCIE (1 << 3)
#define ADC1_CR1_CONT (1 << 2)
#define ADC1_CR1_START (1 << 1)
#define ADC1_CR1_ADON (1 << 0)

// ADC1_CR2
#define ADC1_CR2_PRESC (1 << 7)

// ADC1_SR
#define ADC1_SR_OVER (1 << 2)
#define ADC1_SR_AWD (1 << 1)
#define ADC1_SR_EOC (1 << 0)

// ADC1_SQR1
#define ADC1_SQR1_DMAOFF (1 << 7)
#define ADC1_SQR1_CHSEL_STS (1 << 5)
#define ADC1_SQR1_CHSEL_SVREFINT (1 << 4)

// ADC1_TRIGR1
#define ADC1_TRIGR1_TSON (1 << 5)
#define ADC1_TRIGR1_VREFINTON (1 << 4)

// TIM2_CR1
#define TIM2_CR1_CEN (1 << 0)

// TIM2_IER
#define TIM2_IER_UIE (1 << 0)

// TIM2_SR1
#define TIM2_SR1_UIF (1 << 0)

// TIM
#define TIM_PRSC_2 1
#define TIM_PRSC_4 2
#define TIM_PRSC_8 3
#define TIM_PRSC_16 4

// ADC
#define CYCLES_192 6

#endif