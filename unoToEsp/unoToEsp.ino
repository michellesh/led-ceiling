// Receives data from the Arduino UNO
// Sends that data to the receiver ESP8266
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "BetsyShared.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(betsy_receiverAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  if (Serial.available()) {
    String str = Serial.readStringUntil('\n');
    msg m = parseMsg(str);
    Serial.print("buttonId: ");
    Serial.println(m.buttonId);
    Serial.print("buttonValue: ");
    Serial.println(m.buttonValue);
  }
}

void send(msg m) {
  esp_now_send(0, (uint8_t *) &m, sizeof(m));
}
