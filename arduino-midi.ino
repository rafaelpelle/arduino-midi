#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <FastLED.h>
const byte NOTE_ON = 144;
const byte NOTE_OFF = 128;
const int LED_PIN = 7;
const int NUM_LEDS = 74;
const int NUM_KEYS = 88;
const int PIANO_OFFSET = 21;
const int ARRAY_SIZE = 10;
byte commandByte;
byte noteByte;
byte velocityByte;
int pressedNotes[ARRAY_SIZE];
int keyToLedMapper[NUM_KEYS] = {0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 11, 12, 13, 13, 14, 15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 23, 24, 25, 26, 27, 28, 28, 29, 30, 31, 32, 32, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 42, 43, 44, 45, 46, 47, 47, 48, 49, 50, 51, 52, 52, 53, 54, 55, 56, 57, 57, 58, 59, 60, 60, 61, 62, 63, 64, 65, 66, 66, 67, 68, 69, 70, 70, 71, 72};

CRGB leds[NUM_LEDS];
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);



void resetPressedNotes() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    pressedNotes[i] = -1;
  }
}

void insertNote(byte note) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (pressedNotes[i] == -1) {
      pressedNotes[i] = note;
      break;
    }
  }
}

void removeNote(byte note) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (pressedNotes[i] == note) {
      pressedNotes[i] = -1;
      break;
    }
  }
}

void updateLedStrip() {
  // Turn off the LEDs from last update
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  // Turn on the LEDs from this update
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (pressedNotes[i] >= 0) {
      int ledIndex = keyToLedMapper[pressedNotes[i] - PIANO_OFFSET];
      leds[ledIndex] = CRGB(255, 255, 255);
    }
  }
  FastLED.show();
}

//void updateDisplay() {
//  String displayLine1 = "";
//  for (int i = 0; i < ARRAY_HALF_SIZE; i++) {
//    if (pressedNotes[i] >= 0) {
//      displayLine1 = displayLine1 + pressedNotes[i] + " ";
//    }
//  }
//  String displayLine2 = "";
//  for (int i = ARRAY_HALF_SIZE; i < ARRAY_SIZE; i++) {
//    if (pressedNotes[i] >= 0) {
//      displayLine2 = displayLine2 + pressedNotes[i] + " ";
//    }
//  }
//  lcd.clear();
//  lcd.print(displayLine1);
//  lcd.setCursor (0, 1);
//  lcd.print(displayLine2);
//}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  //  lcd.begin(16, 2);
  //  lcd.clear();
  resetPressedNotes();
}

void loop() {
  while (Serial.available() > 2) { //While at least three bytes available
    commandByte = Serial.read();
    noteByte = Serial.read();
    velocityByte = Serial.read();
    if (commandByte == NOTE_ON) {
      insertNote(noteByte);
    } else if (commandByte == NOTE_OFF) {
      removeNote(noteByte);
    }
    //    updateDisplay();
    updateLedStrip();
  };
}
