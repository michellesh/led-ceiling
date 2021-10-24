// Parses N64 data from string form

#include <ESP8266WiFi.h>
#include <espnow.h>

struct n64data {
  bool Start;
  bool Z;
  bool B;
  bool A;
  bool L;
  bool R;
  bool C_up;
  bool C_down;
  bool C_right;
  bool C_left;
  bool D_up;
  bool D_down;
  bool D_right;
  bool D_left;
  int axis_x;
  int axis_y;
};

n64data data;

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
}

void loop() {
  printN64();
  delay(1000);
}

void printN64() {
  Serial.print("Start: ");
  Serial.println(data.Start);
  Serial.print("Z: ");
  Serial.println(data.Z);
  Serial.print("B: ");
  Serial.println(data.B);
  Serial.print("A: ");
  Serial.println(data.A);
  Serial.print("L: ");
  Serial.println(data.L);
  Serial.print("R: ");
  Serial.println(data.R);
  Serial.print("C_up: ");
  Serial.println(data.C_up);
  Serial.print("C_down: ");
  Serial.println(data.C_down);
  Serial.print("C_right: ");
  Serial.println(data.C_right);
  Serial.print("C_left: ");
  Serial.println(data.C_left);
  Serial.print("D_up: ");
  Serial.println(data.D_up);
  Serial.print("D_down: ");
  Serial.println(data.D_down);
  Serial.print("D_right: ");
  Serial.println(data.D_right);
  Serial.print("D_left: ");
  Serial.println(data.D_left);
  Serial.print("axis_x: ");
  Serial.println(data.axis_x);
  Serial.print("axis_y: ");
  Serial.println(data.axis_y);
}
