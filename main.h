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
#define BUZZER_Pin PIN2
#define BUZZER_GPIO_Port PB

#define LED_GREEN_Pin PIN4
#define LED_GREEN_GPIO_Port PB

#define LED_RED_Pin PIN3
#define LED_RED_GPIO_Port PB

#define TRIAC_1_Pin PIN7
#define TRIAC_1_GPIO_Port PB

#define TRIAC_0_Pin PIN0
#define TRIAC_0_GPIO_Port PC

#define TILT_SWITCH_Pin PIN6
#define TILT_SWITCH_GPIO_Port PB

// ADC1_CR1
#define ADC1_CR1_OVERIE (1 << 7) // Overrun interrupt enable
#define ADC1_CR1_AWDIE (1 << 4)  // Analog watchdog interrupt enable
#define ADC1_CR1_EOCIE (1 << 3)  // Interrupt enable for EOC
#define ADC1_CR1_CONT (1 << 2)   // Continuous conversion
#define ADC1_CR1_START (1 << 1)  // Conversion start
#define ADC1_CR1_ADON (1 << 0)   // A/D converter ON / OFF

// ADC1_CR2
#define ADC1_CR2_PRESC (1 << 7) // Clock prescaler

// ADC1_SR
#define ADC1_SR_OVER (1 << 2) // Overrun flag
#define ADC1_SR_AWD (1 << 1)  // Analog watchdog flag
#define ADC1_SR_EOC (1 << 0)  // End of conversion

// ADC1_SQR1
#define ADC1_SQR1_DMAOFF (1 << 7)    // DMA disable for a single conversion
#define ADC1_SQR1_CHSEL_STS (1 << 5) // Selection of channel TS for scan
#define ADC1_SQR1_CHSEL_SVREFINT                                               \
  (1 << 4) // Selection of channel Vrefint for scan

// ADC1_TRIGR1
#define ADC1_TRIGR1_TSON                                                       \
  (1 << 5) // Temperature sensor internal reference voltage enable
#define ADC1_TRIGR1_VREFINTON (1 << 4) // Internal reference voltage enable

// ADC sampling times
#define CYCLES_4 0
#define CYCLES_9 1
#define CYCLES_16 2
#define CYCLES_24 3
#define CYCLES_48 4
#define CYCLES_96 5
#define CYCLES_192 6
#define CYCLES_384 7

// TIM2_CR1
#define TIM2_CR1_CEN (1 << 0) // Counter enable

// TIM2_IER
#define TIM2_IER_UIE (1 << 0) // Update interrupt enable

// TIM2_SR1
#define TIM2_SR1_UIF (1 << 0) // Update interrupt flag

// TIM prescaler divisions
#define TIM_PRSC_2 1
#define TIM_PRSC_4 2
#define TIM_PRSC_8 3
#define TIM_PRSC_16 4

#endif