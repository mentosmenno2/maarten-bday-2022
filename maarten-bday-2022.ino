// Include libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Include custom libraries
#include "pitches.h"

// Define pins
#define PIN_PIEZO 11
#define PIN_BUTTON_RESET 8
#define PIN_BUTTON_ADD 7
#define PIN_BUTTON_NEXT 6

// Define display constants
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define global game variables
int levelNumber = 0;
unsigned int gameStartTimestampMillis = 0;

void setup() {
  // Setup the serial monitor
  Serial.begin(9600);

  // Setup the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextColor(SSD1306_WHITE);

  // Setup the buttons
  pinMode(PIN_BUTTON_RESET, INPUT);
  pinMode(PIN_BUTTON_ADD, INPUT);
  pinMode(PIN_BUTTON_NEXT, INPUT);

  // Setup the speaker
  pinMode(PIN_PIEZO, OUTPUT);
}

void loop() {
  playCurrentLevel();
  levelNumber++;
}

void playCurrentLevel() {
  switch (levelNumber) {
    case 0:
      gameStartTimestampMillis = millis();
      playLevelZero();
      break;
    case 1:
      displayLevelMessage();
      playLevelOne();
      break;
    case 2:
      displayLevelMessage();
      playLevelTwo();
      break;
    case 3:
      displayLevelMessage();
      playLevelThree();
      break;
    case 4:
      displayLevelMessage();
      playLevelFour();
      break;
    case 5:
      displayLevelMessage();
      playLevelFive();
      break;
    case 6:
      displayLevelMessage();
      playLevelSix();
      break;
    case 7:
      displayLevelMessage();
      playLevelSeven();
      break;
    case 8:
      displayLevelMessage();
      playLevelEight();
      break;
    case 9:
      displayLevelMessage();
      playLevelNine();
      break;
    case 10:
      displayLevelMessage();
      playLevelTen();
      break;
    default:
      playLevelFinished();
      playLevelHappyBirthday();
      break;
  }
}

// Levels

void playLevelHappyBirthday() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Van harte\r\ngefeliciteerd Maarten\r\nmet je verjaardag!");
  display.display();

  playHappyBirthday();

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Kies optie:\r\n0: Reboot\r\n1+: Happy birthday!");
  display.display();

  int userInput = awaitUserInput();
  if(userInput == 0) {
    levelNumber = -1;
    return;
  }
  
  playLevelHappyBirthday();
}

void playLevelFinished() {
  unsigned int gameEndTimestampMillis = millis();
  unsigned int secondsItTook = round((gameEndTimestampMillis - gameStartTimestampMillis) / 1000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("Finished");
  display.display();
  display.startscrollleft(0x00, 0x0F);
  delay(5000);
  display.stopscroll();
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Jouw tijd:");
  display.setCursor(0, 8);
  display.setTextSize(2);
  display.println(String(secondsItTook));
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.println("seconden");
  display.display();
  delay(5000);
}

void playLevelTen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Decodeer:\r\n26 5 19 5 14 20 23 9 14 20 9 7");
  display.display();

  awaitCorrectAnswer(26);
}

void playLevelNine() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Op welke vraagindex\r\nzijn we nu?");
  display.display();

  awaitCorrectAnswer(8);
}

void playLevelEight() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Waar zijn we?\r\n###.0.0.1");
  display.display();

  awaitCorrectAnswer(127);
}

void playLevelSeven() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Wat krijg je als je\r\nhet cijfer 42 2x\r\nbitshift naar\r\nrechts?");
  display.display();

  awaitCorrectAnswer(10);
}

void playLevelSix() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Welk getal staat\r\nop plek 3 en 4\r\nachter de komma\r\nvan PI?");
  display.display();

  awaitCorrectAnswer(15);
}

void playLevelFive() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Hoeveel jaar verschil\r\nzit er tussen\r\nonze geboortejaren?\r\n(Menno en Maarten)");
  display.display();

  awaitCorrectAnswer(0);
}

void playLevelFour() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Wat is\r\n11011010 - 11000110?");
  display.display();

  awaitCorrectAnswer(20);
}

void playLevelThree() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Op welke latitude\r\nbevinden wij ons?\r\n(afgerond)");
  display.display();

  awaitCorrectAnswer(52);
}

void playLevelTwo() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Decodeer:\r\nMA==");
  display.display();

  awaitCorrectAnswer(0);
}

void playLevelOne() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Als 42 het antwoord\r\nis op alles, dan is\r\n... het antwoord\r\nop niets.");
  display.display();

  awaitCorrectAnswer(24);
}

