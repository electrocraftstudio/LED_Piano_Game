# Arduino LED Piano

This project is an Arduino-based LED piano with levels and a buzzer for sound feedback. The project is designed for beginners to intermediate Arduino enthusiasts.

## Project Details

- **Name**: Arduino LED Piano
- **Description**: A fun and interactive project where players follow LED sequences to play a virtual piano. The game progresses through levels, increasing in difficulty.
- **Components**:
  - Arduino Uno
  - 5 LEDs
  - 5 Push Buttons
  - 5 Resistors
  - LCD1602 I2C Display
  - Buzzer
- **Libraries**: 
  - `LiquidCrystal_I2C` (for the LCD1602 display)

## How It Works

- Each level lights up a sequence of LEDs.
- The player must press the corresponding buttons in the correct order.
- If successful, they advance to the next level, where the sequence is longer.
- If they make a mistake, the game shows "Game Over" and restarts.
- The buzzer provides sound feedback for each button press.

## Pin Configuration

- **LEDs**: Connect each LED to digital pins 2-6.
- **Buttons**: Connect each button to digital pins 7-11 with a pull-down resistor.
- **LCD1602 I2C**: Connect SDA to A4, SCL to A5.
- **Buzzer**: Connect the buzzer to digital pin 12.

## Setup

1. Clone this repository to your local machine.
2. Upload the `LED_Piano.ino` file to your Arduino.
3. Connect the components as described in the pin configuration section.
4. Install the `LiquidCrystal_I2C` library in the Arduino IDE.
5. Run the code and follow the instructions on the LCD screen.

## Credits

- Project by (https://github.com/electrocraftstudio)
- Inspired by classic Simon Says and piano games.

## License

This project is licensed under the MIT License.
