#ifndef __MAIN_H
#define __MAIN_H

#include "iostm8l.h"

#define CONCAT(a, b) a##_##b
#define PORT(a, b) CONCAT(a, b)

#define PIN0 (1 << 0)
#define PIN1 (1 << 1)
#define PIN2 (1 << 2)
#define PIN3 (1 << 3)
#define PIN4 (1 << 4)
#define PIN5 (1 << 5)
#define PIN6 (1 << 6)
#define PIN7 (1 << 7)

#define LED_Pin PIN4
#define LED_GPIO_Port PB

#define TRIAC_1_Pin PIN7
#define TRIAC_1_GPIO_Port PB

#define TRIAC_0_Pin PIN0
#define TRIAC_0_GPIO_Port PC

#define TILT_SWITCH_Pin PIN1
#define TILT_SWITCH_GPIO_Port PC

#define GATE_DRIVER_0_Pin PIN6
#define GATE_DRIVER_0_GPIO_Port PB

#define GATE_DRIVER_1_Pin PIN5
#define GATE_DRIVER_1_GPIO_Port PB

// ADC_CR1
#define ADC1_CR1_OVERIE (1 << 7)
#define ADC1_CR1_AWDIE (1 << 4)
#define ADC1_CR1_EOCIE (1 << 3)
#define ADC1_CR1_CONT (1 << 2)
#define ADC1_CR1_START (1 << 1)
#define ADC1_CR1_ADON (1 << 0)

// ADC_CR2
#define ADC_CR2_PRESC (1 << 7)

// ADC_SR
#define ADC_SR_OVER (1 << 2)
#define ADC_SR_AWD (1 << 1)
#define ADC_SR_EOC (1 << 0)

// ADC_SQR1
#define ADC_SQR1_DMAOFF (1 << 7)
#define ADC_SQR1_CHSEL_STS (1 << 5)
#define ADC_SQR1_CHSEL_SVREFINT (1 << 4)

// ADC_TRIGR1
#define ADC_TRIGR1_TSON (1 << 5)
#define ADC_TRIGR1_VREFINTON (1 << 4)

#endif