# arduino-midi

### My goals:
Use a Arduino UNO board to receive MIDI data over USB and use it to control a WS2812B individually adressable LED strip.

### MIDI format:
![alt text](https://github.com/rafaelpelle/arduino-midi/blob/master/midi-format.png?raw=true)

### To Do:
- [x] Receive MIDI data over USB;
- [x] MIDI "Note on" (command byte) recognition;
- [x] MIDI "Note off" (command byte) recognition;
- [x] MIDI "Note number" (data byte 1) recognition;
- [x] MIDI "Note velocity" (data byte 2) recognition;
- [x] Update the board memory state after every "Note on" and "Note off" event;
- [x] Show the pressed notes on the LCD Display after every "Note on" and "Note off" event;
- [x] Individually turn on/off the LEDs after every "Note on" and "Note off" event;

