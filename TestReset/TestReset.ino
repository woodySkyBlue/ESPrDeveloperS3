#include "bounce.h"

#define SW_1 1
#define SW_2 10
#define RESET_1 3
#define RESET_2 8

int StartupCounter = 0;
Debounce resetSwitch1(SW_1, 500);
Debounce resetSwitch2(SW_2, 500);
const unsigned long ON_TIME = 100;
unsigned long onState1Time = 0;
unsigned long onState2Time = 0;
bool isOn1 = false;
bool isOn2 = false;
bool hasOn1 = false;
bool hasOn2 = false;

void updateSwitchState(int switchState, bool &isOn, bool &hasOn, unsigned long &onStateTime, int resetPin, int otherSwitchState) {
  if (switchState == LOW && !hasOn && otherSwitchState == HIGH) {
    digitalWrite(resetPin, LOW);
    onStateTime = millis();
    isOn = true;
    hasOn = true;
  }
  if (isOn && ((millis() - onStateTime) >= ON_TIME)) {
    digitalWrite(resetPin, HIGH);
    isOn = false;
  }
  if (switchState == HIGH) {
    hasOn = false;
  }
}

void setup() {
  pinMode(RESET_1, OUTPUT);
  pinMode(RESET_2, OUTPUT);
  pinMode(SW_1, INPUT);
  pinMode(SW_2, INPUT);
  digitalWrite(RESET_1, HIGH);
  digitalWrite(RESET_2, HIGH);
}

void loop() {
  if (StartupCounter < 100) {
    StartupCounter += 1;
  }
  if (StartupCounter >= 100) {
    int switchState1 = resetSwitch1.read();
    int switchState2 = resetSwitch2.read();
    updateSwitchState(switchState1, isOn1, hasOn1, onState1Time, RESET_1, switchState2);
    updateSwitchState(switchState2, isOn2, hasOn2, onState2Time, RESET_2, switchState1);
  }
  delay(10);
}
