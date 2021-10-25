// Receives data from the receiver ESP8266

// Connect RX pin (ESP) to 18/TX1 (Due)
// Connect TX pin (ESP) to 19/RX1 (Due)
#include "BetsyShared.h"

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  if (Serial1.available()) {
    String str = Serial1.readStringUntil('\n');
    Button button = parseButton(str);
    Serial.print("id: ");
    Serial.println(button.id);
    Serial.print("value1: ");
    Serial.println(button.value1);
    Serial.print("value2: ");
    Serial.println(button.value2);
  }
}