void playLevelZero() {
  for (int percent = 0; percent < 100; percent++) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(100, 0);
    display.println(String(percent + 1) + "%");
    display.display();
  }

  playLoadedSound();
  delay(1000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Welkom\r\nMaarten"));
  display.display();
  delay(5000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(F("Ben je klaar\r\nvoor een kleine\r\nquiz?"));
  display.display();
  delay(10000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(F("Dit jaar niet\r\nmet alleen maar\r\nprogrammeerpuzzletjes\r\n...      LETS GO!!!"));
  display.display();
  delay(10000);
}

// Await input logic

void awaitCorrectAnswer(int correctAnswer) {
  int userInput = awaitUserInput();
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Jouw antwoord");
  display.setCursor(0, 8);
  display.setTextSize(2);
  display.println("\"" + String(userInput) + "\"");
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.println("is ...");
  display.display();
  delay(2000);
  if( userInput == correctAnswer ) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println(F("Goed! :)"));
    display.display();
    playSoundSuccess();
    delay(2000);
    return;
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(F("Fout :("));
  display.display();
  playSoundFail();
  delay(2000);
  awaitCorrectAnswer(correctAnswer);
}

int awaitUserInput() {
  int currentInput = 0;
  
  // Only enable after pressing one of the buttons
  while(digitalRead(PIN_BUTTON_RESET) == LOW && digitalRead(PIN_BUTTON_ADD) == LOW && digitalRead(PIN_BUTTON_NEXT) == LOW) {
    delay(1);
  }
  
  displayCurrentInputValue(currentInput);
  delay(200);
  
  while(digitalRead(PIN_BUTTON_NEXT) == LOW) {
      if (digitalRead(PIN_BUTTON_RESET) == HIGH) {
        currentInput = 0;
        displayCurrentInputValue(currentInput);
      }
      if (digitalRead(PIN_BUTTON_ADD) == HIGH) {
        currentInput++;
        displayCurrentInputValue(currentInput);
        delay(200);
      }
  }
 
  return currentInput;
}

// Display messages

void displayLevelMessage() {
  display.clearDisplay();
  display.setCursor(30, 0);
  display.setTextSize(2);
  display.println("Level " + String(levelNumber));
  display.display();
  display.startscrollleft(0x00, 0x0F);
  delay(5000);
  display.stopscroll();
}

void displayCurrentInputValue(int input) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Jouw antwoord:");
  display.setCursor(0, 16);
  display.setTextSize(2);
  display.println(String(input));
  display.display();
}

// Play sounds

void playSoundSuccess() {
  tone(PIN_PIEZO, NOTE_E6, 125);
  delay(130);
  tone(PIN_PIEZO, NOTE_G6, 125);
  delay(130);
  tone(PIN_PIEZO, NOTE_E7, 125);
  delay(130);
  tone(PIN_PIEZO, NOTE_C7, 125);
  delay(130);
  tone(PIN_PIEZO, NOTE_D7, 125);
  delay(130);
  tone(PIN_PIEZO, NOTE_G7, 125);
  delay(125);
  noTone(PIN_PIEZO);
}

void playSoundFail() {
  tone(PIN_PIEZO, NOTE_B5, 200);
  delay(260);
  tone(PIN_PIEZO, NOTE_F6, 200);
  delay(300);
  tone(PIN_PIEZO, NOTE_F6, 150);
  delay(200);
  tone(PIN_PIEZO, NOTE_F6, 150);
  delay(200);
  tone(PIN_PIEZO, NOTE_E6, 200);
  delay(200);
  tone(PIN_PIEZO, NOTE_D6, 150);
  delay(200);
  tone(PIN_PIEZO, NOTE_C6, 150);
  delay(200);
  tone(PIN_PIEZO, NOTE_E5, 150);
  delay(200);
  tone(PIN_PIEZO, NOTE_E5, 150);
  delay(200);
  tone(PIN_PIEZO, NOTE_C5, 200);
  delay(200);
  
  noTone(PIN_PIEZO);
}

void playLoadedSound() {
  tone(PIN_PIEZO, NOTE_B6, 100);
  delay(100);
  tone(PIN_PIEZO, NOTE_E7, 850);
  delay(800);
  noTone(PIN_PIEZO);
}

void playHappyBirthday() {
  for (int i = 0; i < 2; i++) {
    tone(PIN_PIEZO, 131);
    delay(250);
    noTone(PIN_PIEZO);
    delay(125);
    tone(PIN_PIEZO, 131);
    delay(250);
    tone(PIN_PIEZO, 147);
    delay(500);
    tone(PIN_PIEZO, 131);
    delay(500);
    tone(PIN_PIEZO, 175);
    delay(500);
    tone(PIN_PIEZO, 165);
    delay(1000);
    tone(PIN_PIEZO, 131);
    delay(250);
    noTone(PIN_PIEZO);
    delay(125);
    tone(PIN_PIEZO, 131);
    delay(250);
    tone(PIN_PIEZO, 147);
    delay(500);
    tone(PIN_PIEZO, 131);
    delay(500);
    tone(PIN_PIEZO, 196);
    delay(500);
    tone(PIN_PIEZO, 175);
    delay(1000);
    tone(PIN_PIEZO, 131);
    delay(250);
    noTone(PIN_PIEZO);
    delay(125);
    tone(PIN_PIEZO, 131);
    delay(250);
    tone(PIN_PIEZO, 262);
    delay(500);
    tone(PIN_PIEZO, 220);
    delay(500);
    tone(PIN_PIEZO, 175);
    delay(500);
    tone(PIN_PIEZO, 165);
    delay(500);
    tone(PIN_PIEZO, 147);
    delay(500);
    tone(PIN_PIEZO, 233);
    delay(250);
    noTone(PIN_PIEZO);
    delay(125);
    tone(PIN_PIEZO, 233);
    delay(250);
    tone(PIN_PIEZO, 220);
    delay(500);
    tone(PIN_PIEZO, 175);
    delay(500);
    tone(PIN_PIEZO, 196);
    delay(500);
    tone(PIN_PIEZO, 175);
    delay(1000);
    noTone(PIN_PIEZO);
    delay(2000);
  }
}
