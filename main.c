/* main.c */
#include "main.h"

#include <stdint.h>

// Function prototypes
void systemClockInit(void);
void GPIOInit(void);
void ADCInit(void);
void simpleDelay(uint32_t count);
void delayms(uint16_t ms);

// Value from ADC 0-4095 for 12-bit res.(default)
uint16_t adc_val;

void main(void) {
  systemClockInit();
  GPIOInit();
  ADCInit();

  // Infinite loop
  for (;;) {
    // Start ADC
    ADC1_CR1 |= ADC1_CR1_START;

    // Wait for end of conversion
    while (!(ADC1_SR & ADC1_SR_EOC))
      ;

    // Read result
    adc_val = (ADC1_DRH << 8) | ADC1_DRL; // Depends on alignment(?)

    // Check if tilt switch is on
    if (PORT(TILT_SWITCH_GPIO_Port, IDR) & TILT_SWITCH_Pin) {
      PORT(LED_GPIO_Port, ODR) |= LED_Pin; // Set LED high
    } else {
      PORT(LED_GPIO_Port, ODR) &= ~LED_Pin; // Set LED low
    }
    simpleDelay(1000UL);
  }
}

void systemClockInit(void) {
  // No division (16 MHz)
  CLK_DIVR = 0x00;
}

/*
 * Initialization function for the GPIO.
 */
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

/*
 * Initialization function for the ADC.
 */
void ADCInit(void) {
  // Select channel 22
  ADC1_CR3 |= 22;

  // Sampling time (192 cycles)
  ADC1_CR2 |= 6;

  // Turn AD on
  ADC1_CR1 |= ADC1_CR1_ADON;

  // Delay needed (longer than wake-up, shorter than idle)
  simpleDelay(1000UL);
}

/*
 * Very crude delay function.
 */
void simpleDelay(uint32_t count) {
  while (count--) {
    __asm("nop");
  }
}

/*
 * Use TIM2 to generate a delay.
 */
void delayms(uint16_t ms) {
  // Assuming a clock of 16 MHz, and a delay of 1 ms

  // (Clock / Prescaler) * ms
  uint16_t timer_value = (16000 / 16) * ms;

  // Prescale
  TIM2_PSCR |= 4;

  // Set Auto-Reload Register value
  TIM2_ARRH = (timer_value >> 8);
  TIM2_ARRL = (timer_value & 0xFF);

  // Start Timer
  TIM2_CR1 |= TIM2_CR1_CEN;

  // Wait for update flag
  while (!(TIM2_SR1 & TIM2_SR1_UIF))
    ;
  TIM2_SR1 &= ~TIM2_SR1_UIF; // Clear update flag
  TIM2_CR1 &= ~TIM2_CR1_CEN; // Stop Timer
}