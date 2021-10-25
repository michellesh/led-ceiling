// Receives data from the sender ESP8266
// Sends that data to the Arduino Due

// Connect RX pin (ESP) to 18/TX1 (Due)
// Connect TX pin (ESP) to 19/RX1 (Due)
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "BetsyShared.h"

Button data;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataRecv);
}

void onDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&data, incomingData, sizeof(data));
  Serial.println(stringifyButton(data));
}

void loop() {
}
