// Basic test sketch for Adafruit STTC4 CO2 sensor

#include <Adafruit_STTC4.h>

Adafruit_STTC4 sttc4;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println(F("Adafruit STTC4 test"));

  if (!sttc4.begin()) {
    Serial.println(F("Failed to find STTC4 chip"));
    while (1) delay(10);
  }

  Serial.println(F("STTC4 found!"));
}

void loop() {
  delay(100);
}
