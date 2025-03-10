#include <EEPROM.h>

const int address = 0;
int value = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial connect");
  EEPROM.begin(512);
  int value = EEPROM.length();
  Serial.printf("length=%d\r\n", value); 
  int count = EEPROM.readUInt(address);
  Serial.printf("count=%d\r\n", count);
  count += 1;
  //count = 0;
  EEPROM.writeUInt(address, count);
  EEPROM.commit();
  Serial.printf("count=%d\r\n", count);
}

void loop() {
  // Serial.println(value);
  // delay(1000);
}