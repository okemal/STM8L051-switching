#include "main.h"

#include <stdint.h>

void systemClockInit(void);
void GPIOInit(void);
void ADCInit(void);
void simpleDelay(uint32_t count);

void main(void) {
  systemClockInit();
  GPIOInit();
  ADCInit();

  for (;;) {
    if (PORT(TILT_SWITCH_GPIO_Port, IDR) & TILT_SWITCH_Pin) {
      PORT(LED_GPIO_Port, ODR) |= LED_Pin; // Set LED high
    } else {
      PORT(LED_GPIO_Port, ODR) &= ~LED_Pin; // Set LED low
    }
    simpleDelay(1000UL);
  }
}

void systemClockInit(void) { CLK_DIVR = 0x00; }

void GPIOInit(void) {
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

  // Initialize outputs to low
  PORT(LED_GPIO_Port, ODR) &= ~LED_Pin;
  PORT(TRIAC_0_GPIO_Port, ODR) &= ~TRIAC_0_Pin;
  PORT(TRIAC_1_GPIO_Port, ODR) &= ~TRIAC_1_Pin;
}

void ADCInit(void) {}

void simpleDelay(uint32_t count) {
  while (count--) {
    __asm("nop");
  }
}