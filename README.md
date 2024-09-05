# STM8L051-switching

## Description

This project is designed for the STM8L051F3 microcontroller. It drives two TRIAC thyristors using GPIO outputs and reads input from a current sensor connected to the ADC. The operation of the TRIACs is controlled based on the state of a tilt switch connected to a GPIO input.

## Features

- **TRIAC Control**: Drives two TRIAC thyristors using GPIO pins.
- **Current Sensing**: Reads current values from an ADC-connected sensor.
- **Tilt Switch Input**: Monitors a tilt switch to determine whether to turn TRIACs on or off.
- **Efficient MCU Utilization**: Designed specifically for the STM8L051F3 microcontroller.

## Pins Configuration

| Pin Nb | PINs | FUNCTIONs   | LABELs         |
|--------|------|-------------|----------------|
| 3      | PA0  | SYS_SWIM    | SWIM           |
| 11     | PB1  | ADC1_IN17   | CURRENT_SENSOR |
| 12     | PB2  | GPIO_Output | BUZZER         |
| 13     | PB3  | GPIO_Output | LED_RED        |
| 14     | PB4  | GPIO_Output | LED_GREEN      |
| 16     | PB6  | GPIO_Input  | TILT_SWITCH    |
| 17     | PB7  | GPIO_Output | TRIAC_1        |
| 18     | PC0  | GPIO_Output | TRIAC_0        |

## Installation

To get started with this project, you will need:

1. **STM8L051F3 Microcontroller**: Ensure you have the STM8S001J3 microcontroller available.
2. **Development Environment**: Install the [Cosmic IdeaSTM8](https://www.cosmicsoftware.com/download_stm8_free.php) or a compatible IDE for STM8 development.

### Steps:

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/okemal/STM8L051-switching.git
   ```

2. **Load the project file in IdeaSTM8**: Use the .prjsm8 file in the root folder. In IdeaSTM8 it's Project-->Load-->STM8L051-switching.prjsm8
