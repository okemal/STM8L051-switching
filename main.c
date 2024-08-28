#include "main.h"

#include <stdint.h>

static void GPIO_Init(void);
static void ADC_Init(void);
static void simple_Delay(uint32_t count);

void main(void) {
  CLK_DIVR = 0x00;
  GPIO_Init();
  ADC_Init();

  for (;;) {
    if (PORT(TILT_SWITCH_GPIO_Port, IDR) & TILT_SWITCH_Pin) {
      PORT(LED_GPIO_Port, ODR) |= LED_Pin; // Set LED high
    } else {
      PORT(LED_GPIO_Port, ODR) &= ~LED_Pin; // Set LED low
    }
    simple_Delay(1000UL);
  }
}

static void GPIO_Init(void) {
  // Set TILT_SWITCH as input
  PORT(TILT_SWITCH_GPIO_Port, DDR) &= ~TILT_SWITCH_Pin;
  // Enable pull-up resistor
  PORT(TILT_SWITCH_GPIO_Port, CR1) |= TILT_SWITCH_Pin;

  // Set LED as output
  PORT(LED_GPIO_Port, DDR) |= LED_Pin;
  // Set LED as "push-pull"
  PORT(LED_GPIO_Port, CR1) |= LED_Pin;

  // Set TRIAC_0 as output
  PORT(TRIAC_0_GPIO_Port, DDR) |= TRIAC_0_Pin;
  // Set TRIAC_0 as "push-pull"
  PORT(TRIAC_0_GPIO_Port, CR1) |= TRIAC_0_Pin;

  // Set TRIAC_1 as output
  PORT(TRIAC_1_GPIO_Port, DDR) |= TRIAC_1_Pin;
  // Set TRIAC_1 as "push-pull"
  PORT(TRIAC_1_GPIO_Port, CR1) |= TRIAC_1_Pin;

  // Set GATE_DRIVER_0 as output
  PORT(GATE_DRIVER_0_GPIO_Port, DDR) |= GATE_DRIVER_0_Pin;
  // Set GATE_DRIVER_0 as "push-pull"
  PORT(GATE_DRIVER_0_GPIO_Port, CR1) |= GATE_DRIVER_0_Pin;

  // Set GATE_DRIVER_1 as output
  PORT(GATE_DRIVER_1_GPIO_Port, DDR) |= GATE_DRIVER_1_Pin;
  // Set GATE_DRIVER_1 as "push-pull"
  PORT(GATE_DRIVER_1_GPIO_Port, CR1) |= GATE_DRIVER_1_Pin;

  // Initialize outputs to low
  PORT(LED_GPIO_Port, ODR) &= ~LED_Pin;
  PORT(TRIAC_0_GPIO_Port, ODR) &= ~TRIAC_0_Pin;
  PORT(TRIAC_1_GPIO_Port, ODR) &= ~TRIAC_1_Pin;
  PORT(GATE_DRIVER_0_GPIO_Port, ODR) &= ~GATE_DRIVER_0_Pin;
  PORT(GATE_DRIVER_1_GPIO_Port, ODR) &= ~GATE_DRIVER_1_Pin;
}

static void ADC_Init(void) {}

static void simple_Delay(uint32_t count) {
  while (count--) {
    __asm("nop");
  }
}