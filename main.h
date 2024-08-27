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

#define ADC_CSR_EOC (1 << 7)
#define ADC_CSR_AWD (1 << 6)
#define ADC_CSR_EOCIE (1 << 5)
#define ADC_CSR_AWDIE (1 << 4)

#define ADC_CR1_CONT (1 << 1)
#define ADC_CR1_ADON (1 << 0)

#define ADC_CR2_EXTTRIG (1 << 6)
#define ADC_CR2_EXTSEL (1 << 4)
#define ADC_CR2_ALIGN (1 << 3)
#define ADC_CR2_SCAN (1 << 1)

#endif