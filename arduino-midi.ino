#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const byte NOTE_ON = 144;
const byte NOTE_OFF = 128;
const int ARRAY_SIZE = 10;
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
  String displayText = "";
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (pressedNotes[i] >= 0) {
      displayText = displayText + pressedNotes[i] + ", ";
    }
  }
  lcd.clear();
  lcd.print(displayText);
  //  lcd.setCursor (0, 1);
  //  lcd.print((String)"Velocidade: " + velocityByte);
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
