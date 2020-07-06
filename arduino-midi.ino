#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const byte NOTE_ON = 144;
const byte NOTE_OFF = 128;
const int ARRAY_SIZE = 10;
const int ARRAY_HALF_SIZE = ARRAY_SIZE / 2;
byte commandByte;
byte noteByte;
byte velocityByte;
int pressedNotes[ARRAY_SIZE];


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

void updateDisplay() {
  String displayLine1 = "";
  for (int i = 0; i < ARRAY_HALF_SIZE; i++) {
    if (pressedNotes[i] >= 0) {
      displayLine1 = displayLine1 + pressedNotes[i] + " ";
    }
  }
  String displayLine2 = "";
  for (int i = ARRAY_HALF_SIZE; i < ARRAY_SIZE; i++) {
    if (pressedNotes[i] >= 0) {
      displayLine2 = displayLine2 + pressedNotes[i] + " ";
    }
  }
  lcd.clear();
  lcd.print(displayLine1);
  lcd.setCursor (0, 1);
  lcd.print(displayLine2);
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
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
    updateDisplay();
  };
}
