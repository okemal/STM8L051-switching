/* main.c */
/* Tried to explain most things, consult the datasheet and the reference manual
 * provided under the /info folder. For definitions check main.h file.
 */
#include "main.h"

#include <stdint.h>

// Function prototypes
void systemClockInit(void);
void GPIOInit(void);
void ADCInit(void);
void simpleDelay(uint32_t count);
void delayms(uint16_t ms);
uint8_t invertMotor(uint8_t direction);
void startMotor(uint8_t direction);
void stopMotor(void);

// Value from ADC 0-4095 for 12-bit res.(default)
uint16_t adc_val;

// Current limit(as read by the ADC)
const uint16_t limit = 4095; // 2^12 - 1 for 12-bit res.(default)

// May need such a variable for determining whether the motor should invert
// or stop
uint8_t overcurrent_count = 0;

// Maximum number of inversions
const uint8_t max_invert = 2;

// May need a variable for passing the current direction to motor functions
uint8_t direction = 0;

void main(void) {
  systemClockInit();
  GPIOInit();
  ADCInit();

  // Start motor
  startMotor(direction);

  // Infinite loop
  for (;;) {
    // Start ADC
    ADC1_CR1 |= ADC1_CR1_START;

    // Wait for end of conversion
    while (!(ADC1_SR & ADC1_SR_EOC));

    // Read result
    adc_val = (ADC1_DRH << 8) | ADC1_DRL; // Depends on alignment(?)

    // Check if current passes the threshold and the motor can be inverted
    if (adc_val >= limit && overcurrent_count <= max_invert) {
      // Invert direction
      direction = invertMotor(direction);

      // Record instance of overcurrent
      overcurrent_count++;

      // Turns the buzzer on for half a second
      PORT(BUZZER_GPIO_Port, ODR) |= BUZZER_Pin;
      delayms(500);
      PORT(BUZZER_GPIO_Port, ODR) &= ~BUZZER_Pin;
    } else if (overcurrent_count > max_invert) {
      // Too many instances, stop the motor
      stopMotor();
    }

    // Use tilt switch to turn the motor on and off(maybe needs debouncing)
    if (PORT(TILT_SWITCH_GPIO_Port, IDR) & TILT_SWITCH_Pin) {
      startMotor(direction);
    } else {
      stopMotor();
    }
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

  // Set LED_GREEN as output
  PORT(LED_GREEN_GPIO_Port, DDR) |= LED_GREEN_Pin;
  // Set LED_GREEN as "push-pull"
  PORT(LED_GREEN_GPIO_Port, CR1) |= LED_GREEN_Pin;

  // Set LED_RED as output
  PORT(LED_RED_GPIO_Port, DDR) |= LED_RED_Pin;
  // Set LED_RED as "push-pull"
  PORT(LED_RED_GPIO_Port, CR1) |= LED_RED_Pin;

  // Set BUZZER as output
  PORT(BUZZER_GPIO_Port, DDR) |= BUZZER_Pin;
  // Set BUZZER as "push-pull"
  PORT(BUZZER_GPIO_Port, CR1) |= BUZZER_Pin;

  // Set TRIAC_0 as output
  PORT(TRIAC_0_GPIO_Port, DDR) |= TRIAC_0_Pin;
  // Set TRIAC_0 as "push-pull"
  PORT(TRIAC_0_GPIO_Port, CR1) |= TRIAC_0_Pin;

  // Set TRIAC_1 as output
  PORT(TRIAC_1_GPIO_Port, DDR) |= TRIAC_1_Pin;
  // Set TRIAC_1 as "push-pull"
  PORT(TRIAC_1_GPIO_Port, CR1) |= TRIAC_1_Pin;

  // Initialize outputs to low
  PORT(LED_GREEN_GPIO_Port, ODR) &= ~LED_GREEN_Pin;
  PORT(LED_RED_GPIO_Port, ODR) &= ~LED_RED_Pin;
  PORT(BUZZER_GPIO_Port, ODR) &= ~BUZZER_Pin;
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

  // Delay needed (longer than wake-up(3us), shorter than idle(20ms at 70C))
  delayms(1);
}

/*
 * Very crude delay function. Don't use in the actual build.
 */
void simpleDelay(uint32_t count) {
  while (count--) {
    __asm("nop");
  }
}

/*
 * Use TIM2 to generate a delay. Does ms right now but a similar function can
 * be written to do delay in us. If so, adjust timer value. If it goes out of
 * range, use the prescaler to adjust. Consult clock configuration under /info
 * folder for a better understanding.
 */
void delayms(uint16_t ms) {
  // (Clock(kHz) / Prescaler) * ms
  uint16_t timer_value = (16000 / 16) * ms;

  // Prescale ([2,1,0] bits are 100 for 2^4=16)
  TIM2_PSCR |= 4;

  // Set Auto-Reload Register value
  TIM2_ARRH = (timer_value >> 8);
  TIM2_ARRL = (timer_value & 0xFF);

  // Start Timer
  TIM2_CR1 |= TIM2_CR1_CEN;

  // Wait for update flag
  while (!(TIM2_SR1 & TIM2_SR1_UIF));
  // Clear update flag
  TIM2_SR1 &= ~TIM2_SR1_UIF;

  // Stop Timer
  TIM2_CR1 &= ~TIM2_CR1_CEN;
}

/*
 * Uses TRIAC GPIO pin to invert direction of the motor and returns current
 * direction if successful.
 */
uint8_t invertMotor(uint8_t direction) {
  if (direction) {
    PORT(TRIAC_0_GPIO_Port, ODR) &= ~TRIAC_0_Pin;
    PORT(TRIAC_1_GPIO_Port, ODR) |= TRIAC_1_Pin;
    direction = 0;
  } else {
    PORT(TRIAC_0_GPIO_Port, ODR) |= TRIAC_0_Pin;
    PORT(TRIAC_1_GPIO_Port, ODR) &= ~TRIAC_1_Pin;
    direction = 1;
  }
  return direction;
}

/*
 * Uses TRIAC GPIO pins to start motor in the given direction.
 */
void startMotor(uint8_t direction) {
  if (direction) {
    PORT(TRIAC_0_GPIO_Port, ODR) &= ~TRIAC_0_Pin;
    PORT(TRIAC_1_GPIO_Port, ODR) |= TRIAC_1_Pin;
  } else {
    PORT(TRIAC_0_GPIO_Port, ODR) |= TRIAC_0_Pin;
    PORT(TRIAC_1_GPIO_Port, ODR) &= ~TRIAC_1_Pin;
  }
}

/*
 * Uses TRIAC GPIO pins to stop the motor.
 */
void stopMotor(void) {
  PORT(TRIAC_0_GPIO_Port, ODR) &= ~TRIAC_0_Pin;
  PORT(TRIAC_1_GPIO_Port, ODR) &= ~TRIAC_1_Pin;
}