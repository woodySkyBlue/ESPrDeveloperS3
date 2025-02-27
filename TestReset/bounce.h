class Debounce {
private:
  int pin;
  int lastSwitchState;
  int switchState;
  unsigned long lastDebounceTime;
  const unsigned long debounceDelay;
public:
  Debounce(int pin, unsigned long debounceDelay = 50): pin(pin), lastSwitchState(LOW), lastDebounceTime(0), debounceDelay(debounceDelay) {
    pinMode(pin, INPUT);
  }
  int read() {
    int reading = digitalRead(pin);
    if (reading != lastSwitchState) {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != switchState) {
        switchState = reading;
      }
    }
    lastSwitchState = reading;
    return switchState;
  }
};
  