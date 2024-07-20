#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NUM_LEDS 5
#define NUM_LEVELS 10

const int ledPins[NUM_LEDS] = {2, 3, 4, 5, 6};
const int buttonPins[NUM_LEDS] = {7, 8, 9, 10, 11};
const int buzzerPin = 12;
int currentLevel = 1;
bool gameOver = false;
int sequence[NUM_LEVELS];
int currentStep = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.setCursor(0, 1);
  lcd.print("Press any button");

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if (gameOver) {
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(ledPins[i], HIGH);
      tone(buzzerPin, random(100, 1000));
      delay(100);
      digitalWrite(ledPins[i], LOW);
      noTone(buzzerPin);
      delay(100);
    }

    if (anyButtonPressed()) {
      gameOver = false;
      currentLevel = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Level: 1");
      lcd.setCursor(0, 1);
      lcd.print("Let's Start!");
      delay(1000);
    }

    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(currentLevel);
  lcd.setCursor(0, 1);
  lcd.print("Get Ready!");

  generateSequence();
  showSequence();

  currentStep = 0;

  while (!gameOver) {
    if (digitalRead(buttonPins[sequence[currentStep]]) == LOW) {
      tone(buzzerPin, 1000, 100);
      delay(150);

      currentStep++;
      if (currentStep >= currentLevel) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Level: ");
        lcd.print(currentLevel + 1);
        lcd.setCursor(0, 1);
        lcd.print(getRandomSuccessMessage());
        delay(1000);

        currentLevel++;
        if (currentLevel > NUM_LEVELS) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("You Win!");
          lcd.setCursor(0, 1);
          lcd.print("Congratulations!");
          delay(2000);
          currentLevel = 1;
        }

        break;
      }
    } else if (anyButtonPressed() && digitalRead(buttonPins[sequence[currentStep]]) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over");
      lcd.setCursor(0, 1);
      lcd.print("Try Again");
      gameOver = true;
      delay(2000);
      break;
    }
  }
}

void generateSequence() {
  for (int i = 0; i < currentLevel; i++) {
    sequence[i] = random(NUM_LEDS);
  }
}

void showSequence() {
  int delayTime = 500 - (currentLevel - 1) * 40; // Decreases delayTime with each level
  for (int i = 0; i < currentLevel; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);
    tone(buzzerPin, random(100, 1000));
    delay(delayTime);
    digitalWrite(ledPins[sequence[i]], LOW);
    noTone(buzzerPin);
    delay(delayTime);
  }
}

bool anyButtonPressed() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      return true;
    }
  }
  return false;
}

String getRandomSuccessMessage() {
  String messages[] = {"Bravo!", "Well Done!", "Great!", "Awesome!", "Fantastic!"};
  return messages[random(0, 5)];
}
