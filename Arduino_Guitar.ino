// Guitar Tuning E2–A2–D3–G3–B3–E4

const int E2 = 82;
const int F2 = 87;
const int FS2 = 92;
const int G2 = 98;
const int GS2 = 104;
const int TONEA2 = 110;
const int TONEAS2 = 117;
const int B2 = 123;
const int C3 = 131;
const int CS3 = 139;
const int D3 = 147;
const int DS3 = 156;
const int E3 = 165;
const int F3 = 175;
const int FS3 = 185;
const int G3 = 196;
const int GS3 = 208;
const int TONEA3 = 220;
const int AS3 = 233;
const int B3 = 247;
const int C4 = 262;
const int CS4 = 277;
const int D4 = 294;
const int DS4 = 311;
const int E4 = 330;
const int F4 = 349;
const int FS4 = 370;
const int G4 = 392;
const int GS4 = 415;
const int TONEA4 = 440;
const int AS4 = 466;
const int B4 = 494;
const int C5 = 523;
const int CS5 = 554;
const int D5 = 587;
const int DS5 = 622;
const int E5 = 659;
int tones[] = {E2, F2, FS2, G2, GS2, TONEA2, TONEAS2, B2, C3, CS3, D3, DS3, E3, F3, FS3, G3, GS3, TONEA3, AS3, B3, C4, CS4, D4, DS4,
               E4, F4, FS4, G4, GS4, TONEA4, AS4, B4, C5, CS5, D5, DS5, E5
              };
const int WHOLENOTE = 2400;
const int HALFNOTE = 1200;
const int QUARTERNOTE = 600;
const int EIGHTHNOTE = 300;

#include "Display.h"
const int KNOB = A0;
const int BUZZER = 3;
const int BUTTON_INPUT = 9;
const int BUTTON_CONFIRM = 8;
const int DEBOUNCE_DELAY = 50;
int buttonState1;
int buttonState2;
int lastButtonState1;
unsigned long  lastDebounceTime1;
int lastButtonState2;
unsigned long lastDebounceTime2;


int guitarString;
int knobValue;
int toggleEasterEgg;
int counter;

void setup() {
  pinMode(BUTTON_INPUT, INPUT_PULLUP);
  pinMode(BUTTON_CONFIRM, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(KNOB, INPUT);
  lastButtonState1 = HIGH;
  lastDebounceTime1 = 0;
  lastButtonState2 = HIGH;
  lastDebounceTime2 = 0;
  guitarString = 6;
  counter = 0;

}

int readKeys() {
  int answer = 0;
  int reading = digitalRead(BUTTON_INPUT);
  if (reading != lastButtonState1) {
    lastDebounceTime1 = millis();
  }
  if ((millis() - lastDebounceTime1) > DEBOUNCE_DELAY) {
    if (reading != buttonState1) {
      buttonState1 = reading;
      if (buttonState1 == LOW) {
        lastButtonState1 = reading;
        answer = 1;
      }
    }
  }
  lastButtonState1 = reading;
  if (answer == 0) {
    reading = digitalRead(BUTTON_CONFIRM);
    if (reading != lastButtonState2) {
      lastDebounceTime2 = millis();
    }
    if ((millis() - lastDebounceTime2) > DEBOUNCE_DELAY) {
      if (reading != buttonState2) {
        buttonState2 = reading;
        if (buttonState2 == LOW) {
          answer = 2;
        }
      }
    }
  }
  lastButtonState2 = reading;
  return answer;
}

int readKnob() {
  int knobAmmount = analogRead(KNOB);
  knobAmmount /= 84.5;
  return knobAmmount;
}

void PlayTone() {
  int toneNum = (6 - guitarString) * 5 + knobValue;
  if (guitarString > 4) {
    toneNum--;
  }
  int toneToPlay = tones[toneNum];
  tone(BUZZER, toneToPlay, 500);
  counter = 0;
}

void ShowDisplay() {
  String displayLine = "";
  if (knobValue < 10) {
    displayLine += "0";
  }
  displayLine += String(knobValue);
  displayLine += "-";
  displayLine += String(guitarString);

  Display.show(displayLine);
}

void ChangeString() {
  if (guitarString > 1) {
    guitarString--;
  } else {
    guitarString = 6;
  }
  counter++;
  if (counter == 12){
    easterEgg();
  }
}

void loop() {
  int pressedKey = readKeys();
  knobValue = readKnob();

  if (pressedKey == 1) {
    PlayTone();
  }
  if (pressedKey == 2) {
    ChangeString();
  } 
  ShowDisplay();
}
void PlayNote (int toneNote, int interval){
  tone(BUZZER, toneNote, interval);
  delay(interval);
}
void PlayNote (int toneNote){
  PlayNote(toneNote, EIGHTHNOTE);
}
void easterEgg() {  
  PlayNote(AS3,QUARTERNOTE);
  PlayNote(F4);
  PlayNote(D4);
  PlayNote(D4);
  delay(EIGHTHNOTE);
  PlayNote(C4);
  PlayNote(AS3);
  PlayNote(AS3);
  PlayNote(DS4,QUARTERNOTE);
  PlayNote(D4);
  PlayNote(D4);
  PlayNote(C4);
  PlayNote(C4);
  PlayNote(AS3);
  delay(EIGHTHNOTE);
  PlayNote(AS3);
  PlayNote(F4);
  PlayNote(D4);
  PlayNote(D4);
  PlayNote(C4);
  PlayNote(C4);
  PlayNote(AS3);
  PlayNote(AS3);
  PlayNote(G3,QUARTERNOTE);
  PlayNote(F3,QUARTERNOTE);
  counter = 0;
}

// AS3 F4 D4 D4 C4 AS3   AS4 DS4 D4 D4 C4 C4 AS4   AS3 F4 D4 D4 C4 C4 AS3 AS3 G3 F3
