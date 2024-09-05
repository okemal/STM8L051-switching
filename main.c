/* main.c */
/* Tried to explain most things, consult the datasheet and the reference manual
 * provided under the /info folder. For definitions check main.h file.
 */
#include "main.h"

#include <stdint.h>

#define ADC_CHANNEL 17
#define DEBOUNCE_DELAY_MS 10
#define CURRENT_LIMIT 4095 // 2^12 - 1 for 12-bit res.(default)
#define MAX_INVERT 2       // Maximum number of inversions
#define BUZZER_DELAY_MS 10000

// Function prototypes
void systemClockInit(void);
void GPIOInit(void);
void ADCInit(void);
void delayms(uint16_t ms);
uint8_t invertMotor(uint8_t direction);
void startMotor(uint8_t direction);
void stopMotor(void);
uint8_t isTiltSwitchActivated(void);

// Value from ADC 0-4095 for 12-bit res.(default)
uint16_t adc_val;

// May need such a variable for determining whether the motor should invert
// or stop
uint8_t overcurrent_count = 0;

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

    // Wait for end of conversion (may need a timeout)
    while (!(ADC1_SR & ADC1_SR_EOC))
      ;

    // Read result
    adc_val = (ADC1_DRH << 8) | ADC1_DRL; // Depends on alignment(?)

    // Check if current passes the threshold and the motor can be inverted
    if (adc_val >= CURRENT_LIMIT && overcurrent_count <= MAX_INVERT) {
      // Invert direction
      direction = invertMotor(direction);

      // Record instance of overcurrent
      overcurrent_count++;

    } else if (overcurrent_count > MAX_INVERT) {
      // Too many instances, stop the motor
      stopMotor();
      // Turns the buzzer on for some time
      PORT(BUZZER_GPIO_Port, ODR) |= BUZZER_Pin;
      delayms(BUZZER_DELAY_MS);
      PORT(BUZZER_GPIO_Port, ODR) &= ~BUZZER_Pin;
    }

    // Use tilt switch to turn the motor on and off
    if (isTiltSwitchActivated()) {
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
  // Set output pins
  PORT(LED_GREEN_GPIO_Port, DDR) |= LED_GREEN_Pin;
  PORT(LED_RED_GPIO_Port, DDR) |= LED_RED_Pin;
  PORT(BUZZER_GPIO_Port, DDR) |= BUZZER_Pin;
  PORT(TRIAC_0_GPIO_Port, DDR) |= TRIAC_0_Pin;
  PORT(TRIAC_1_GPIO_Port, DDR) |= TRIAC_1_Pin;

  // Set input pin
  PORT(TILT_SWITCH_GPIO_Port, DDR) &= ~TILT_SWITCH_Pin;

  // Enable/disable pull-up resistor for inputs
  // Enable/disable push-pull for outputs
  PORT(TILT_SWITCH_GPIO_Port, CR1) |= TILT_SWITCH_Pin;
  PORT(LED_GREEN_GPIO_Port, CR1) |= LED_GREEN_Pin;
  PORT(LED_RED_GPIO_Port, CR1) |= LED_RED_Pin;
  PORT(BUZZER_GPIO_Port, CR1) |= BUZZER_Pin;
  PORT(TRIAC_0_GPIO_Port, CR1) |= TRIAC_0_Pin;
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
  // Select channel
  ADC1_CR3 &= 0xE0;
  ADC1_CR3 |= ADC_CHANNEL;

  // Select sampling time
  ADC1_CR2 |= CYCLES_192;

  // Turn AD on
  ADC1_CR1 |= ADC1_CR1_ADON;

  // Delay needed (longer than wake-up(3us), shorter than idle(20ms at 70C))
  delayms(1);
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

  // Prescale
  TIM2_PSCR |= TIM_PRSC_16;

  // Set Auto-Reload Register value
  TIM2_ARRH = (timer_value >> 8);
  TIM2_ARRL = (timer_value & 0xFF);

  // Start Timer
  TIM2_CR1 |= TIM2_CR1_CEN;

  // Wait for update flag
  while (!(TIM2_SR1 & TIM2_SR1_UIF))
    ;
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
    PORT(TRIAC_1_GPIO_Port, ODR) &= ~TRIAC_1_Pin;
    delay_ms(10);
    PORT(TRIAC_0_GPIO_Port, ODR) |= TRIAC_0_Pin;
    direction = 0;
  } else {
    PORT(TRIAC_0_GPIO_Port, ODR) &= ~TRIAC_0_Pin;
    delay_ms(10);
    PORT(TRIAC_1_GPIO_Port, ODR) |= TRIAC_1_Pin;
    direction = 1;
  }
  return direction;
}

/*
 * Uses TRIAC GPIO pins to start motor in the given direction.
 */
void startMotor(uint8_t direction) {
  if (direction) {
    PORT(TRIAC_0_GPIO_Port, ODR) |= TRIAC_0_Pin;
    PORT(TRIAC_1_GPIO_Port, ODR) &= ~TRIAC_1_Pin;
  } else {
    PORT(TRIAC_0_GPIO_Port, ODR) &= ~TRIAC_0_Pin;
    PORT(TRIAC_1_GPIO_Port, ODR) |= TRIAC_1_Pin;
  }
}

/*
 * Uses TRIAC GPIO pins to stop the motor.
 */
void stopMotor(void) {
  PORT(TRIAC_0_GPIO_Port, ODR) |= TRIAC_0_Pin;
  PORT(TRIAC_1_GPIO_Port, ODR) |= TRIAC_1_Pin;
}

uint8_t isTiltSwitchActivated(void) {
  if (PORT(TILT_SWITCH_GPIO_Port, IDR) & TILT_SWITCH_Pin) {
    delayms(DEBOUNCE_DELAY_MS); // Debounce delay
    if (PORT(TILT_SWITCH_GPIO_Port, IDR) & TILT_SWITCH_Pin) {
      return 1;
    }
  }
  return 0;
}