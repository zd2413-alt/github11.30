#include "BetterButton.h"

int button1Pin = 27;
int button2Pin = 32;
int button3Pin = 33;
int button4Pin = 34;

int ledPins[4] = { 0, 1, 2, 3 };
int midiNotesArray[4] = { 60, 70, 80, 95 };
int buttonPinArray[4] = { 27, 32, 33, 34 };

BetterButton button1(button1Pin, 0);
BetterButton button2(button2Pin, 1);
BetterButton button3(button3Pin, 2);
BetterButton button4(button4Pin, 3);
BetterButton* buttonArray[4] = { &button1, &button2, &button3, &button4 };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPinArray[i], INPUT);
  }
  for (int i = 0; i < 4; i++) {
    buttonArray[i]->pressHandler(onPress);
    buttonArray[i]->releaseHandler(onRelease);
  }
}


void loop() {
  for (int i = 0; i < 4; i++) {
    buttonArray[i]->process();
  }
}

void onPress(int val) {
  Serial.print(val);
  Serial.println(" on");
  digitalWrite(ledPins[val], HIGH);
  usbMIDI.sendNoteOn(midiNotesArray[val], 127, 1);
}

void onRelease(int val) {
  Serial.print(val);
  Serial.println(" off");
  usbMIDI.sendNoteOff(midiNotesArray[val], 0, 1);
  digitalWrite(ledPins[val], LOW);
}
